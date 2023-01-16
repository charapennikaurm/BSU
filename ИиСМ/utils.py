import numpy as np
from typing import Optional, Union
from generators import AbstractRandomGenerator
from scipy.stats import rv_discrete, rv_continuous
import matplotlib.pyplot as plt


def discrete_hist(
        generator: AbstractRandomGenerator,
        name: Optional[str] = None,
        correct_dist: Union[rv_discrete, None] = None,
        **dist_params
):
    generated = [generator.next_element() for _ in range(1000)]
    bins = np.arange(np.array(generated).min(), np.array(generated).max() + 2)
    plt.hist(generated, label='Emperical', rwidth=0.5, bins=bins, align='left', density=True)
    if name is not None:
        plt.title(name)
    if correct_dist is not None:
        y = correct_dist.pmf(bins,**dist_params)
        plt.plot(bins[:-1], y[:-1], marker="o", label='Theoretical')
    plt.xticks(bins)
    plt.legend()
    plt.show()


def continious_hist(
        generator: AbstractRandomGenerator,
        name: Optional[str] = None,
        correct_dist: Union[rv_continuous, None] = None,
        **dist_params
):
    generated = [generator.next_element() for _ in range(1000)]
    plt.hist(generated, label='Emperical', density=True)

    if name is not None:
        plt.title(name)
    if correct_dist is not None:
        x = np.linspace(min(generated) - 2 , max(generated) + 2, 1000)
        y = correct_dist.pdf(x, **dist_params)
        plt.plot(x, y, label='Theoretical')
    plt.legend()
    plt.show()