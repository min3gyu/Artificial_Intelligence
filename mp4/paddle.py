import math

class Paddle:
    def __init__(self):
        self.action = (-.04, 0, .04)
        self.h = 0.2
        self.y = 0.5 - self.h / 2

    def update(self, q_idx):
        self.y += self.action[q_idx]
        self.validate()

    def validate(self):
        if self.y < 0:
            self.y = 0
        elif self.y > 1:
            self.y = 1 - self.h;

    def get_xy(self):
        return (1, math.floor((12 * self.y / (1 - self.h))))
