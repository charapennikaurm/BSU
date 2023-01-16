import matplotlib.pyplot as plt

from generators import (
    NormalGenerator, LogNormalGenerator, ExponentialGenerator, LaplaceGenerator, CauchyGenerator
)
from utils import continious_hist as hist
from stats import mean, dispersion
import math
from tabulate import tabulate


if __name__ == '__main__':
    E = []
    D = []
    Et = []
    Dt = []
    titles = []

    loc = 2
    scale = 4
    n = NormalGenerator(loc, scale**2)
    title = f'Normal({loc}, {scale**2})'
    hist(
        n, title
    )
    generated = [n() for _ in range(10000)]
    E.append(mean(generated))
    D.append(dispersion(generated))
    Et.append(loc)
    Dt.append(scale**2)
    titles.append(title)

    a = 0.25
    title = f'Exponential({a})'
    exp = ExponentialGenerator(a)
    hist(
        exp, title,
    )
    generated = [exp() for _ in range(10000)]
    E.append(mean(generated))
    D.append(dispersion(generated))
    Et.append(1/a)
    Dt.append(1/a**2)
    titles.append(title)

    a = 1.5
    title = f'Laplace({a})'
    lapl = LaplaceGenerator(a)
    hist(
        lapl, title
    )
    generated = [lapl() for _ in range(10000)]
    E.append(mean(generated))
    D.append(dispersion(generated))
    Et.append(0)
    Dt.append(2 / a**2)
    titles.append(title)

    a = 1
    b = 2
    title = f'Cauchy({a}, {b})'
    cauchy = CauchyGenerator(a, b)
    generated = [cauchy() for _ in range(10000)]
    E.append(mean(generated))
    D.append(dispersion(generated))
    Et.append(None)
    Dt.append(None)
    titles.append(title)
    generated = [g for g in generated if -10 < g < 10]
    plt.hist(generated, label='Emperical')
    plt.title(title)
    plt.show()

    m = -1
    s2 = 2
    title = f'LogNormal({m}, {s2})'
    ln = LogNormalGenerator(m, s2)
    hist(
        ln, title
    )
    generated = [ln() for _ in range(100000)]
    e = math.exp(m + s2 / 2)
    d = math.exp(2 * m + s2) * (math.exp(s2) - 1)
    E.append(mean(generated))
    D.append(dispersion(generated))
    Et.append(e)
    Dt.append(d)
    titles.append(title)

    data = {
        "Распределение": titles,
        "Мат. ожидание (теоретически)": Et,
        "Мат. ожидание (оценка)": E,
        "Диспресия (теоретически)": Dt,
        "Диспресия (оценка)": D,
    }

    print(tabulate(
        data, headers="keys", missingval="Не определено", tablefmt="simple_grid", floatfmt=".4f", numalign='center'
    ))