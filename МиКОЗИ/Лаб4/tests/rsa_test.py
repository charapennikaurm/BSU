import random

from rsa.rsa import RSA


def test_rsa():
    p = 1003636526287921
    q = 630114564355681
    e = 227175758417350578804323023499

    rsa = RSA(p, q, e)

    for i in range(1000):
        x = random.randint(1, 2 ** 30)
        x_enc = rsa.encrypt(x)
        x_dec = rsa.decrypt(x_enc)
        assert x_dec == x
