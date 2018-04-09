from matplotlib import pyplot as plt
import math
import numpy as np
import random

LEN = 1024
w_vec = []

def generate_weight_vec(rand):
    globals
    for i in range(0, 10):
        vec = []
        for j in range(0, LEN):
            if rand:
                vec += [random.uniform(-1, 1)]
            else:
                vec += [0]
        w_vec.append(vec)
    for e in w_vec:
        assert (len(e) == LEN)
def parse_digit_data(path_to_file, bias):
    global LEN
    if bias:
        LEN = 1025
    data = []
    labels = []
    single_digit = []
    with open(path_to_file, "r") as digit_data:
        for lines in digit_data:
            for i in range(0, len(lines)):
                if lines[i] == " ":
                    labels.append(int(lines[1]))
                    if bias:
                        single_digit.append(1)
                    data.append(single_digit)
                    single_digit = []
                    break
                elif lines[i] != '\n':
                    single_digit.append(int(lines[i]))

    return data, labels



def training(data, labels, ep, shuffle):
    globals
    if shuffle:
        data, labels = shuffle_data(data, labels)

    for i in range (0, len(data)):
        curr = data[i]
        label = labels[i]

        dot_p = []
        n = 0
        for j in range(0, 10):
            x = dot(w_vec[j], curr)
            n += np.exp(x)
            dot_p.append(dot(w_vec[j], curr))

        classification = dot_p.index(max(dot_p))
        if classification != label:
            n = 1 / math.sqrt(((i + 1) + ep * len(labels)))
            for k in range(0, LEN):
                w_vec[classification][k] -= (curr[k] * n)
                w_vec[label][k] += (curr[k] * n)

def testing(bias):
    globals
    test_data, test_label = parse_digit_data("./digitdata/optdigits-orig_test.txt", bias)
    result = []
    for i in range(0, len(test_label)):
        curr = test_data[i]
        label = test_label[i]

        dot_p = []
        for j in range(0, 10):
            # print(dot(w_vec[j], curr))
            dot_p.append(dot(w_vec[j], curr))

        classification = dot_p.index(max(dot_p))
        result += [classification]

    num = 0
    num_occ = [0] * 10
    for i in range(0, len(test_label)):
        num_occ[result[i]] += 1
        if result[i] == test_label[i]:
            num += 1
    print("Overall Accuracy: {}".format(num / len(test_label)))

    # confusion_matrix
    confusion_matrix = [[0] * 10 for x in range(0, 10)]
    for i in range(0, len(result)):
        confusion_matrix[result[i]][test_label[i]] += 1

    for i in range(0, 10):
        for j in range(0, 10):
            if confusion_matrix[i][j] is not 0:
                confusion_matrix[i][j] /= num_occ[i]
                confusion_matrix[i][j] = round(confusion_matrix[i][j], 5) * 100

    # for e in confusion_matrix:
    #     print(e)

def dot(a, b):
    assert(len(a) == len(b))
    result = 0
    for i in range (0, LEN):
        result += (a[i] * b[i])
    return result

def pack_data(data, labels):
    packed = []
    for i in range(0, len(data)):
        packed += [[data[i], labels[i]]]
    return packed

def unpack_data(packed):
    data = []
    label = []
    for i in range(0, len(packed)):
        curr_data, curr_label = packed[i]
        data.append(curr_data)
        label.append(curr_label)
    return data, label

def shuffle_data(data, labels):
    print("*****Shuffling*****")
    packed = pack_data(data, labels)
    random.shuffle(packed)
    return unpack_data(packed)

def driver(rand, bias, shuffle, num_epoch):
    data, label = parse_digit_data("./digitdata/optdigits-orig_train.txt", bias)
    generate_weight_vec(rand)
    for i in range(0, num_epoch):
        training(data, label, i, shuffle)
        # print("Epoch {}".format(i))
        # testing(bias)
        if i == num_epoch - 1:
            print("Epoch {}:".format(i), end = " ")
            testing(bias)
            weight_visualization()

def weight_visualization():
    globals
    for i in range(0, len(w_vec)):
        plt.imshow(np.array(w_vec[i][:1024]).reshape(32, 32), interpolation = 'nearest')
        plt.show()

driver(rand = False, bias = False, shuffle = False, num_epoch = 4)
