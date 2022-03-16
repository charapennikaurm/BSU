from typing import Tuple, Optional


def euclid_ext(a: int, b: int) -> Tuple[int, int, int]:
    if a == 0:
        return b, 0, 1

    gcd, x, y = euclid_ext(b % a, a)
    return gcd, y - (b // a) * x, x


def mod_inverse(a: int, n: int) -> Optional[int]:
    """
    returns solution of
    a * x = 1 (mod n) if Solution exists, else None
    """
    g, x, _ = euclid_ext(a, n)
    if g == 1:
        return x % n
    return None
