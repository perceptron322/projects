import matplotlib.pyplot as plt
import numpy as np

# Данные
processes = [4, 16, 28, 40, 52, 64]
nodes = [1, 1, 1, 2, 2, 2]

# Метод средних прямоугольников
midpoint_times = [0.000142378, 0.000178043, 0.000223808, 0.0445016, 0.0720465, 0.0127674]

# Метод Монте-Карло n=10^7
mc_1e7_times = [0.133666, 0.029185, 0.016392, 0.064526, 0.072693, 0.025591]

# Метод Монте-Карло n=10^8
mc_1e8_times = [1.007035, 0.286408, 0.189695, 0.191330, 0.212315, 0.126490]

# Создаем figure с тремя subplot
fig, axes = plt.subplots(1, 3, figsize=(16, 5))
fig.suptitle('Сравнение времени вычисления интегралов различными методами', 
             fontsize=16, fontweight='bold')

# График 1: Метод средних прямоугольников с разделением по узлам
ax1 = axes[0]
ax1.scatter(processes[:3], midpoint_times[:3], color='blue', s=100, 
            label='1 узел', zorder=3)
ax1.scatter(processes[3:], midpoint_times[3:], color='red', s=100, 
            label='2 узла', zorder=3)
ax1.plot(processes, midpoint_times, 'k--', alpha=0.3, linewidth=1)
ax1.set_xlabel('Количество процессов', fontsize=12)
ax1.set_ylabel('Время (секунды)', fontsize=12)
ax1.set_title('Метод средних прямоугольников', fontsize=13, fontweight='bold')
ax1.legend(fontsize=10)
ax1.grid(True, alpha=0.3)
ax1.set_xticks(processes)

# График 2: Монте-Карло n=10^7 с разделением по узлам
ax2 = axes[1]
ax2.scatter(processes[:3], mc_1e7_times[:3], color='blue', s=100, 
            label='1 узел', zorder=3)
ax2.scatter(processes[3:], mc_1e7_times[3:], color='red', s=100, 
            label='2 узла', zorder=3)
ax2.plot(processes, mc_1e7_times, 'k--', alpha=0.3, linewidth=1)
ax2.set_xlabel('Количество процессов', fontsize=12)
ax2.set_ylabel('Время (секунды)', fontsize=12)
ax2.set_title('Монте-Карло (n=10⁷)', fontsize=13, fontweight='bold')
ax2.legend(fontsize=10)
ax2.grid(True, alpha=0.3)
ax2.set_xticks(processes)

# График 3: Монте-Карло n=10^8 с разделением по узлам
ax3 = axes[2]
ax3.scatter(processes[:3], mc_1e8_times[:3], color='blue', s=100, 
            label='1 узел', zorder=3)
ax3.scatter(processes[3:], mc_1e8_times[3:], color='red', s=100, 
            label='2 узла', zorder=3)
ax3.plot(processes, mc_1e8_times, 'k--', alpha=0.3, linewidth=1)
ax3.set_xlabel('Количество процессов', fontsize=12)
ax3.set_ylabel('Время (секунды)', fontsize=12)
ax3.set_title('Монте-Карло (n=10⁸)', fontsize=13, fontweight='bold')
ax3.legend(fontsize=10)
ax3.grid(True, alpha=0.3)
ax3.set_xticks(processes)

plt.tight_layout()
plt.show()

# Таблица с данными
print("\n" + "="*80)
print("ТАБЛИЦА РЕЗУЛЬТАТОВ")
print("="*80)
print(f"{'Процессы':<12} {'Узлы':<8} {'Прямоуг.':<15} {'МК (10⁷)':<15} {'МК (10⁸)':<15}")
print("-"*80)
for i, p in enumerate(processes):
    print(f"{p:<12} {nodes[i]:<8} {midpoint_times[i]:<15.6f} "
          f"{mc_1e7_times[i]:<15.6f} {mc_1e8_times[i]:<15.6f}")
print("="*80)