import matplotlib.pyplot as plt
import numpy as np

# Данные
processes = [8, 16, 32]

# Ускорение для n = 1000
speedup_1000 = [5.727, 11.967, 19.061]

# Ускорение для n = 10000
speedup_10000 = [7.296, 11.297, 22.474]

# Идеальное (линейное) ускорение
ideal_speedup = processes

# Создаем фигуру с двумя графиками
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

# График 1: n = 1000
ax1.plot(processes, speedup_1000, 'o-', linewidth=2, markersize=8, 
         label='Реальное ускорение', color='#2E86AB')
ax1.plot(processes, ideal_speedup, '--', linewidth=2, 
         label='Идеальное ускорение', color='#A23B72', alpha=0.7)
ax1.set_xlabel('Число процессов', fontsize=12)
ax1.set_ylabel('Ускорение', fontsize=12)
ax1.set_title('Ускорение для n = 1000', fontsize=14, fontweight='bold')
ax1.grid(True, alpha=0.3)
ax1.legend(fontsize=10)
ax1.set_xticks(processes)

# Добавляем значения на точки
for i, (x, y) in enumerate(zip(processes, speedup_1000)):
    ax1.annotate(f'{y:.2f}', (x, y), textcoords="offset points", 
                xytext=(0,10), ha='center', fontsize=9)

# График 2: n = 10000
ax2.plot(processes, speedup_10000, 'o-', linewidth=2, markersize=8, 
         label='Реальное ускорение', color='#2E86AB')
ax2.plot(processes, ideal_speedup, '--', linewidth=2, 
         label='Идеальное ускорение', color='#A23B72', alpha=0.7)
ax2.set_xlabel('Число процессов', fontsize=12)
ax2.set_ylabel('Ускорение', fontsize=12)
ax2.set_title('Ускорение для n = 10000', fontsize=14, fontweight='bold')
ax2.grid(True, alpha=0.3)
ax2.legend(fontsize=10)
ax2.set_xticks(processes)

# Добавляем значения на точки
for i, (x, y) in enumerate(zip(processes, speedup_10000)):
    ax2.annotate(f'{y:.2f}', (x, y), textcoords="offset points", 
                xytext=(0,10), ha='center', fontsize=9)

plt.tight_layout()
plt.savefig('speedup_comparison.png', dpi=300, bbox_inches='tight')
plt.show()

# Дополнительно: общий график для сравнения
plt.figure(figsize=(10, 6))
plt.plot(processes, speedup_1000, 'o-', linewidth=2, markersize=8, 
         label='n = 1000', color='#2E86AB')
plt.plot(processes, speedup_10000, 's-', linewidth=2, markersize=8, 
         label='n = 10000', color='#F18F01')
plt.plot(processes, ideal_speedup, '--', linewidth=2, 
         label='Идеальное ускорение', color='#A23B72', alpha=0.7)

plt.xlabel('Число процессов', fontsize=12)
plt.ylabel('Ускорение', fontsize=12)
plt.title('Сравнение ускорения для разных размеров задачи', 
          fontsize=14, fontweight='bold')
plt.grid(True, alpha=0.3)
plt.legend(fontsize=11)
plt.xticks(processes)

# Добавляем значения на точки
for x, y1, y2 in zip(processes, speedup_1000, speedup_10000):
    plt.annotate(f'{y1:.2f}', (x, y1), textcoords="offset points", 
                xytext=(0,8), ha='center', fontsize=9, color='#2E86AB')
    plt.annotate(f'{y2:.2f}', (x, y2), textcoords="offset points", 
                xytext=(0,-15), ha='center', fontsize=9, color='#F18F01')

plt.tight_layout()
plt.savefig('speedup_combined.png', dpi=300, bbox_inches='tight')
plt.show()

# Вычисляем эффективность
efficiency_1000 = [s/p * 100 for s, p in zip(speedup_1000, processes)]
efficiency_10000 = [s/p * 100 for s, p in zip(speedup_10000, processes)]

print("Эффективность параллелизации:")
print("\nn = 1000:")
for p, eff in zip(processes, efficiency_1000):
    print(f"  {p} процессов: {eff:.2f}%")

print("\nn = 10000:")
for p, eff in zip(processes, efficiency_10000):
    print(f"  {p} процессов: {eff:.2f}%")