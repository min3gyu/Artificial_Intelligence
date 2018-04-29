import random
import math

class Ball:
    def __init__(self):
        self.x = 0.5
        self.y = 0.5
        self.vx = 0.03
        self.vy = 0.01

    def update(self):
        self.x += self.vx
        self.y += self.vy
        self.bounce()

    def bounce(self):
        if self.y < 0:
            self.y *= -1
            self.vy *= -1
        elif self.y > 1:
            self.y = 2 - self.y
            self.vy *= -1
        elif self.x < 0:
            self.x *= -1
            self.vx *= -1

    def bounce_hit(self):
        self.x = 2 - self.x
        U = random.uniform(-.015, .015)
        V = random.uniform(-.03, .03)
        self.vx = U - self.vx
        self.vy += V

        if abs(self.vx) < 0.03:
            self.vx = .03 if self.vx > 0 else -.03

    def discretize(self, val):
        return 11 if val >= 1 else math.floor(val * 12)

    def get_xy(self):
        return (self.discretize(self.x), self.discretize(self.y))
