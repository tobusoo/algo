import math

C = float(input())
if C == 1:
    print(0)
    exit()

def func(x):
    return x ** 2 + math.sqrt(x + 1)


l: float = -1.0
r: float = 10**10
eps: float = 1e-8

while r - l > eps:
    mid = (l + r) / 2
    if func(mid) < C:
        l = mid
    else:
        r = mid

print(l)
