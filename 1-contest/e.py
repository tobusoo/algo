a, b, c, d = list(map(float, input().split()))

if (a < 0.0):
    a = -a
    b = -b
    c = -c
    d = -d

def func(aa, bb, cc, dd, x):
    return aa*x**3 + bb*x**2 + cc*x + dd


l: float = -10**10
r: float = 10**10
eps: float = 1e-5

while r - l > eps:
    mid = (l + r) / 2
    if func(a, b, c, d, mid) < 0:
        l = mid
    else:
        r = mid

print(l)
