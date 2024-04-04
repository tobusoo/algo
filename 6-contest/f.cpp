#include <iostream>
#include <map>
#include <queue>
#include <vector>

class Graph {
public:
    std::vector<std::vector<size_t>> g;
    std::vector<int> used;
    size_t n = 0;

    Graph(size_t n) : g(n, std::vector<size_t>()), used(n, 0), n(n)
    {
    }

    void add(size_t i, size_t j)
    {
        g[i].push_back(j);
    }

    int bfs(size_t start, size_t end)
    {
        std::queue<std::pair<size_t, int>> q;
        q.push({start, 0});
        while (!q.empty()) {
            auto v = q.front();
            q.pop();
            if (v.first == end)
                return v.second;
            used[v.first] = 1;
            for (size_t i = 0; i < g[v.first].size(); i++) {
                if (used[g[v.first][i]] == 0) {
                    q.push({g[v.first][i], v.second + 1});
                    used[g[v.first][i]] = 1;
                }
            }
        }

        return -1;
    }
};

int main()
{
    size_t n;
    std::cin >> n;

    Graph g(100);
    std::string from, to;
    char t1, t2;
    size_t k = 0;
    std::map<std::string, size_t> m;

    for (size_t i = 0; i < n; i++) {
        std::cin >> from >> t1 >> t2 >> to;
        if (m.count(from) == 0) {
            m.insert({from, k++});
        }
        if (m.count(to) == 0) {
            m.insert({to, k++});
        }

        g.add(m[from], m[to]);
    }

    std::cin >> from >> to;
    if (m.count(from) == 0) {
        m.insert({from, k++});
    }
    if (m.count(to) == 0) {
        m.insert({to, k++});
    }

    int answ = g.bfs(m[from], m[to]);
    std::cout << answ << '\n';

    return 0;
}