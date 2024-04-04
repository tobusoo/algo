#include <iostream>
#include <queue>
#include <stack>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::vector<std::vector<int>>> d(
            n + 1, std::vector<std::vector<int>>(n + 1, std::vector<int>(3, 99999)));

    int x[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int y[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;

    std::queue<std::pair<int, int>> q;
    d[x1][y1] = {0, 0, 0};
    q.push({x1, y1});
    int i = 0, j = 0;

    bool is_find = false;
    while (!q.empty() && !is_find) {
        i = q.front().first;
        j = q.front().second;
        q.pop();
        for (int k = 0; k < 8; k++) {
            int u = i + x[k];
            int v = j + y[k];
            if (u > 0 && u <= n && v > 0 && v <= n && d[u][v][0] == 99999) {
                d[u][v][0] = d[i][j][0] + 1;
                d[u][v][1] = i;
                d[u][v][2] = j;
                if (u == x2 && v == y2) {
                    is_find = true;
                    break;
                }
                q.push({u, v});
            }
        }
    }

    std::cout << d[x2][y2][0] << '\n';
    int u = x2, v = y2;
    std::stack<std::pair<int, int>> s;

    while (true) {
        int uu = d[u][v][1];
        int vv = d[u][v][2];
        s.push({uu, vv});
        u = uu;
        v = vv;
        if (u == x1 && v == y1)
            break;
    }

    while (!s.empty()) {
        auto e = s.top();
        s.pop();
        std::cout << e.first << ' ' << e.second << '\n';
    }
    std::cout << x2 << ' ' << y2 << '\n';

    return 0;
}