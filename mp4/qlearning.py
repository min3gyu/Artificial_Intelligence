from state import State

class Q_Learning:
    def __init__(self, c = 50, gamma = 0.9):
        self.constant = c
        self.gamma = gamma
        self.q_table = {}
        self.seen = {}
        self.action = [-1, 0, 1]
        for x in range(0, 12):
            for y in range(0, 12):
                for vx in [-1, 1]:
                    for vy in [-1, 0, 1]:
                        for pad_y in range(0, 12):
                            for a in self.action:
                                self.q_table[((x, y, vx, vy, pad_y), a)] = 0
                                self.seen[((x, y, vx, vy, pad_y), a)] = 0

    def get_Q(self, state, action):
        return self.q_table[(state, action)]

    def set_Q(self, state, action, value):
        self.q_table[(state, action)] = value

    def update(self, state, action, next_state, reward):
        # update seen
        self.seen[(state, action)] += 1

        alpha = self.constant / (self.constant + self.seen[state, action])

        # (1 - alpha)Q(s, a)
        q_val = self.get_Q(state, action)
        q_val *= (1 - alpha)

        max_q = max([self.get_Q(next_state, a) for a in self.action])
        max_q *= self.gamma
        max_q += reward
        max_q *= alpha
        q_val += max_q

        self.set_Q(state, action, q_val)
