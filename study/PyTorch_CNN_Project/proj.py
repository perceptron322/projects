import torch
import torch.nn as nn
import torch.distributed as dist
from torch.nn.parallel import DistributedDataParallel as DDP
from torch.utils.data import DataLoader, DistributedSampler
import time
import os

class ConvNet(nn.Module):
    def __init__(self):
        super().__init__()
        self.conv1 = nn.Conv2d(1, 32, 3, 1)
        self.conv2 = nn.Conv2d(32, 64, 3, 1)
        self.dropout1 = nn.Dropout(0.25)
        self.dropout2 = nn.Dropout(0.5)
        self.fc1 = nn.Linear(9216, 128)
        self.fc2 = nn.Linear(128, 10)
    
    def forward(self, x):
        x = self.conv1(x)
        x = nn.functional.relu(x)
        x = self.conv2(x)
        x = nn.functional.relu(x)
        x = nn.functional.max_pool2d(x, 2)
        x = self.dropout1(x)
        x = torch.flatten(x, 1)
        x = self.fc1(x)
        x = nn.functional.relu(x)
        x = self.dropout2(x)
        x = self.fc2(x)
        return x

def setup():
    if 'SLURM_PROCID' in os.environ:
        os.environ['RANK'] = os.environ['SLURM_PROCID']
        os.environ['WORLD_SIZE'] = os.environ['SLURM_NTASKS']
        os.environ['LOCAL_RANK'] = os.environ['SLURM_LOCALID']

        # MASTER_ADDR и MASTER_PORT устанавливаются в job скрипте
        if 'MASTER_ADDR' not in os.environ:
            raise RuntimeError("MASTER_ADDR not set!")
        if 'MASTER_PORT' not in os.environ:
            os.environ['MASTER_PORT'] = '29500'

        rank = int(os.environ['RANK'])
        world_size = int(os.environ['WORLD_SIZE'])
        hostname = os.environ.get('SLURMD_NODENAME', 'unknown')

        print(f"[Pre-init] Rank {rank}/{world_size} on {hostname}")
        print(f"[Pre-init] Master: {os.environ['MASTER_ADDR']}:{os.environ['MASTER_PORT']}")
    
    dist.init_process_group(backend='gloo')
    
    rank = dist.get_rank()
    world_size = dist.get_world_size()
    hostname = os.environ.get('SLURMD_NODENAME', 'unknown')
    print(f"[Post-init] Rank {rank}/{world_size} on {hostname} - CONNECTED")


def cleanup():
    dist.destroy_process_group()

def train(ddp_model, dataloader, sampler, criterion, optimizer, rank, epochs=5):
    for epoch in range(epochs):
        sampler.set_epoch(epoch)
        ddp_model.train()
        total_loss = 0.0

        for batch_idx, (data, target) in enumerate(dataloader):
            data, target = data.to('cpu'), target.to('cpu')

            optimizer.zero_grad()
            output = ddp_model(data)
            loss = criterion(output, target)
            loss.backward()
            optimizer.step()

            total_loss += loss.item()

            if batch_idx % 100 == 0 and rank == 0:
                print(f"Rank {rank}, Epoch {epoch}, Batch {batch_idx}, Loss: {loss.item():.4f}")

        if rank == 0:
            avg_loss = total_loss / len(dataloader)
            print(f"Epoch {epoch} finished, Avg Loss: {avg_loss:.4f}")

def test(ddp_model, dataloader, rank, world_size):
    ddp_model.eval()
    
    correct = 0
    total = 0
    test_loss = 0.0
    criterion = nn.CrossEntropyLoss()
    
    with torch.no_grad():
        for data, target in dataloader:
            data, target = data.to('cpu'), target.to('cpu')

            output = ddp_model(data)
            loss = criterion(output, target)
            test_loss += loss.item()

            pred = output.argmax(dim=1, keepdim=True)
            correct += pred.eq(target.view_as(pred)).sum().item()
            total += target.size(0)
    
    correct_tensor = torch.tensor(correct, dtype=torch.float32)
    total_tensor = torch.tensor(total, dtype=torch.float32)
    loss_tensor = torch.tensor(test_loss, dtype=torch.float32)
    
    dist.all_reduce(correct_tensor, op=dist.ReduceOp.SUM)
    dist.all_reduce(total_tensor, op=dist.ReduceOp.SUM)
    dist.all_reduce(loss_tensor, op=dist.ReduceOp.SUM)
    
    if rank == 0:
        accuracy = 100. * correct_tensor.item() / total_tensor.item()
        avg_loss = loss_tensor.item() / len(dataloader) / world_size
        print(f"\nTest Results:")
        print(f"  Average Loss: {avg_loss:.4f}")
        print(f"  Accuracy: {accuracy:.2f}% ({int(correct_tensor.item())}/{int(total_tensor.item())})")

def main():
    rank = dist.get_rank()
    world_size = dist.get_world_size()
    
    print(f"Process {rank}/{world_size} started")
    
    device = torch.device('cpu')
    model = ConvNet().to(device)
    ddp_model = DDP(model)
    
    from torchvision import datasets, transforms
    
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.5,), (0.5,))
    ])
    
    train_dataset = datasets.MNIST('./data', train=True, download=False, transform=transform)
    train_sampler = DistributedSampler(train_dataset, num_replicas=world_size, rank=rank, shuffle=True)
    train_loader = DataLoader(train_dataset, batch_size=64, sampler=train_sampler, num_workers=2)
    
    test_dataset = datasets.MNIST('./data', train=False, download=False, transform=transform)
    test_sampler = DistributedSampler(test_dataset, num_replicas=world_size, rank=rank, shuffle=False)
    test_loader = DataLoader(test_dataset, batch_size=64, sampler=test_sampler, num_workers=2)
    
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(ddp_model.parameters(), lr=0.001)
    
    if rank == 0:
        print("\n" + "="*50)
        print("Starting training...")
        print("="*50)
    
    start_time = time.time()
    train(ddp_model, train_loader, train_sampler, criterion, optimizer, rank, epochs=5)
    end_time = time.time()
    
    training_time = end_time - start_time
    
    if rank == 0:
        print("\n" + "="*50)
        print(f"Training completed in {training_time:.2f} seconds ({training_time/60:.2f} minutes)")
        print("="*50)
    
    if rank == 0:
        print("\n" + "="*50)
        print("Starting testing...")
        print("="*50)
    
    test(ddp_model, test_loader, rank, world_size)
    
    print(f"Process {rank} finished")

if __name__ == '__main__':
    setup()
    main()
    cleanup()