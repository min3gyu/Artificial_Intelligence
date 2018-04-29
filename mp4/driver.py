from qlearning import *
from ball import *
from paddle import *
from state import *
import random

q_learn = Q_Learning()
ball = None
paddle = None
action = [-1, 0, 1]
def train():
    print("*******************TRAINING...*******************")
    for i in range(0, 1000000):
        train_game()

    print("*******************DONE TRAINING*******************")

def train_game():
    global q_learn, ball, paddle, action

    ball = Ball()
    paddle = Paddle()
    reward = 0

    prev_state = None
    while reward != -1:
        prev_state = get_state(ball, paddle)
        prev_action = random.choice(action)
        ball.update()
        paddle.update(prev_action)
        curr_state = get_state(ball, paddle)
        reward = compute_reward()
        q_learn.update(prev_state, prev_action, curr_state, reward)

def compute_reward():
    global ball, paddle
    if ball.x > 1:
        return 1 if (ball.y >= paddle.y and ball.y <= paddle.y + paddle.h) else -1

    return 0

def get_state(b, p):
    x, y = b.get_xy()
    if x >= 12:
        x = 11
    if x < 0:
        x = 0
    if y >= 12:
        y = 11
    if y < 0:
        y = 0
    p_x, p_y = p.get_xy()
    if p_y >= 12:
        p_y = 11
    if p_y < 0:
        p_y = 0
    vx = -1 if b.vx < 0 else 1
    vy = None
    if abs(b.vy) < .015:
        vy = 0
    elif b.vy > 0:
        vy = 1
    else:
        vy = -1
    return (x, y, vx, vy, p_y)

def play_game():
    global q_learn, ball, paddle
    print("*******************PLAY GAME...*******************")
    hit_rate = []
    for i in range(0, 200):
        ball = Ball()
        paddle = Paddle()
        num_hit = 0
        reward = 0
        while reward != -1:
            ball.update()
            t = (ball.x, ball.y, ball.vx, ball.vy, paddle.y)
            best_action = max([q_learn.q_table.get(t, action) for action in q_learn.action])
            paddle.update(best_action)
            reward = compute_reward()
            if reward == 1:
                num_hit += 1
        hit_rate += [num_hit]

    return hit_rate


train()
res = play_game()
print(res)
print(max(res))
