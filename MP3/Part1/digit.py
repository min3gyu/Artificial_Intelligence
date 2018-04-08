from math import log as ln
from matplotlib import pyplot as plt

LEN = 32
def parse_digit_data(path_to_file):
    data = []
    digit = []
    labels = []
    with open(path_to_file, "r") as digit_data:
        for lines in digit_data:
            if lines[0] == " ":
                labels += [int(lines[1])]
                data.append(digit)
                digit = []
            else:
                digit.append([int(x) for x in lines if x is not '\n'])

    return data, labels

def training(smoothing=1):
    data, labels = parse_digit_data("./digitdata/optdigits-orig_train.txt")
    print("****Training...****")
    likelihood = []
    num_occ = [0] * 10

    for i in range(0, 10):
        e = []
        for j in range(0, LEN):
            l = [0] * 32
            e.append(l)
        likelihood.append(e)

    for i in range(0, len(labels)):
        curr = labels[i]
        num_occ[curr] += 1
        for x in range(0, LEN):
            for y in range(0, LEN):
                if data[i][x][y] == 1:
                    likelihood[curr][x][y] += 1

    # P(Fij = f | class)
    for i in range(0, 10):
        for x in range(0, LEN):
            for y in range(0, LEN):
                likelihood[i][x][y] += smoothing
                likelihood[i][x][y] /= (num_occ[i] + smoothing)

    prior = [x/len(labels) for x in num_occ]
    return data, labels, likelihood, prior

def test_digit():
    test_data, test_labels = parse_digit_data("./digitdata/optdigits-orig_test.txt")
    orig_data, orig_labels, likelihood, prior = training(1.1)

    MAP = []
    for i in range(0, len(test_labels)):
        l = []
        for j in range(0, 10):
            result = ln(prior[j])
            for x in range(0, LEN):
                for y in range(0, LEN):
                    if test_data[i][x][y] == 1:
                        result += ln(likelihood[j][x][y])
            l += [result]

        MAP += [l.index(max(l))]

    # Calculate Accuracy and construct confusion matrix
    num_correct = 0
    confusion_matrix = [[0] * 10 for x in range(0, 10)]
    test_num_occur = [0] * 10
    for i in range(0, len(MAP)):
        M_elem = MAP[i]
        label_elem = test_labels[i]
        test_num_occur[label_elem] += 1
        if M_elem == label_elem:
            num_correct += 1
        else:
            confusion_matrix[label_elem][M_elem] += 1
    print("Overall accuracy: {:.2f}%".format(num_correct / len(test_labels) * 100))

    # Confusion Matrix(the negative percentage is used to find the highest and lowest posterior probabilities)
    for i in range(0, len(confusion_matrix)):
        for j in range(0, len(confusion_matrix[i])):
            if confusion_matrix[i][j] is not 0:
                confusion_matrix[i][j] /= test_num_occur[i]
                confusion_matrix[i][j] = round(confusion_matrix[i][j], 5)

    # print("\nCONFUSION MATRIX")
    # for e in confusion_matrix:
    #     print(e)

    classification_rate(MAP, test_labels, test_num_occur)
    # high_low_posterior(likelihood, prior, orig_data, orig_labels)
    # draw_four_odd_ratio(likelihood)

def classification_rate(result_label, orig_label, num_occ):
    rate = [0] * 10
    for i in range(0, len(result_label)):
        result_curr = result_label[i]
        orig_curr = orig_label[i]
        if result_curr == orig_curr:
            rate[result_curr] += 1
    for i in range(0, 10):
        print("Classification rate for digit {} is {:.2f}%".format(i, (rate[i] / num_occ[i]) * 100))

def draw_four_odd_ratio(likelihood):
    # 14.63%
    draw_odd_ratio(likelihood, 2, 8)

    # 7.143%
    draw_odd_ratio(likelihood, 9, 8)

    # 6.896%
    draw_odd_ratio(likelihood, 5, 8)

    # 6.667%
    draw_odd_ratio(likelihood, 1, 8)

def draw_odd_ratio(likelihood, r, c):
    plt.imshow(likelihood[r], interpolation = 'nearest')
    plt.show()

    plt.imshow(likelihood[c], interpolation = 'nearest')
    plt.show()

    ratio = []
    for x in range(0, LEN):
        row = []
        for y in range(0, LEN):
            row += [ln(likelihood[r][x][y] / likelihood[c][x][y])]
        ratio.append(row)

    plt.imshow(ratio, interpolation = 'nearest')
    plt.show()

def high_low_posterior(likelihood, prior, orig_data, orig_label):
    digit_data = []
    digit_index = []
    for i in range(0, 10):
        digit_data.append([float('inf'), float('-inf')])
        digit_index.append([0, 0])

    # for i in range(0, len(orig_label)):
    #     curr = orig_label[i]
    #     result = ln(prior[curr])
    #     for x in range(0, LEN):
    #         for y in range(0, LEN):
    #             if orig_data[i][x][y] == 1:
    #                 result += ln(likelihood[curr][x][y])
    #     digit_data[curr] += [result]

    for i in range(0, len(orig_label)):
        curr = orig_label[i]
        result = ln(prior[curr])
        for x in range(0, LEN):
            for y in range(0, LEN):
                if orig_data[i][x][y] == 1:
                    result += ln(likelihood[curr][x][y])
        if result < digit_data[curr][0]:
            digit_data[curr][0] = result
            digit_index[curr][0] = i
        if result > digit_data[curr][1]:
            digit_data[curr][1] = result
            digit_index[curr][1] = i

    print(digit_index)
    line_no = [[(x + 1) * 33, (y + 1) * 33] for x, y in digit_index]
    print(line_no)
    #cprint(orig_label[185])
    # print(orig_label)
    # m = digit_data[0].index(max(digit_data[0]))
    # l = digit_data[0].index(min(digit_data[0]))
    # for i in range(0, len(orig_label)):

    #for i in range(0, len(digit_data)):


if __name__ == '__main__':
    test_digit()
