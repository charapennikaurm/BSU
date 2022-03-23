from hashlib import sha256
from random import randrange
from typing import Tuple

from sympy import isprime

from utils import mod_inverse, pow_


def gen(q: int) -> Tuple[Tuple[int, int, int], int, int]:
    if not isprime(q):
        raise ValueError(f"Expected q to be prime, but {q} is not prime")

    while True:
        r = randrange(0, 4 * (q + 1), 2)
        p = q * r + 1
        if pow_(2, q * r, p) != 1 or pow_(2, r, p) == 1:
            continue
        while True:
            x = randrange(0, p)
            g = pow_(x, r, p)
            if g == 1:
                continue
            else:
                break

        d = randrange(0, q)
        e = pow_(g, d, p)
        break
    digital_signature_params = (p, q, g)
    open_key = e
    personal_key = d
    return digital_signature_params, open_key, personal_key


def sign(
    signature_params: Tuple[int, int, int], personal_key: int, message: str
) -> Tuple[int, int]:
    p, q, g = signature_params
    d = personal_key
    if not (0 <= personal_key <= q):
        raise ValueError()
    m = int(sha256(bytes(message, encoding="utf-8")).hexdigest(), 16)
    k = randrange(1, q)
    r = pow_(g, k, p)
    s = (mod_inverse(k, q) * (m - d * r)) % q
    return r, s


def verify(
    signature_params: Tuple[int, int, int],
    open_key: int,
    message: str,
    signature: Tuple[int, int],
) -> bool:
    p, q, g = signature_params
    r, s = signature
    e = open_key
    if not (0 <= open_key < p):
        raise ValueError()
    m = int(sha256(bytes(message, encoding="utf-8")).hexdigest(), 16)
    if (pow_(e, r, p) * pow_(r, s, p)) % p == pow_(g, m, p):
        return True
    return False


def main():
    signature_params, open_key, personal_key = None, None, None
    while True:
        available_operations = ["gen", "sign", "verify", "exit"]
        operation = input(
            "Enter gen for keys signature, sign for signing message, verify to verify signature authenticity"
            + "exit to exit the program: "
        )
        if operation not in available_operations:
            print(f"Unknown operation, use one of {available_operations}")
            continue
        if operation == "exit":
            return

        if operation == "gen":
            q = int(input("Enter q: "))
            signature_params, open_key, personal_key = gen(q)
            print("Keys are generated")
            continue

        if operation == "sign":
            if signature_params is None:
                print("Keys need to be generated first, use gen command")
                continue
            else:
                message = input("Enter message:")
                r, s = sign(signature_params, personal_key, message)
                print(f"r = {r}")
                print(f"s = {s}")
                continue

        if operation == "verify":
            if signature_params is None:
                print("Keys need to be generated first, use gen command")
                continue
            else:
                r = int(input("Enter r: "))
                s = int(input("Enter s: "))
                message = input("Enter message: ")
                print(verify(signature_params, open_key, message, (r, s)))
                continue


def report():
    with open("report.txt", "w") as f:
        q = 178706295845602514261898501512678379830100933245565184651730520471740478551107
        signature_params, open_key, personal_key = gen(q)
        f.write(f"Gen: {signature_params, open_key, personal_key} \n")
        message = "I, Roman Cherepennikov, love MIKOZI"
        signature = sign(signature_params, personal_key, message)
        f.write(f"Sign: {signature} \n")
        ver_result = verify(signature_params, open_key, message, signature)
        f.write(f"Verify: {ver_result} \n")


if __name__ == "__main__":
    main()
