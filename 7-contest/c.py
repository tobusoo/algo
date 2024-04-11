from collections import deque

def find_min_cost_path_linear(n, k, cost):
    max_cost = [0] * (n + 1)
    dq = deque([0])
    path = [0] * (n + 1)

    for i in range(1, n + 1):
        while dq and dq[0] < i - k:
            dq.popleft()
        
        max_cost[i] = max_cost[dq[0]] + cost[i]
        path[i] = dq[0]
        while dq and max_cost[i] >= max_cost[dq[-1]]:
            dq.pop()
        
        dq.append(i)
    
    pathh = []
    prev = path[-1]
    while (prev != 0):
        pathh.append(prev)
        prev = path[prev]
    print(max_cost[-1])
    print(len(pathh) + 1)
    pathh.reverse()
    print(1, end=' ')
    for i in range(len(pathh)):
        print(pathh[i] + 1, end=' ')
    print(n+1)


n, k = list(map(int, input().split()))
cost = [0]
cost += list(map(int, input().split()))
cost.append(0)

find_min_cost_path_linear(n-1, k, cost)