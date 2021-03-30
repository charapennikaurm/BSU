def decode(words, dictionary):
    decoded_words = []
    for word in words:
        s = ''
        for letter in word:
            if letter in dictionary:
                s += str(dictionary[letter])
            else:
                s += letter
        decoded_words.append(s)
    return decoded_words


def min_column_element(array, column_index):
    minimum = 0
    for i in range(len(array)):
        if (array[i][column_index] < minimum and array[i][column_index] != 0) or minimum == 0:
            minimum = array[i][column_index]
    return minimum


def restore_word(dp, min_words, words):
    result = ''
    i = len(dp[0]) - 1
    j = len(words) - 1
    while j >= 0 and i > 0:
        if dp[j][i] == min_words[i]:
            result = words[j] + ' ' + result
            i -= len(words[j])
            j = len(words) - 1
        else:
            j -= 1
    return result.strip()


dictionary = {
    'A': 2, 'B': 2, 'C': 2,
    'D': 3, 'E': 3, 'F': 3,
    'G': 4, 'H': 4,
    'I': 1, 'J': 1,
    'K': 5, 'L': 5,
    'M': 6, 'N': 6, 'O': 0,
    'P': 7, 'Q': 0, 'R': 7, 'S': 7,
    'T': 8, 'U': 8, 'V': 8,
    'W': 9, 'X': 9, 'Y': 9, 'Z': 0
}

file_in = open('in.txt', 'r')
file_out = open('out.txt', 'w')

words = []

for line in file_in:
    words.append(line.strip())

phone_number = words[0]
number_len = len(words[0])
words.pop(0)
n = int(words[0])
words.pop(0)

words.sort(key=len)
decoded_words = decode(words, dictionary)

dp = [[0] * (number_len + 1) for i in range(n)]

min_words = [0 for i in range(number_len + 1)]
for i in range(1, number_len + 1):
    for j in range(n):
        if len(decoded_words[j]) <= i:
            if decoded_words[j] == phone_number[i - len(decoded_words[j]):i] \
                    and (min_words[i - len(decoded_words[j])] != 0 or i - len(decoded_words[j]) == 0):
                ind = i - len(decoded_words[j])
                dp[j][i] = int(min_words[ind] + 1)
        else:
            break
    min_words[i] = min_column_element(dp, i)

result = ''
if min_words[-1] == 0:
    file_out.write('No solution')
else:
    file_out.write(str(min_words[-1]) + '\n')
    file_out.write(restore_word(dp, min_words, words))