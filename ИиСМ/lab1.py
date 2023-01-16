import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

from generators import MultiplicativeCongruetteGenerator, MacLarenMarsagliaGenerator
from stats import moments_matching_test, covariation_test

if __name__ == "__main__":
    sns.set()
    M = 2 ** 31
    a01 = 445423
    c1 = 90474281
    gen1 = MultiplicativeCongruetteGenerator(
        a01, max([c1, M - c1]), M,
    )
    n = 30
    generated = [gen1.next_element() for _ in range(1, n + 1)]
    print(generated)
    a02 = 275803775
    c2 = 42062397
    gen2 = MultiplicativeCongruetteGenerator(
        a02, max([c2, M - c2]), M,
    )
    K = 160
    gen = MacLarenMarsagliaGenerator(gen1, gen2, K)
    moments_matching_test(gen, eps=0.05, n=20)
    covariation_test(gen, eps=0.05, n=20)
    generated = [gen.next_element() for _ in range(100000)]
    _, bins, _ = plt.hist(generated, bins=10, density=True)
    plt.plot(bins, np.ones_like(bins), lw=2, color='red')
    plt.show()
