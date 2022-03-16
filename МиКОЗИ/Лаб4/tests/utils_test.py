import numpy as np
from rsa.utils import mod_inverse
import random


def test_mod_inverse():
    for i in range(100000):
        a = random.randint(1, 2 ** 20)
        m = random.randint(a, 2 ** 30)
        x = mod_inverse(a, m)
        if np.gcd(a, m) == 1:
            assert (a * x) % m == 1
        else:
            assert x is None
