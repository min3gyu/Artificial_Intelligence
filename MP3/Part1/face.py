from math import log as ln

#height
H = 70
#width
W = 60
def parse_face_data(path_to_file):
    data = []
    face = []
    with open(path_to_file, 'r') as face_data:
        line_no = 0
        for lines in face_data:
            if line_no == H:
                data.append(face)
                face = []
                line_no = 0

            line_no += 1
            l = list(lines)
            assert(l[-1] == '\n')
            face.append(l[:W])

    # add last line and face data
    face.append(['\n'])
    data.append(face)

    # for e in data:
    #     assert (len(e) == H)

    return data

def parse_face_label(path_to_file):
    face_label = []
    with open(path_to_file, 'r') as labels:
        for l in labels:
            face_label += [int(l[0])]

    # print(face_label)
    # print(len(face_label))

    return face_label

def training(smoothing=1):
    data = parse_face_data("./facedata/facedatatrain")
    labels = parse_face_label("./facedata/facedatatrainlabels")
    likelihood = []
    num_occ = [0, 0]

    for i in range(0, 2):
        e = []
        for j in range(0, H):
            l = [0] * W
            e.append(l)
        likelihood.append(e)

    for i in range(0, len(labels)):
        curr = labels[i]
        num_occ[curr] += 1

        for x in range(0, H):
            for y in range(0, W):
                if data[i][x][y] == '\n':
                    break
                if data[i][x][y] == '#':
                    likelihood[curr][x][y] += 1

    # P(Fij = f | class)
    for i in range(0, 2):
        for x in range(0, H):
            for y in range(0, W):
                likelihood[i][x][y] += smoothing
                likelihood[i][x][y] /= (num_occ[i] + smoothing * 2)

    prior = [x/len(labels) for x in num_occ]

    return likelihood, prior

def test_face():
    test_data = parse_face_data("./facedata/facedatatest")
    test_labels = parse_face_label("./facedata/facedatatestlabels")

    likelihood, prior = training(1)

    MAP = []
    num_occ = [0, 0]
    for i in range(0, len(test_labels)):
        l = []
        num_occ[test_labels[i]] += 1
        for j in range(0, 2):
            result = ln(prior[j])

            for x in range(0, H):
                for y in range(0, W):
                    if test_data[i][x][y] == '\n':
                        break
                    if test_data[i][x][y] == '#':
                        result += ln(likelihood[j][x][y])
                    elif test_data[i][x][y] == ' ':
                        result += ln(1 - likelihood[j][x][y])
            l += [result]
        MAP += [l.index(max(l))]

    assert (len(MAP) == len(test_labels))
    num_correct = [0, 0]
    for i in range(0, len(MAP)):
        if MAP[i] == test_labels[i]:
            if MAP[i] == 0:
                num_correct[0] += 1
            else:
                num_correct[1] += 1

    print("Overall accuracy: {:.2f}%".format(sum(num_correct) / len(test_labels) * 100))
    print("Correctly classified face as face: {:.2f}%".format(num_correct[0] / num_occ[0] * 100))
    print("Correctly classified non-face as non-face: {:.2f}%".format(num_correct[1] / num_occ[1] * 100))

    return sum(num_correct)
if __name__ == '__main__':
    test_face()
