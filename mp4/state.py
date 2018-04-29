class State:
    def __init__(self, x, y, vx, vy, pad_y):
        self.x = x
        self.y = y
        self.vx = vx
        self.vy = vy
        self.pad_y = pad_y

    def __str__(self):
        s = "(" + str(self.x)
        s += (", " + str(self.y))
        s += (", " + str(self.vx))
        s += (", " + str(self.vy))
        s += (", " + str(self.pad_y))
        s += (")")
        return s

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y and self.vx == other.vx and\
                self.vy == other.vy and self.pad_y == self.pad_y

    def as_tuple(self):
        return (self.x, self.y, self.vx, self.vy, self.pad_y)
