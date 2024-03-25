import sys

# n, m = list(map(int, sys.stdin.readline().split()))

# g = [[] for i in range(n)]

# for _ in range(m):
#     u, v = list(map(int, sys.stdin.readline().split()))
#     g[u-1].append(v-1)
#     g[v-1].append(u-1)

# print(g)
n = 7

g = [[1],
     [0],
     [3, 4],
     [2, 4],
     [2, 3], [6], [5]]

used = [0] * n


def dfs(v: int, comp: set):
    used[v] = 1
    comp.add(v)
    for i in range(len(g[v])):
        to = g[v][i]
        if used[to] == 0:
            dfs(to, comp)


def find_comps():
    comp = [set()]
    for i in range(len(used)):
        used[i] = 0
    for i in range(n):
        if used[i] == 0:
            comp.append(set())
            dfs(i, comp[-1])

    print(len(comp))
    for i in comp:
        if len(i) == 0:
            continue
        
        print(len(i))
        for j in i:
            print(j+1, end=' ')
        print(' ')


find_comps()
