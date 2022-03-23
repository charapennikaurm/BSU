from typing import Optional, Tuple


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


def pow_(x: int, n: int, mod: int):
    if mod < 1:
        raise ValueError(f"Expected n to be > 1, but got {n}")

    if n == 0:
        return 1
    if n % 2 == 0:
        return pow_(((x % mod) * (x % mod)) % mod, n // 2, mod)
    else:
        return ((x % mod) * pow_((x % mod), n - 1, mod)) % mod
