import math

import numpy as np
import random
import matplotlib.pyplot as plt
import seaborn as sns
from tqdm import tqdm
sns.set()
from matplotlib import patches


def get_markov_chain(n: int, len_: int):
    pi = np.ones((n,), dtype=np.float32) * 1 / n
    P = np.ones((n, n), dtype=np.float32) * 1 / n
    return markov_chain(pi, P, len_), pi, P


def get_observation(pi):
    x = random.random()
    st = 0.0
    i = 0
    for v in pi:
        if st <= x <= st + v:
            return i
        i += 1
        st += v


def markov_chain(pi, P, len_):
    observations = [get_observation(pi)]
    for _ in range(len_ - 1):
        current_observ = observations[-1]
        observations.append(get_observation(P[current_observ]))
    return observations


def one_chain_realization(A, f, h, markov_len):
    mc, pi, P = get_markov_chain(A.shape[0], markov_len)

    qs = []
    if pi[mc[0]] > 0:
        qs.append(h[mc[0]] / pi[mc[0]])
    else:
        qs.append(0)

    for k in range(1, markov_len):
        i = mc[k]
        i_prev = mc[k-1]
        if P[i_prev, i] > 0:
            g = A[i_prev, i] / P [i_prev, i]
        else:
            g = 0
        qs.append(qs[-1] * g)

    sum_ = 0.0
    for k in range(markov_len):
        sum_ += qs[k] * f[mc[k]]

    return sum_



def solve_one_variable(A,f, h , markov_len, num_realizations=10000):
    xis = [one_chain_realization(A, f, h, markov_len) for _ in tqdm(range(num_realizations), total=num_realizations, desc='Markov chain realizations', leave=False)]
    return np.array(xis).mean()

def solve_monte_carlo(A: np.ndarray, f: np.ndarray, markov_len):
    mc_sol = np.zeros((A.shape[0],))
    h = np.identity(A.shape[0])
    for i in range(A.shape[0]):
        mc_sol[i] = solve_one_variable(A, f, h[i], markov_len)
    return mc_sol

def r_circle(r, x_0, y_0, a1, a2):
    theta = a2 * math.pi * 2
    R = math.sqrt(a1) * r
    return R * math.cos(theta) + x_0, R * math.sin(theta) + y_0

def exp_(a):
    return -math.log(a)

def f(x):
    return math.exp(-x) * (1 + math.cos(x))


if __name__ == "__main__":
    # A = np.array([
    #     [0.7, -0.2, 0.3],
    #     [0.4, 1.3, 0.1],
    #     [0.2, 0.1, 1.1]
    # ])
    # b = np.array([3, 1, 1])
    # correct_solution = np.linalg.solve(A, b)
    # markov_lens = np.linspace(10, 100, 10, dtype=np.int32)
    # A = np.identity(A.shape[0]) - A
    # f = b
    # print(A)
    # print(np.linalg.norm(A))
    # solutions = np.array([solve_monte_carlo(A, f, ml) for ml in tqdm(markov_lens, desc='Length of markov chain', leave=False)])
    # r = [np.linalg.norm(sol - correct_solution) for sol in solutions]
    # print(f'Точное решение: {correct_solution}')
    # print(f'Решение методом Монте Карло: {solutions[np.argmin(r)]}')
    # plt.plot(markov_lens, r)
    # plt.xlabel('Длина цепи Маркова')
    # plt.ylabel('Невязка решения')
    # plt.show()
    a = [random.random() for _ in range(10000)]
    xi = [exp_(v) for v in a]
    f_ = [f(x) for x in xi]
    print(sum(f_) / len(f_))


