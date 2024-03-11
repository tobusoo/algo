# O(n) Space complexity
# O((n+q)logn) Time complexity

# input

# 3
# 1 3
# 4 9
# 1 5
# 7
# 4
# 2
# 3
# 1
# 9
# 10000
# -10000
#

my_inf = 10**9

n = int(input())

l, r = map(int, input().split())
arr: list[tuple] = [(l, '+'), (r, '-')]

for i in range(1, n):
    l, r = map(int, input().split())
    arr.append((l, '+'))
    arr.append((r, '-'))

arr.sort(key=lambda x: x[0])
prefix_sum: list[list] = [[0, -my_inf, arr[0][0] - 1], [1, arr[0][0], arr[0][0]]]

print(arr)

prev_x = arr[0][0]
for i in range(1, len(arr)):
    if prev_x == arr[i][0]:
        if arr[i][1] == '+':
            prefix_sum[-1][0] += 1
        else:
            prefix_sum[-1][0] -= 1
        prefix_sum[-1][2] = arr[i][0] - 1
    else:
        prefix_sum[-1][2] = arr[i][0] - 1
        if arr[i][1] == '+':
            prefix_sum.append([prefix_sum[-1][0] + 1, arr[i][0], arr[i][0]])
        else:
            prefix_sum.append([prefix_sum[-1][0] - 1, arr[i][0], arr[i][0]])

    prev_x = arr[i][0]

prefix_sum[-1][2] = my_inf
print(prefix_sum)


q = int(input())


def request(x_i) -> int:
    left = 0
    right = len(prefix_sum)
    while right - left > 1:
        mid = (left + right) // 2
        count, ll, rr = prefix_sum[mid]
        if x_i < ll:
            right = mid
        elif x_i > rr:
            left = mid
        else:
            return count

    count, ll, rr = prefix_sum[left]
    return count


for i in range(0, q):
    x = int(input())
    print(f'{request(x)} lines at x = {x}')
