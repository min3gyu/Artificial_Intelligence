from copy import deepcopy as dp
import time

class Node:
    def __init__(self):
        self.parent = None
        self.child = list()
        self.avail_pos = []
        self.value = 0
        self.board = None
        self.pos = None

    def __lt__(self, other):
        return self.value < other.value

    def __gt__(self, other):
        return self.value > other.value

    def __eq__(self, other):
        return self.value == other.value

    def __ne__(self, other):
        return not self.__eq__(other)

LEN = 3
AVAIL = ' '
P1 = 'O'
P2 = 'X'
board = []

for i in range(0, LEN):
    board += [[AVAIL] * LEN]

def get_avail_pos(b):
    avail_pos = []
    for i in range(0, LEN):
        for j in range(0, LEN):
            if b[i][j] is AVAIL:
                avail_pos += [(i, j)]

    return avail_pos

class Minimax:
    def __init__(self, board):
        self.root = Node()
        self.root.board = board
        self.root.avail_pos = get_avail_pos(board)

    def get_next_move(self):
        self.expand_to_depth3()


    def expand_to_depth3(self):
        num_node_expand = 0
        start = time.time()
        # ------------------------ DEPTH 1 --------------------------------
        for i in range(0, len(self.root.avail_pos)):
            child = Node()
            child.parent = self.root
            child.avail_pos = dp(self.root.avail_pos)
            child.pos = child.avail_pos.pop(i)
            child.board = dp(self.root.board)
            child.board[child.pos[0]][child.pos[1]] = 'O'
            self.root.child += [child]
            num_node_expand += 1

        for c in self.root.child:
            for i in range(0, len(c.avail_pos)):
                child = Node()
                child.parent = c
                child.avail_pos = dp(c.avail_pos)
                child.pos = child.avail_pos.pop(i)
                child.board = dp(c.board)
                child.board[child.pos[0]][child.pos[1]] = 'X'
                c.child += [child]
                num_node_expand += 1

        for c in self.root.child:
            for c1 in c.child:
                for i in range(0, len(c1.avail_pos)):
                    child = Node()
                    child.parent = c1
                    child.avail_pos = dp(c1.avail_pos)
                    child.pos = child.avail_pos.pop(i)
                    child.board = dp(c1.board)
                    child.board[child.pos[0]][child.pos[1]] = 'O'
                    c1.child += [child]
                    num_node_expand += 1
                    # COMPUTER VALUE

        print(num_node_expand)
        end = time.time()
        print(end - start)

b = [[' ', ' ', ' '], [' ', ' ', ' '], [' ', ' ', ' ']]
minimax = Minimax(b)
minimax.expand_to_depth3()
