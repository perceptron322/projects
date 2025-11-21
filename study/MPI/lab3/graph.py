import matplotlib.pyplot as plt
import numpy as np

# Данные для n = 28000
processes_28000 = [8, 16, 32, 64]
speedup_28000 = [8.14, 14.26, 20.57, 31.41]

# Данные для n = 45000
processes_45000 = [8, 16, 32, 64]
speedup_45000 = [8.11, 13.46, 27.38, 36.53]

# Идеальное ускорение (линейное)
ideal_speedup = processes_28000  # [8, 16, 32, 64]

# Создание фигуры с двумя графиками
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))

# ============ График 1: Сравнение двух размеров задачи ============
ax1.plot(processes_28000, speedup_28000, 'bo-', label='n = 28000', 
         linewidth=2.5, markersize=10)
ax1.plot(processes_45000, speedup_45000, 'go-', label='n = 45000', 
         linewidth=2.5, markersize=10)
ax1.plot(processes_28000, ideal_speedup, 'r--', label='Идеальное ускорение', 
         linewidth=2, alpha=0.7)

ax1.set_xlabel('Число процессов (p)', fontsize=14, fontweight='bold')
ax1.set_ylabel('Ускорение S(p)', fontsize=14, fontweight='bold')
ax1.set_title('Зависимость ускорения от числа процессов\nдля разных размеров задачи', 
              fontsize=15, fontweight='bold')
ax1.grid(True, alpha=0.3, linestyle='--')
ax1.legend(fontsize=12, loc='upper left')
ax1.set_xticks(processes_28000)

# Добавление значений на точки
for i, (p, s) in enumerate(zip(processes_28000, speedup_28000)):
    ax1.annotate(f'{s:.2f}', (p, s), textcoords="offset points", 
                xytext=(0, 10), ha='center', fontsize=9, color='blue')
for i, (p, s) in enumerate(zip(processes_45000, speedup_45000)):
    ax1.annotate(f'{s:.2f}', (p, s), textcoords="offset points", 
                xytext=(0, -15), ha='center', fontsize=9, color='green')

# ============ График 2: Эффективность ============
efficiency_28000 = [(s / p) * 100 for s, p in zip(speedup_28000, processes_28000)]
efficiency_45000 = [(s / p) * 100 for s, p in zip(speedup_45000, processes_45000)]

ax2.plot(processes_28000, efficiency_28000, 'bo-', label='n = 28000', 
         linewidth=2.5, markersize=10)
ax2.plot(processes_45000, efficiency_45000, 'go-', label='n = 45000', 
         linewidth=2.5, markersize=10)
ax2.axhline(y=100, color='r', linestyle='--', linewidth=2, 
           label='Идеальная эффективность (100%)', alpha=0.7)

ax2.set_xlabel('Число процессов (p)', fontsize=14, fontweight='bold')
ax2.set_ylabel('Эффективность E(p), %', fontsize=14, fontweight='bold')
ax2.set_title('Зависимость эффективности от числа процессов\nдля разных размеров задачи', 
              fontsize=15, fontweight='bold')
ax2.grid(True, alpha=0.3, linestyle='--')
ax2.legend(fontsize=12, loc='upper right')
ax2.set_xticks(processes_28000)
ax2.set_ylim([0, 110])

# Добавление значений на точки
for i, (p, e) in enumerate(zip(processes_28000, efficiency_28000)):
    ax2.annotate(f'{e:.1f}%', (p, e), textcoords="offset points", 
                xytext=(0, 10), ha='center', fontsize=9, color='blue')
for i, (p, e) in enumerate(zip(processes_45000, efficiency_45000)):
    ax2.annotate(f'{e:.1f}%', (p, e), textcoords="offset points", 
                xytext=(0, -15), ha='center', fontsize=9, color='green')

plt.tight_layout()
plt.savefig('speedup_comparison.png', dpi=300, bbox_inches='tight')
print("График сохранен в файл 'speedup_comparison.png'")

# ============ Вывод таблицы с результатами ============
print("\n" + "="*70)
print("РЕЗУЛЬТАТЫ АНАЛИЗА ПРОИЗВОДИТЕЛЬНОСТИ")
print("="*70)

print("\nДанные для n = 28000:")
print("-" * 70)
print(f"{'Процессы':>12} | {'Ускорение':>12} | {'Эффективность':>15}")
print("-" * 70)
for p, s, e in zip(processes_28000, speedup_28000, efficiency_28000):
    print(f"{p:>12} | {s:>12.2f} | {e:>14.2f}%")

print("\nДанные для n = 45000:")
print("-" * 70)
print(f"{'Процессы':>12} | {'Ускорение':>12} | {'Эффективность':>15}")
print("-" * 70)
for p, s, e in zip(processes_45000, speedup_45000, efficiency_45000):
    print(f"{p:>12} | {s:>12.2f} | {e:>14.2f}%")

print("\n" + "="*70)
print("АНАЛИЗ РЕЗУЛЬТАТОВ")
print("="*70)

# Анализ для n = 28000
print("\nДля n = 28000:")
print(f"  • Максимальное ускорение: {max(speedup_28000):.2f}x на {processes_28000[speedup_28000.index(max(speedup_28000))]} процессах")
print(f"  • Эффективность на 64 процессах: {efficiency_28000[-1]:.2f}%")
print(f"  • Характер зависимости: сублинейная (ускорение растет медленнее числа процессов)")

# Анализ для n = 45000
print("\nДля n = 45000:")
print(f"  • Максимальное ускорение: {max(speedup_45000):.2f}x на {processes_45000[speedup_45000.index(max(speedup_45000))]} процессах")
print(f"  • Эффективность на 64 процессах: {efficiency_45000[-1]:.2f}%")
print(f"  • Характер зависимости: сублинейная, но лучше масштабируется на больших p")

# Сравнение
print("\nСравнение:")
if efficiency_45000[-1] > efficiency_28000[-1]:
    print(f"  • При увеличении размера задачи (n) эффективность на 64 процессах")
    print(f"    улучшается с {efficiency_28000[-1]:.1f}% до {efficiency_45000[-1]:.1f}%")
    print(f"  • Большая задача (n=45000) лучше масштабируется")
else:
    print(f"  • Меньшая задача (n=28000) показывает лучшую эффективность")

print("\nВыводы:")
print("  • Оба варианта показывают хорошую масштабируемость до 8-16 процессов")
print("  • На 32-64 процессах начинают проявляться накладные расходы")
print(f"  • Эффективность падает, но остается приемлемой (>{min(efficiency_28000[-1], efficiency_45000[-1]):.0f}%)")
print("="*70)

plt.show()