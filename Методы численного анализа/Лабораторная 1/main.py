import math


def f(x):
    return 2 * x + math.log10(2 * x + 3) - 1


def df(x):
    return 2 / ((2 * x + 3) * math.log(10)) + 2


def d2f(x):
    return -4 / (((2 * x + 3) ** 2) * math.log(10))



def phi(x):
    return x - 1 / 2.25547 * f(x)


def mpi(x0, func, eps):
    iterations_number = 1
    x1 = func(x0)
    delta = abs(x1 - x0)
    while delta > eps:
        x0 = x1
        x1 = func(x0)
        delta = abs(x1 - x0)
        iterations_number += 1
    return x1, iterations_number



def steffens(x0, func, eps):
    iterations_number = 1
    x1 = (x0 * func(func(x0)) - (func(x0) ** 2)) / (func(func(x0)) - 2 * func(x0) + x0)
    delta = abs(x1 - x0)
    while delta > eps:
        x0 = x1
        x1 = func(x0)
        delta = abs(x1 - x0)
        iterations_number += 1
    return x1, iterations_number


def newton(x0, func, dfunc, eps):
    iterations_number = 1
    x1 = x0 - func(x0) / dfunc(x0)
    delta = abs(x1 - x0)
    while delta > eps:
        x0 = x1
        x1 = x0 - func(x0) / dfunc(x0)
        delta = abs(x1 - x0)
        iterations_number += 1
    return x1, iterations_number


def secant(x0, x1, func, eps):
    iterations_number = 1
    x2 = x1 - func(x1) * (x1 - x0) / (f(x1) - f(x0))
    delta = abs(x2 - x1)
    while delta > eps:
        x0 = x1
        x1 = x2
        x2 = x1 - func(x1) * (x1 - x0) / (f(x1) - f(x0))
        delta = abs(x2 - x1)
        iterations_number += 1
    return x1, iterations_number

