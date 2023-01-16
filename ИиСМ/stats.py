import numpy as np

from generators import AbstractRandomGenerator
import math

from typing import List


def phi(x):
    return (1.0 + math.erf(x / math.sqrt(2.0))) / 2.0


def moments_matching_test(generator: AbstractRandomGenerator, eps: float = 0.05, n: int = 20):
    """
    Тест совпадения моментов, c уровнем значимости eps при длине генерируемой последовательности n.
    """
    generated = [generator.next_element() for _ in range(1, n + 1)]
    m = sum(generated) / n
    s2 = sum([(g - m) ** 2 for g in generated]) / (n - 1)
    xi1 = m - 0.5
    xi2 = s2 - 1 / 12
    c1 = math.sqrt(12 * n)
    c2 = (n - 1) / n * (
            0.0056 * n ** (-1) + 0.0028 * n ** (-2) - 0.0083 * n ** (-3)
    ) ** (-0.5)
    P1 = 2 * (1 - phi(c1 * abs(xi1)))
    P2 = 2 * (1 - phi(c2 * abs(xi2)))

    hypotesis = ['H0' if P1 >= eps else 'H1', 'H0' if P2 >= eps else 'H1']
    print('Тест "совпадения моментов":')
    print(
        f'Для среднего принята гипотеза {hypotesis[0]}, для стандартного отклонения гипотеза {hypotesis[1]}'
    )


def covariation_test(generator: AbstractRandomGenerator, eps: float = 0.05, n: int = 20):
    """
    Тест "ковариация", c уровнем значимости eps при длине генерируемой последовательности n.
    """
    generated = [generator.next_element() for _ in range(1, n + 1)]
    m = sum(generated) / n
    s2 = sum([(g - m) ** 2 for g in generated]) / (n - 1)
    P = 2 * (1 - phi(
        6 * math.sqrt(2 * (n - 1)) * abs(s2 - 1 / 12)
    ))
    hypotesis = 'H0' if P >= eps else 'H1'
    print('Тест "ковариация" (книга Жук):')
    print(f'Принята гипотеза {hypotesis}')


def skewness(generator: AbstractRandomGenerator) -> float:
    """
    Несмещенная оценка выборочного коэффициента ассиметрии
    """
    generated = [generator.next_element() for _ in range(100000)]
    return m3(generated) / m2(generated) ** (1.5)


def excess(generator: AbstractRandomGenerator) -> float:
    """
    Несмещенная оценка выборочного коэффициента эксцесса
    """
    generated = [generator.next_element() for _ in range(100000)]
    return m4(generated) / m2(generated) ** 2 - 3


def m2(generated: List):
    """
    Несмещённая оценка выборочного центрального момента 2-го порядка
    """
    m = len(generated)
    return m * _biased_mk(generated, k=2) / (m - 1)

def dispersion(generated: List):
    "Несмещенная оценка дисперсии"
    return m2(generated)


def mean(generated: List):
    "Несмещенная оценка математического ожидания"
    return np.array(generated).mean()

def m3(generated: List):
    """
    Несмещённая оценка выборочного центрального момента 3-го порядка
    """
    m = len(generated)
    m3_ = _biased_mk(generated, k=3)
    return (m ** 2) * m3_ / ((m - 1) * (m - 2))


def m4(generated: List):
    """
    Несмещённая оценка выборочного центрального момента 4-го порядка
    """
    m = len(generated)
    m2_ = _biased_mk(generated, 2)
    m4_ = _biased_mk(generated, 4)
    return (
                   m * (m ** 2 - 2 * m + 3) * m4_ + 3 * m * (2 * m - 3) * (m2_ ** 2)
           ) / (
                   (m - 1) * (m - 2) * (m - 3)
           )


def emperical_dist_function(generator: AbstractRandomGenerator):
    """
    Эмпирическая функция распределения
    """
    generated = np.array([generator.next_element() for _ in range(100000)])
    unique_vals = np.unique(generated)
    x = []
    y = []
    for val in unique_vals:
        x.append(val)
        y.append((generated <= val).sum())
    y = (np.array(y) / len(generated)).tolist()
    return x, y


def _biased_mk(generated: List, k: int = 1) -> float:
    """
    Выборочный момент k-го порядка
    """
    mean = np.array(generated).mean()
    generated = np.array(generated)
    mk = ((generated - mean) ** k).mean()
    return mk
