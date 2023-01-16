from abc import abstractmethod
import math
import random


# LAB 1

class AbstractRandomGenerator:
    """
    Base random number generator.
    """

    @abstractmethod
    def next_element(self):
        pass

    @abstractmethod
    def reset(self):
        pass

    def generate_Kth_element(self, k: int):
        """
        Get kth element of random generator.
        Resets state before and after getting element.
        """
        self.reset()
        el = 0
        for _ in range(1, k + 1):
            el = self.next_element()
        self.reset()
        return el

    def __call__(self):
        return self.next_element()


# БСВ
class ConstantGenerator(AbstractRandomGenerator):
    """
    Generates constant(for test purposes).
    """

    def __init__(self, c: float = 0.5):
        self.c = c

    def next_element(self):
        return self.c

    def reset(self):
        pass


class MultiplicativeCongruetteGenerator(AbstractRandomGenerator):
    def __init__(
            self,
            a0: int,
            b: int,
            M: int,
    ):
        if b >= M:
            raise ValueError(f'Expected b to be less then M, but got b={b}, M={M}')
        if a0 % 2 == 0:
            raise ValueError(f'Expected a0 to be odd number, but got a0={a0}')
        self.a0 = a0
        self.M = M
        self.b = b
        self.prev = self.a0

    def next_element(self):
        z = self.b * self.prev
        self.prev = z - self.M * int(z / self.M)

        return self.prev / self.M

    def reset(self):
        self.prev = self.a0


class MacLarenMarsagliaGenerator(AbstractRandomGenerator):
    def __init__(
            self,
            gen1: AbstractRandomGenerator,
            gen2: AbstractRandomGenerator,
            K: int,
    ):
        self.gen1 = gen1
        self.gen2 = gen2
        self.K = K
        self.V = [self.gen1.next_element() for _ in range(K)]

    def next_element(self):
        s = int(self.gen2.next_element() * self.K)
        val = self.V[s]
        self.V[s] = self.gen1.next_element()
        return val

    def reset(self):
        self.gen1.reset()
        self.gen2.reset()


# ДСВ

class BernoulliGenerator(AbstractRandomGenerator):
    def __init__(self, p: float):
        self.p = p

    def reset(self):
        super().reset()

    def next_element(self):
        a = random.random()
        return 1 if a <= self.p else 0


class GeometricGenerator(AbstractRandomGenerator):
    def __init__(self, p):
        self.q = 1.0 - p

    def next_element(self):
        return math.ceil(
            math.log(random.random()) / math.log(self.q)
        )

    def reset(self):
        super().reset()


class BinomialGenerator(AbstractRandomGenerator):
    def __init__(self, m: int, p: float):
        self.m = m
        self.bern = BernoulliGenerator(p)

    def next_element(self):
        x = 0
        for _ in range(self.m):
            x += self.bern.next_element()
        return x

    def reset(self):
        super().reset()


class PoissonGenerator(AbstractRandomGenerator):
    def __init__(self, l: float):
        self.l = l

    def next_element(self):
        p = math.exp(-self.l)
        x = 0
        r = random.random()
        r = r - p
        while r >= 0:
            x = x + 1
            p = p * self.l / x
            r = r - p
        return x

    def reset(self):
        super().reset()


# НСВ

class NormalGenerator(AbstractRandomGenerator):
    def __init__(self, m: float, s2: float):
        self.m = m
        self.s2 = s2
        self._next = None

    def next_element(self):
        if self._next is not None:
            res = self._next
            self._next = None
        else:
            a1 = random.random()
            a2 = random.random()
            self._next = math.sqrt(-2 * math.log(a1)) * math.cos(math.pi * 2 * a2)
            res = math.sqrt(-2 * math.log(a1)) * math.sin(math.pi * 2 * a2)

        res = self.m + res * math.sqrt(self.s2)
        return res


    def reset(self):
        self.a1 = None
        self.a2 = None


class StandardNormalGenerator(AbstractRandomGenerator):
    def __init__(self):
        self.gen = NormalGenerator(0, 1)

    def next_element(self):
        return self.gen()

    def reset(self):
        return self.gen.reset()


class LogNormalGenerator(AbstractRandomGenerator):
    def __init__(self, m: float, s2: float):
        self.gen = NormalGenerator(m, s2)

    def next_element(self):
        return math.exp(self.gen())

    def reset(self):
        self.gen.reset()


class LaplaceGenerator(AbstractRandomGenerator):
    def __init__(self, a: float):
        self.a = a

    def next_element(self):
        x = random.random()
        if x < 0.5:
            res = 1 / self.a * math.log(2 * x)
        else:
            res = - 1 / self.a * math.log(2 * (1 - x))
        return res

    def reset(self):
        pass


class ExponentialGenerator(AbstractRandomGenerator):
    def __init__(self, a: float):
        self.a = a

    def next_element(self):
        x = random.random()
        return - 1/ self.a * math.log(x)

    def reset(self):
        pass


class CauchyGenerator(AbstractRandomGenerator):
    def __init__(self, a: float, b: float):
        self.a = a
        self.b = b

    def next_element(self):
        x = random.random()
        res = self.a + self.b * math.tan(math.pi * (x - 0.5))
        return res

    def reset(self):
        pass

