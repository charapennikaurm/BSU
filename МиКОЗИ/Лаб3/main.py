import numpy as np
from copy import deepcopy
from typing import Tuple


class RSLOS:
    def __init__(self,
                 a: np.ndarray,
                 c: np.ndarray,
                 ):
        assert a.shape == c.shape, f'Expected a and c to be of the same shape, but got a: {a.shape}, c: {c.shape}'

        self.a = a
        self.c = c
        self.b = deepcopy(a)

    def external_output(self) -> int:  # внешний вывод
        return self.b[0]

    def change_internal_state(self) -> None:
        r = (self.c * self.b).sum() % 2

        for i in range(self.b.shape[0] - 1):
            self.b[i] = self.b[i + 1]
        self.b[-1] = r

    def reset_state(self) -> None:
        self.b = deepcopy(self.a)

    def generate_sample(self, len_: int) -> np.ndarray:
        sample = np.zeros((len_,))
        for i in range(len_):
            sample[i] = self.external_output()
            self.change_internal_state()
        return sample


class GepheGenerator:
    def __init__(self,
                 rslos_1: RSLOS,
                 rslos_2: RSLOS,
                 rslos_3: RSLOS):
        self.rslos_1 = rslos_1
        self.rslos_2 = rslos_2
        self.rslos_3 = rslos_3

    def generate_sample(self, len_: int) -> np.ndarray:
        x1 = self.rslos_1.generate_sample(len_)
        x2 = self.rslos_2.generate_sample(len_)
        x3 = self.rslos_3.generate_sample(len_)

        # return np.logical_xor((x1*x2), np.logical_xor((x2*x3), x3))
        return np.logical_xor((x1 * x2), ((np.logical_xor(x1, 1)) * x3))

    def reset_state(self) -> None:
        self.rslos_1.reset_state()
        self.rslos_2.reset_state()
        self.rslos_3.reset_state()


def count_0_and_1(sample: np.ndarray) -> Tuple[int, int]:
    ones = sample.sum()
    zeros = sample.size - ones
    return zeros, ones


def r_i(sample: np.ndarray, i):
    res = 0
    for j in range(sample.size - i):
        res += (-1) ** (sample[j] ^ sample[j + i])
    return res


a_1 = np.array([int(i) for i in "10010"])
c_1 = np.array([int(i) for i in "10011"])
a_2 = np.array([int(i) for i in "0000001"])
c_2 = np.array([int(i) for i in "0110011"])
a_3 = np.array([int(i) for i in "00100101"])
c_3 = np.array([int(i) for i in "11110011"])

rslos_1 = RSLOS(a_1, c_1)
rslos_2 = RSLOS(a_2, c_2)
rslos_3 = RSLOS(a_3, c_3)

gen = GepheGenerator(rslos_1, rslos_2, rslos_3)
gephe_sample = gen.generate_sample(10000)

print(count_0_and_1(gephe_sample))
for i in range(1, 6):
    print(f'r_{i}: {r_i(gephe_sample, i)}')
