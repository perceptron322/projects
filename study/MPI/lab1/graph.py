import matplotlib.pyplot as plt
import numpy as np

# Настройка стиля
plt.style.use('seaborn-v0_8-darkgrid')
fig = plt.figure(figsize=(16, 12))

# ========== 1. Ring Algorithm - Зависимость от размера сообщения ==========
ax1 = plt.subplot(2, 3, 1)

message_sizes = ['1B', '1KB', '1MB']
ring_8proc = [0.020293, 0.020908, 0.081849]
ring_16proc = [0.020793, 0.019870, 0.172357]
ring_32proc = [0.020150, 0.019992, 0.341563]

x = np.arange(len(message_sizes))
width = 0.25

ax1.bar(x - width, ring_8proc, width, label='8 процессов (2×4)', color='#2E86AB')
ax1.bar(x, ring_16proc, width, label='16 процессов (2×8)', color='#A23B72')
ax1.bar(x + width, ring_32proc, width, label='32 процесса (2×16)', color='#F18F01')

ax1.set_xlabel('Размер сообщения', fontsize=11, fontweight='bold')
ax1.set_ylabel('Время (сек)', fontsize=11, fontweight='bold')
ax1.set_title('Ring: Влияние размера сообщения', fontsize=13, fontweight='bold')
ax1.set_xticks(x)
ax1.set_xticklabels(message_sizes)
ax1.legend()
ax1.grid(True, alpha=0.3)

# ========== 2. Ring Algorithm - Масштабируемость ==========
ax2 = plt.subplot(2, 3, 2)

processes = [8, 16, 32]
time_1B = [0.020293, 0.020793, 0.020150]
time_1KB = [0.020908, 0.019870, 0.019992]
time_1MB = [0.081849, 0.172357, 0.341563]

ax2.plot(processes, time_1B, 'o-', linewidth=2, markersize=8, label='1B', color='#06A77D')
ax2.plot(processes, time_1KB, 's-', linewidth=2, markersize=8, label='1KB', color='#D62246')
ax2.plot(processes, time_1MB, '^-', linewidth=2, markersize=8, label='1MB', color='#F77F00')

ax2.set_xlabel('Количество процессов', fontsize=11, fontweight='bold')
ax2.set_ylabel('Время (сек)', fontsize=11, fontweight='bold')
ax2.set_title('Ring: Масштабируемость', fontsize=13, fontweight='bold')
ax2.legend()
ax2.grid(True, alpha=0.3)
ax2.set_xticks(processes)

# ========== 3. Broadcast - Распределение времени по процессам (1KB) ==========
ax3 = plt.subplot(2, 3, 3)

broadcast_1kb_procs = list(range(16))
broadcast_1kb_times = [0.080112, 0.000022, 0.000095, 0.000055, 0.000083, 0.000106, 
                        0.000147, 0.000117, 0.019543, 0.029387, 0.039500, 0.049529, 
                        0.050164, 0.060221, 0.070245, 0.080294]

colors_bc = ['#C73E1D' if i in [0, 15] else '#3A86FF' for i in broadcast_1kb_procs]
ax3.bar(broadcast_1kb_procs, broadcast_1kb_times, color=colors_bc, alpha=0.8)

ax3.set_xlabel('Номер процесса', fontsize=11, fontweight='bold')
ax3.set_ylabel('Время (сек)', fontsize=11, fontweight='bold')
ax3.set_title('Broadcast (1KB): Время по процессам', fontsize=13, fontweight='bold')
ax3.grid(True, alpha=0.3, axis='y')

# ========== 4. Broadcast - Сравнение 1KB vs 1MB ==========
ax4 = plt.subplot(2, 3, 4)

broadcast_1mb_times = [0.103078, 0.000215, 0.000540, 0.000752, 0.000689, 0.001104, 
                       0.001250, 0.001425, 0.027817, 0.039474, 0.048383, 0.057917, 
                       0.069524, 0.087434, 0.099491, 0.108411]

ax4.plot(broadcast_1kb_procs, broadcast_1kb_times, 'o-', linewidth=2, 
         markersize=6, label='1KB', color='#06A77D')
ax4.plot(broadcast_1kb_procs, broadcast_1mb_times, 's-', linewidth=2, 
         markersize=6, label='1MB', color='#D62246')

ax4.set_xlabel('Номер процесса', fontsize=11, fontweight='bold')
ax4.set_ylabel('Время (сек)', fontsize=11, fontweight='bold')
ax4.set_title('Broadcast: Сравнение размеров сообщений', fontsize=13, fontweight='bold')
ax4.legend()
ax4.grid(True, alpha=0.3)

# ========== 5. Gather - Распределение времени по процессам ==========
ax5 = plt.subplot(2, 3, 5)

gather_procs = list(range(16))
gather_1kb_times = [0.001207, 0.000011, 0.000008, 0.000018, 0.000010, 0.000047, 
                    0.000049, 0.000013, 0.000009, 0.001032, 0.001033, 0.001024, 
                    0.000504, 0.000497, 0.001008, 0.001043]
gather_1mb_times = [0.147555, 0.000322, 0.006236, 0.011176, 0.016045, 0.020864, 
                    0.025697, 0.030521, 0.039824, 0.051840, 0.065661, 0.079505, 
                    0.095680, 0.109318, 0.124158, 0.134653]

width = 0.35
x_gather = np.arange(len(gather_procs))
ax5.bar(x_gather - width/2, gather_1kb_times, width, label='1KB', color='#4ECDC4', alpha=0.8)
ax5.bar(x_gather + width/2, gather_1mb_times, width, label='1MB', color='#FF6B6B', alpha=0.8)

ax5.set_xlabel('Номер процесса', fontsize=11, fontweight='bold')
ax5.set_ylabel('Время (сек)', fontsize=11, fontweight='bold')
ax5.set_title('Gather: Время по процессам', fontsize=13, fontweight='bold')
ax5.legend()
ax5.grid(True, alpha=0.3, axis='y')

# ========== 6. All-to-All - Распределение времени ==========
ax6 = plt.subplot(2, 3, 6)

alltoall_procs = list(range(16))
alltoall_1kb_times = [0.004126, 0.002924, 0.003777, 0.003456, 0.002647, 0.003879, 
                      0.003308, 0.003693, 0.003998, 0.003657, 0.003631, 0.003814, 
                      0.003815, 0.004035, 0.003916, 0.004149]

ax6.bar(alltoall_procs, alltoall_1kb_times, color='#8338EC', alpha=0.7)
ax6.axhline(y=np.mean(alltoall_1kb_times), color='#FB5607', linestyle='--', 
            linewidth=2, label=f'Среднее: {np.mean(alltoall_1kb_times):.6f} сек')

ax6.set_xlabel('Номер процесса', fontsize=11, fontweight='bold')
ax6.set_ylabel('Время (сек)', fontsize=11, fontweight='bold')
ax6.set_title('All-to-All (1KB): Время по процессам', fontsize=13, fontweight='bold')
ax6.legend()
ax6.grid(True, alpha=0.3, axis='y')

plt.tight_layout()
plt.savefig('mpi_performance_analysis.png', dpi=300, bbox_inches='tight')
plt.show()

# ========== Дополнительный график: Сравнение алгоритмов ==========
fig2, ax = plt.subplots(figsize=(12, 6))

algorithms = ['Ring\n(8 proc)', 'Ring\n(16 proc)', 'Ring\n(32 proc)', 
              'Broadcast\n(макс)', 'Gather\n(макс)', 'All-to-All\n(макс)']
times_1kb = [0.020908, 0.019870, 0.019992, 0.080294, 0.001207, 0.004149]
times_1mb = [0.081849, 0.172357, 0.341563, 0.108411, 0.147555, None]

x_pos = np.arange(len(algorithms))
width = 0.35

bars1 = ax.bar(x_pos - width/2, times_1kb, width, label='1KB', color='#06A77D', alpha=0.8)
bars2 = ax.bar(x_pos[:-1] + width/2, times_1mb[:-1], width, label='1MB', color='#D62246', alpha=0.8)

ax.set_xlabel('Алгоритм коммуникации', fontsize=12, fontweight='bold')
ax.set_ylabel('Максимальное время (сек)', fontsize=12, fontweight='bold')
ax.set_title('Сравнение производительности MPI-алгоритмов', fontsize=14, fontweight='bold')
ax.set_xticks(x_pos)
ax.set_xticklabels(algorithms, fontsize=10)
ax.legend(fontsize=11)
ax.grid(True, alpha=0.3, axis='y')

# Добавление значений над столбцами
for bar in bars1:
    height = bar.get_height()
    ax.text(bar.get_x() + bar.get_width()/2., height,
            f'{height:.4f}', ha='center', va='bottom', fontsize=8)

for bar in bars2:
    height = bar.get_height()
    ax.text(bar.get_x() + bar.get_width()/2., height,
            f'{height:.4f}', ha='center', va='bottom', fontsize=8)

plt.tight_layout()
plt.savefig('mpi_algorithms_comparison.png', dpi=300, bbox_inches='tight')
plt.show()

print("Графики успешно созданы!")
print("\nОсновные выводы:")
print("1. Ring: Время растёт линейно с размером сообщения и числом процессов")
print("2. Broadcast: Неравномерное распределение нагрузки, максимум на процессах 0 и 15")
print("3. Gather: Процесс 0 (корневой) имеет максимальную нагрузку")
print("4. All-to-All: Наиболее сбалансированное распределение времени между процессами")