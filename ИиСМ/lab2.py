import matplotlib.pyplot as plt

from generators import  BernoulliGenerator, BinomialGenerator, GeometricGenerator, PoissonGenerator
from scipy.stats import poisson, bernoulli, binom, geom
from stats import excess, skewness, emperical_dist_function
from utils import discrete_hist as hist

if __name__ == "__main__":
    bern = BernoulliGenerator(0.16)
    hist(bern, 'Bernoulli', bernoulli, p=0.16)

    geom_gen = GeometricGenerator(0.3)
    hist(geom_gen, 'Geometric', geom, p=0.3)

    bin = BinomialGenerator(15, 0.35)
    hist(bin, 'Binomial', binom, n=15, p=0.35)

    pois = PoissonGenerator(1.0)
    hist(pois, 'Poisson', poisson, mu=1.0)
    print(f'Коэффициент эксцесса для Пуассона : {excess(pois)}')
    print(f'Коэффициент ассиметрии для Пуассона : {skewness(pois)}')
    x, y = emperical_dist_function(pois)
    y1 = poisson.cdf(x, mu=1.0)
    plt.scatter(x, y, label='Emperical')
    plt.scatter(x, y1, label='Theoretical', marker='x')
    plt.legend()
    plt.show()