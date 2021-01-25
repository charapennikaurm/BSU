import numpy as np
from math import fabs, sqrt, ceil, log10, log
from sympy import solve, symbols


def sign(a):
    if a > 0:
        return 1
    elif a < 0:
        return -1
    else:
        return 0


def find_max_col_element(A, col, start_row, n):
    max_col_element = fabs(A[start_row][col])
    row = start_row
    for i in range(start_row + 1, n):
        if fabs(A[i][col]) > max_col_element:
            max_col_element = fabs(A[i][col])
            row = i
    return row


def solve_system(A, b):
    n = A.shape[0]
    system_matrix = np.array(np.hstack((A, b)))
    # print("Исходная матрица системы: ")
    # print(system_matrix)
    det = 1.0
    # прямой ход
    for i in range(n):
        row = find_max_col_element(system_matrix, i, i, n)
        system_matrix[[i, row]] = system_matrix[[row, i]]
        main_element = system_matrix[i][i]
        det *= main_element
        for j in range(i, n + 1):
            system_matrix[i][j] /= main_element
        for k in range(i + 1, n):
            for j in range(i + 1, n + 1):
                system_matrix[k][j] -= system_matrix[i][j] * system_matrix[k][i]
            system_matrix[k][i] = 0
    x = np.zeros(b.shape)
    # обратный ход
    for i in reversed(range(n)):
        x[i][0] = system_matrix[i][n]
        for j in reversed(range(i + 1, n)):
            x[i][0] -= system_matrix[i][j] * x[j][0]
    return x, det


# Метод Гаусса-Жордано
def find_inverse_matrix(A):
    n = A.shape[0]
    E = np.eye(n)
    system_matrix = np.array(np.hstack((A, E)))
    # прямой ход
    for i in range(n):
        main_element = system_matrix[i][i]
        for j in range(i, 2 * n):
            system_matrix[i][j] /= main_element
        for k in range(i + 1, n):
            for j in range(i + 1, 2 * n):
                system_matrix[k][j] -= system_matrix[i][j] * system_matrix[k][i]
            system_matrix[k][i] = 0.0
    # обратный ход
    for i in reversed(range(n)):
        for k in reversed(range(i)):
            factor = system_matrix[k][i]
            for j in range(i, 2 * n):
                system_matrix[k][j] -= system_matrix[i][j] * factor
    inv = system_matrix[:, range(n, 2 * n)]
    return inv


# Метод Гаусса
def inverse(A):
    n = A.shape[0]
    inv = np.zeros(A.shape)
    for i in range(n):
        b = np.zeros([n, 1])
        b[i][0] = 1
        x = solve_system(A, b)[0]
        inv[:, i] = x[:, 0]
    return inv


def sqrt_system_solve(A, b):
    n = A.shape[0]
    s = np.zeros(A.shape)
    d = np.zeros(A.shape)
    a = np.array(np.hstack((A, b)))
    print("Исходная матрица системы:")
    print(a)
    # a = np.dot(np.transpose(A), a)
    print("Матрица системы после умножения на A^T: ")
    print(a)
    s[0][0] = sqrt(a[0][0])
    det = s[0][0]
    d[0][0] = sign(a[0][0])
    for j in range(1, n):
        s[0][j] = a[0][j] / s[0][0]
    for i in range(1, n):
        s[i][i] = a[i][i]
        d[i][i] = a[i][i]
        for k in range(i):
            s[i][i] -= (s[k][i] ** 2 * d[k][k])
            d[i][i] -= (s[k][i] ** 2 * d[k][k])
        s[i][i] = sqrt(s[i][i])
        det *= s[i][i]
        d[i][i] = sign(d[i][i])
        det *= d[i][i]
        for j in range(i + 1, n):
            s[i][j] = a[i][j]
            for k in range(i):
                s[i][j] -= s[k][i] * s[k][j] * d[k][k]
            s[i][j] /= s[i][i]
    print("Определитель матрицы А:")
    print(det)
    print("Матрица S:")
    print(s)
    print("Матрица D:")
    print(d)
    print("S^T * D * S")
    print(np.dot(np.transpose(s), np.dot(d, s)))
    y = np.zeros(b.shape)
    g = np.dot(np.transpose(s), d)
    y[0][0] = a[0][n] / s[0][0]
    for i in range(1, n):
        y[i][0] = a[i][n]
        for k in range(i):
            y[i][0] -= g[i][k] * y[k][0]
        y[i][0] /= s[i][i]
    print("Вектор y:")
    print(y.tolist())
    x = np.zeros(b.shape)
    x[n - 1][0] = y[n - 1][0] / s[n - 1][n - 1]
    for i in reversed(range(n - 1)):
        x[i][0] = y[i][0]
        for k in range(i + 1, n):
            x[i][0] -= s[i][k] * x[k][0]
        x[i][0] /= s[i][i]
    print("Вектор x:")
    print(x.tolist())
    print("Невязка:")
    print((np.dot(A, x) - b).tolist())


def jacobi(A, b, eps):
    n = A.shape[0]
    B = np.zeros(A.shape)
    for i in range(n):
        b[i][0] /= A[i][i]
        for j in range(n):
            if i != j:
                B[i][j] = -A[i][j] / A[i][i]
    x_new = b
    x_old = np.zeros(b.shape)
    B_norm = np.linalg.norm(B)
    b_norm = np.linalg.norm(b)
    print("||B|| = ", B_norm, sep=" ")
    print("||b|| = ", b_norm, sep=" ")
    real_iterations = 0
    aprior_iterations = ceil(((log10(eps) + log10(1 - B_norm) - log10(b_norm)) / log10(B_norm)) - 1)
    while np.linalg.norm(x_old - x_new) >= eps:
        x_old = x_new
        x_new = np.dot(B, x_old) + b
        real_iterations += 1
    print("Априорное число итераций:", aprior_iterations, sep=" ")
    print("Реальное число итераций:", real_iterations, sep=" ")
    return x_new


def gauss_seidel(A, b, eps):
    n = A.shape[0]
    H = np.zeros(A.shape)
    F = np.zeros(A.shape)
    for i in range(n):
        b[i][0] /= A[i][i]
        for j in range(n):
            if i > j:
                H[i][j] = -A[i][j] / A[i][i]
            if j > i:
                F[i][j] = -A[i][j] / A[i][i]
    x_new = b
    x_old = np.zeros(b.shape)
    real_iterations = 0
    while np.linalg.norm(x_old - x_new) >= eps:
        x_old = x_new
        x_new = np.dot(H, x_new) + np.dot(F, x_old) + b
        real_iterations += 1
    print("Реальное число итераций:", real_iterations, sep=" ")
    return x_new


def danilevsky(A):
    n = A.shape[0]
    print('Матрица А: ')
    print(A)
    F = A
    S = np.identity(n)
    for i in reversed(range(1, n)):
        M_inv = np.identity(n)
        M_inv[i - 1, :] = F[i, :]
        F = np.dot(M_inv, F)
        M = np.linalg.inv(M_inv)
        F = np.dot(F, M)
        S = np.dot(S, M)
        print('M' + str(n - i))
        print(M)
        print('M_inv' + str(n - i))
        print(M_inv)
        print(F)
    print('Форма Фробениуса:')
    print(F)
    print('Матрица S: ')
    print(S)
    c = F[0, :]
    x = symbols('x')
    lambdas = solve(x ** 5 - c[0] * x ** 4 - c[1] * x ** 3 - c[2] * x ** 2 - c[3] * x - c[4], x)
    print('Собственный многочлен: ')
    print('x^5 -(', c[0], ')x^4 -(', c[1], ')x^3 -(', c[2], ')x^2 -(', c[3], ')x -(', c[4], ')', sep='')
    print('Собственные значения: ')
    print(lambdas)
    print('Собственные значения и соотв. собственные векторы: ')
    for i in range(n):
        l = lambdas[i]
        print(l, ": ", sep="", end="")
        y = [l ** (n - k - 1) for k in range(n)]
        x = np.dot(S, y)
        print(x)


def krylov_vectors(A, c):
    n = A.shape[0]
    C = np.identity(n)
    print('c(0)')
    print('c')
    for i in range(n):
        for k in range(n):
            C[k][n - i - 1] = c[k][0]
        c1 = np.dot(A, c)
        c = c1
        print('c(' + str(i + 1) + '):')
        print(c)
    print('Система:')
    print(np.array(np.hstack((C, c))))
    print('Вектор коэффициентов')
    print(np.linalg.solve(C, c))


def find_max_nondiag_element(A):
    n = A.shape[0]
    col = 1
    row = 0
    max = fabs(A[0][1])
    for i in range(n):
        for j in range(n):
            if i != j:
                if fabs(A[i][j]) > max:
                    max = fabs(A[i][j])
                    row = i
                    col = j
    return row, col


def build_rotation_matrix(n, i, j, cos, sin):
    T = np.identity(n)
    T[i][i] = cos
    T[i][j] = -sin
    T[j][j] = cos
    T[j][i] = sin
    return T


def rotation_eigvals(A, eps):
    n = A.shape[0]
    a = np.array(A - np.diag(np.diagonal(A)))
    error = (np.linalg.norm(a)) ** 2
    while error > eps:
        i = find_max_nondiag_element(A)[0]
        j = find_max_nondiag_element(A)[1]
        print(A[i][j], i, j, sep=" ")
        u = A[i][j] * 2 / (A[i][i] - A[j][j])
        print('tg = ', u)
        cos = sqrt(0.5 * (1 + 1 / sqrt(u ** 2 + 1)))
        print('cos = ', cos)
        sin = sign(u) * sqrt(0.5 * (1 - 1 / sqrt(u ** 2 + 1)))
        print('sin = ', sin)
        T = build_rotation_matrix(n, i, j, cos, sin)
        print('T: ')
        print(T)
        A = np.dot(np.transpose(T), A)
        A = np.dot(A, T)
        print('A: ')
        print(A)
        a = np.array(A - np.diag(np.diagonal(A)))
        error = (np.linalg.norm(a)) ** 2


def stepennoy(A, y0, eps):
    number_of_iteratons = 0
    print('Исходная матрица А:')
    print(A)
    print('Матрица после умножения А^T справа:')
    A = np.dot(A, A.transpose())
    print(A)
    error = eps
    l0 = 0
    while error >= eps:
        y0 = y0 / np.linalg.norm(y0)
        y = np.dot(A, y0)
        l = y[0] / y0[0]
        y0 = y
        error = fabs(l - l0)
        l0 = l
        number_of_iteratons += 1
    print('Максимальное по модулю собственное значение:')
    print(l0)
    y0 = y0 / np.linalg.norm(y0)
    print('Собственный вектор соответсвующий максимальному по модулю собственному значению: ')
    print(y0)
    print('Число итераций: ', number_of_iteratons)
    r = np.dot(A, y0) - l0 * y0
    print('Невязка: ', r)
    print('Собственные значения через встроенную функцию:')
    print(np.linalg.eigvals(A))

