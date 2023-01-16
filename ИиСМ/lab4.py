import math
import random
import matplotlib.pyplot as plt
import numpy as np
from tqdm.auto import tqdm

def f1(x):
    return (
        abs(math.sin(x)) * math.atan(abs(x) ** 3)
    )


def f2(x, y):
    return math.sqrt(y + math.sin(x) ** 2) / math.exp(-x*y)


def task1(n_its):
    lower = -math.sqrt(math.e) * math.pi
    upper = math.sqrt(math.pi) * math.e
    fn = [
        f1(x) for x in [random.uniform(lower, upper) for _ in range(n_its)]
    ]
    return (upper - lower) * sum(fn) / len(fn)


def task2(n_its):
    x_lower = -2
    x_upper = 2
    y_upper = 4
    Xs = []
    Ys = []
    while(len(Xs) != n_its):
        x = random.uniform(x_lower, x_upper)
        y = random.uniform(0, y_upper)
        if y >= x**2:
            Ys.append(y)
            Xs.append(x)
    fn = [f2(x, y) for x, y in zip(Xs, Ys)]
    mean_fn = np.array(fn).mean()
    S = 32 / 3
    return S * mean_fn


#Task 1
iters = np.linspace(100, 10**5, 100).astype(np.int32)
vals = np.array([task1(nit) for nit in tqdm(iters)])
theor_val = 8.39794
errors = abs(theor_val - vals)
plt.plot(iters, errors)
plt.xlabel('Number of iterations')
plt.ylabel('Absolute error')
plt.title('Task 1')
plt.show()
print(f'Calculated value: {task1(10**6):.5f}')
print(f'Theoretical value: {theor_val:.5f}')

# Task 2
iters = np.linspace(100, 10**5, 100).astype(np.int32)
vals = np.array([task2(nit) for nit in tqdm(iters)])
theor_val = 618.542
errors = abs(theor_val - vals)
plt.plot(iters, errors)
plt.xlabel('Number of iterations')
plt.ylabel('Absolute error')
plt.title('Task 2')
plt.show()
print(f'Calculated value: {task2(10**6):.5f}')
print(f'Theoretical value: {theor_val:.5f}')