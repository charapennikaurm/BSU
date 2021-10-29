import numpy as np
import scipy.special


def left_triangles(f, a, b, h):
    """
    f - интегрируемая функция
    [a, b] - отрезок интегрирования
    h - шаг квадратурной формулы
    """
    res = 0.0
    x = a
    while x < b:
        res += f(x)
        x += h
    return h * res


def trapezoid(f, a, b, h):
    """
        f - интегрируемая функция
        [a, b] - отрезок интегрирования
        h - шаг квадратурной формулы
    """
    res = 0
    left = a
    right = a + h
    while right <= b:
        res += h / 2 * (f(right) + f(left))
        left = right
        right += h
    return res


def mid_rectangles(f, a, b, h):
    """
        f - интегрируемая функция
        [a, b] - отрезок интегрирования
        h - шаг квадратурной формулы
    """
    res = 0
    x = a
    while x < b:
        res += f(x + h / 2)
        x += h
    return h * res


def runge(f, quad_formula, a, b, p, h=1.0, q=0.5, eps=10 ** (-5)):
    """
    f - интегрируемая функция
    [a, b] - отрезок интегрирования
    quad_fromula - используемая кватрадуртая формула принимающая параметры (f, a, b, h)
    h - начальный шаг квадратурной формулы
    q = h2/h1 - изменение шага квадратурной формулы на каждой итерации
    eps - необходимая погрешность
    p - порядок точности формулы
    """
    h1 = h
    h2 = h * q
    I_1 = quad_formula(f, a, b, h1)
    I_2 = quad_formula(f, a, b, h2)
    while abs((I_2 - I_1) / (1 - (h2 / h1) ** p)) > eps:
        h1 = h2
        h2 = h2 * q
        I_1 = I_2
        I_2 = quad_formula(f, a, b, h2)
    return I_1, h1


def NAST_Gauss(f, a, b, n):
    """
        f - интегрируемая функция
        [a, b] - отрезок интегрирования
        n - количество узлов квадратурной формулы НАСТ Гаусса
    """
    X = scipy.special.legendre(n).roots
    res = 0.0
    for x in X:
        res += (2 * (1 - x ** 2)) / (n ** 2 * np.polyval(scipy.special.legendre(n - 1), x) ** 2) * f(
            (a + b) / 2 + (b - a) / 2 * x)
    return (b - a) / 2 * res


def f(x):
    return np.exp(-x ** 3) * np.sin(x / 2) / (1 + x)


exact_result = 0.131787

print('Формула левых прямоугольников с использованием правила Рунге:')
I, h = runge(f, left_triangles, 0, 2, 1, h=1.0, q=1 / 2, eps=10 ** (-5))
print('Значение интеграла:', I)
print('Шаг:', h)
print('Погрешность:', abs(I - exact_result))
print()

print('Формула трапеций')
I = trapezoid(f, 0, 2, 0.00775)
print('Значение интеграла:', I)
print('Погрешность:', abs(I - exact_result))
print()

print('Формула средних прямоугольников:')
I = mid_rectangles(f, 0, 2, 0.01095)
print('Значение интеграла:', I)
print('Погрешность:', abs(I - exact_result))
print()

print('Формула НАСТ Гаусса')
I = NAST_Gauss(f, 0, 2, 5)
print('Значение интеграла:', I)
print('Погрешность:', abs(I - exact_result))
