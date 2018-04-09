import math
import random

LEN = 1024
w_vec = []
BIAS = 1

for i in range(0, 10):
    vec = []
    for j in range(0, LEN):
        vec += [random.uniform(-1, 1)]
    w_vec.append(vec)

def parse_digit_data(path_to_file):
    data = []
    labels = []
    single_digit = []
    with open(path_to_file, "r") as digit_data:
        for lines in digit_data:
            for i in range(0, len(lines)):
                if lines[i] == " ":
                    labels.append(int(lines[1]))
                    data.append(single_digit)
                    single_digit = []
                    break
                elif lines[i] != '\n':
                    single_digit.append(int(lines[i]))

    return data, labels



def training(data, labels, ep):
    globals
    for i in range (0, len(data)):
        curr = data[i]
        # curr.append(1)
        label = labels[i]

        dot_p = []
        for j in range(0, 10):
            dot_p.append(dot(w_vec[j], curr))

        classification = dot_p.index(max(dot_p))
        if classification != label:
            n = 1 / math.sqrt(((i + 1) + ep * len(labels)))
            for k in range(0, LEN):
                w_vec[classification][k] -= (curr[k] * n)
                w_vec[label][k] += (curr[k] * n)

def testing():
    globals
    test_data, test_label = parse_digit_data("./digitdata/optdigits-orig_test.txt")
    result = []
    for i in range(0, len(test_label)):
        curr = test_data[i]
        label = test_label[i]

        dot_p = []
        for j in range(0, 10):
            dot_p.append(dot(w_vec[j], curr))

        classification = dot_p.index(max(dot_p))
        result += [classification]

    print(result)
    num = 0
    for i in range(0, len(test_label)):
        if result[i] == test_label[i]:
            num += 1
    print("Rate: {}".format(num / len(test_label)))

def dot(a, b):
    assert(len(a) == len(b))
    result = 0
    for i in range (0, LEN):
        result += (a[i] * b[i])
    return result

def signum(n):
    return 1 if n >= 0 else -1

data, label = parse_digit_data("./digitdata/optdigits-orig_train.txt")
for i in range(0, 10):
    training(data, label, i)
    testing()
