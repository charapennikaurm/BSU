import random
from typing import Callable, Sequence, Union
import numpy as np
from functools import reduce
from operator import mul

class MonteCarloIntegralCalculator:
    def __init__(
            self,
            function: Callable,
            num_args: int = 1,
            lower_limit: Union[Sequence[float], float] = 0,
            upper_limit: Union[Sequence[float], float] = 1,
    ):
        self.fn = function
        self.num_args = num_args
        if isinstance(lower_limit, (float, int)):
            lower_limit = [lower_limit for _ in range(num_args)]
        if isinstance(upper_limit, (float, int)):
            upper_limit = [upper_limit for _ in range(num_args)]
        assert len(lower_limit) == num_args, "Length of lower_limit must match number of function arguments"
        assert len(upper_limit) == num_args, "Length of upper_limit must match number of function arguments"
        self.lower_limit = lower_limit
        self.upper_limit = upper_limit

    def __call__(self, n_iterations: int = 100):
        return self._calculate_integral_value(n_iterations=n_iterations)

    def _calculate_integral_value(self, n_iterations: int = 100):
        mean_fn_value = np.array([
            self.fn(*self._generate_values()) for _ in range(n_iterations)
            ]).mean()
        h = reduce(
            mul,
            np.array(self.upper_limit) - np.array(self.lower_limit),
            1
        )
        return h * mean_fn_value

    def _generate_values(self):
        return [self._generate_single_value(i) for i in range(self.num_args)]

    def _generate_single_value(self, i):
        return random.uniform(self.lower_limit[i], self.upper_limit[i])



