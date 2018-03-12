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
        self.total_value = 0

    def __lt__(self, other):
        return self.total_value < other.total_value

    def __gt__(self, other):
        return self.total_value > other.total_value

    def __eq__(self, other):
        return self.total_value == other.total_value

    def __ne__(self, other):
        return not self.__eq__(other)

LEN = 7
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
    def __init__(self, board, player):
        self.root = Node()
        self.root.board = board
        self.root.avail_pos = get_avail_pos(board)
        self.player = player

    def evaluation(self, board):
        h = horizontal_attack(board, self.player) + horizontal_defense(board, self.player)
        v = vertical_attack(board, self.player) + vertical_defense(board, self.player)
        r = RightDiagon_attack(board, self.player) + RightDiagon_defense(board, self.player)
        l = LeftDiagon_attack(board, self.player) + LeftDiagon_defense(board, self.player)
        return h + v + r + l

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
            child.value = self.evaluation(child.board) - self.evaluation(child.parent.board)
            child.total_value = child.value

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
                child.value = self.evaluation(child.board) - child.parent.value
                child.total_value = child.value + c.value

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
                    child.value = self.evaluation(child.board) - child.parent.value
                    child.total_value = child.value + c1.value

                max_val = max(c1.child)
                c1.total_value = max_val.total_value
                if c1.value < max_val.value:
                    c1.pos = max_val.pos

        for c in self.root.child:
            min_val = min(c.child)
            c.total_value = min_val.total_value
            if c.value < min_val.value:
                c.pos = min_val.pos

        return max(self.root.child).pos

# -----------------------------------------------------------------------------------------------------------------
def horizontal_attack(board, player):
    score = 0
    for i in range(0, 7):
        for j in range(0, 3): # check columns from 0 to 3
            # when current position is player.
            count_player = 0
            count_space = 0
            for k in range(0,5):
                if board[i][j+k] == player and board[i][j+k] != ' ':
                    count_player += 1
                elif board[i][j+k] == ' ':
                    count_space += 1
            # if count is 4, which means consecutive 4 locations are all opponents, we have to block it.
            if count_player == 5 and count_space == 0:
                return 10000000

            if count_player == 4 and count_space == 1:
                score += 10000
            elif count_player == 3 and count_space == 2:
                score += 100
            elif count_player == 2 and count_space == 3:
                score += 10
    return score

def vertical_attack(board, player):
    score = 0
    for i in range(0,3):
        for j in range(0,7):
            count_player = 0
            count_space = 0
            for k in range(0,5):
                if board[i+k][j] == player and board[i+k][j] != ' ':
                    count_player += 1
                elif board[i+k][j] == ' ':
                    count_space += 1
            if count_player == 5 and count_space == 0:
                return 10000000

            if count_player == 4 and count_space == 1:
                score += 10000
            elif count_player == 3 and count_space == 2:
                score += 100
            elif count_player == 2 and count_space == 3:
                score += 10
    return score


def RightDiagon_attack(board, player):
    score = 0
    for i in range(0,3): # check rows from 0 to 3
        for j in range(0,3): # check columns from 0 to 3
            # when current position is player.
            count_player = 0
            count_space = 0
            # count the number of opponent player within consecutive 4 locations.
            for k in range(0,5):
                if board[i+k][j+k] == player and board[i+k][j+k] != ' ':
                    count_player += 1
                elif board[i+k][j+k] == ' ':
                    count_space += 1
            if count_player == 5 and count_space == 0:
                return 10000000

            if count_player == 4 and count_space == 1:
                score += 10000
            elif count_player == 3 and count_space == 2:
                score += 100
            elif count_player == 2 and count_space == 3:
                score += 10
    return score

def LeftDiagon_attack(board, player):
    score = 0
    for i in range(0,3): # check rows from 0 to 3
        for j in range(4,7): # check columns from 3 to 6
            # when current position is player.
            count_player = 0
            count_space = 0
            for k in range(0,5):
                if board[i+k][j-k] == player and board[i+k][j-k] != ' ':
                    count_player += 1
                elif board[i+k][j-k] == ' ':
                    count_space += 1
            # if count is 3, which means consecutive 4 locations are all opponents, we have to block it.
            if count_player == 5 and count_space == 0:
                return 10000000

            if count_player == 4 and count_space == 1:
                score += 10000
            elif count_player == 3 and count_space == 2:
                score += 100
            elif count_player == 2 and count_space == 3:
                score += 10
    return score

def horizontal_defense(board, player):
    score = 0
    for i in range(0, 7):
        for j in range(0, 3): # check columns from 0 to 3
            # when current position is player.
            count_player = 0
            count_space = 0
            for k in range(0,5):
                if board[i][j+k] != player and board[i][j+k] != ' ':
                    count_player += 1
                elif board[i][j+k] == ' ':
                    count_space += 1
            # if count is 4, which means consecutive 4 locations are all opponents, we have to block it.
            if count_player == 4 and count_space == 1:
                score += 10000
            elif count_player == 3 and count_space == 2:
                score += 100
            elif count_player == 2 and count_space == 3:
                score += 10
    return score

def vertical_defense(board, player):
    score = 0
    for i in range(0,3):
        for j in range(0,7):
            count_player = 0
            count_space = 0
            for k in range(0,5):
                if board[i+k][j] != player and board[i+k][j] != ' ':
                    count_player += 1
                elif board[i+k][j] == ' ':
                    count_space += 1
            if count_player == 4 and count_space == 1:
                score += 10000
            elif count_player == 3 and count_space == 2:
                score += 100
            elif count_player == 2 and count_space == 3:
                score += 10
    return score

def RightDiagon_defense(board, player):
    score = 0
    for i in range(0,3): # check rows from 0 to 3
        for j in range(0,3): # check columns from 0 to 3
            # when current position is player.
            count_player = 0
            count_space = 0
            # count the number of opponent player within consecutive 4 locations.
            for k in range(0,5):
                if board[i+k][j+k] != player and board[i+k][j+k] != ' ':
                    count_player += 1
                elif board[i+k][j+k] == ' ':
                    count_space += 1
            if count_player == 4 and count_space == 1:
                score += 10000
            elif count_player == 3 and count_space == 2:
                score += 100
            elif count_player == 2 and count_space == 3:
                score += 10
    return score

def LeftDiagon_defense(board, player):
    score = 0
    for i in range(0,3): # check rows from 0 to 3
        for j in range(4,7): # check columns from 3 to 6
            # when current position is player.
            count_player = 0
            count_space = 0
            for k in range(0,5):
                if board[i+k][j-k] != player and board[i+k][j-k] != ' ':
                    count_player += 1
                elif board[i+k][j-k] == ' ':
                    count_space += 1
            if count_player == 4 and count_space == 1:
                score += 10000
            elif count_player == 3 and count_space == 2:
                score += 100
            elif count_player == 2 and count_space == 3:
                score += 10
    return score

board_H = [[' ', ' ', ' ', ' ', ' ', ' ', ' '],
           [' ', ' ', 'O', 'X', ' ', ' ', ' '],
           [' ', ' ', 'O', 'O', 'X', ' ', ' '],
           [' ', 'X', 'O', 'O', 'O', ' ', ' '],
           [' ', 'X', 'X', ' ', 'X', ' ', ' '],
           [' ', ' ', ' ', ' ', ' ', ' ', ' '],
           [' ', ' ', ' ', ' ', ' ', ' ', ' '] ]

count = 0
player = 'O'
while count < 10:
    if count % 2 is 0:
        player = 'O'
    else:
        player = 'X'
    minimax = Minimax(board_H, player)
    pos = minimax.expand_to_depth3()
    board_H[pos[0]][pos[1]] = player
    for e in board_H:
        print(e)
    print("player {} made a move at {}".format(player, pos))
    count += 1
for e in board_H:
    print(e)


# player = 'O'
# minimax = Minimax(board_H, player)
# pos = minimax.expand_to_depth3()
# print(pos)
