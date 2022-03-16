from rsa.utils import mod_inverse


class RSA:
    def __init__(self,
                 p: int,
                 q: int,
                 e: int,
                 ):
        self.n = p * q
        self.e = e
        self.d = self._generate_private_key(p, q)

    def _generate_private_key(self, p: int, q: int) -> int:
        phi = (p - 1) * (q - 1)
        return mod_inverse(self.e, phi)

    def encrypt(self, message: int) -> int:
        return pow(message, self.e, self.n)

    def decrypt(self, message: int) -> int:
        return pow(message, self.d, self.n)