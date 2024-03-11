# input

# 10 3
# 1 3
# 4 9
# 1 5
# 3
# 4
# 3
# 1
#

x, n = map(int, input().split())

t = [0] * x

for i in range(0, n):
    left, right = map(int, input().split())
    if left < 0 or right >= x:
        print('Coordinates must be from 0 to x-1')
        continue
    t[left] += 1
    t[right] -= 1

prefix_sum = [t[0]]
for i in range(1, x):
    prefix_sum.append(prefix_sum[i-1] + t[i])

# print(t)
print(prefix_sum)

q = int(input())
for i in range(0, q):
    xi = int(input())
    if xi < 0 or xi >= x:
        print('Coordinate must be from 0 to x-1')
    print(prefix_sum[xi])
