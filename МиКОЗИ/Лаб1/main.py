# Вариант 10

from typing import Tuple


def affine_encrypt(alphabet: str, key: Tuple[int, int], message: str) -> str:
    a = key[0]
    b = key[1]
    return "".join([alphabet[(a * alphabet.find(i) + b) % len(alphabet)] for i in message])


def simple_decryption(alphabet: str, key: str, message: str) -> str:
    if len(alphabet) != len(key):
        raise ValueError(
            f'Alphabet and key expected to have same length. But got alphabet: {len(alphabet)}, key: {len(key)} '
        )
    return "".join([alphabet[key.find(i)] for i in message])


print(
    affine_encrypt(alphabet="абвгдеёжзийклмнопрстуфхцчшщъыьяюя",
                   message="криптосистема",
                   key=(17, 24),
                   ))

print(
    simple_decryption(
        alphabet="абвгдеёжзийклмнопрстуфхцчшщъыьяюя",
        key="ИЮЧЪЩЁЗМШСХУРЦЭЬЫНФДБТВЛГАПЯЕОЖКЙ".lower(),
        message="ЩМЁУТНБД".lower(),
    )
)


