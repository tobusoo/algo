#include <climits>
#include <iostream>
#include <queue>
#include <vector>

#define INF LONG_LONG_MAX
using ll = long long;
using ull = long long;

struct Edge {
    ll w;
    ll to;
};

struct Graph {
    std::vector<std::vector<Edge>> g;
    ll size;

    Graph(ll n) : g(n, std::vector<Edge>()), size(n)
    {
    }

    void add(ll from, ll to, ll weight)
    {
        g[from].push_back({.w = weight, .to = to});
        g[to].push_back({.w = weight, .to = from});
    }

    void print()
    {
        for (size_t i = 0; i < g.size(); i++) {
            if (g[i].size() == 0)
                continue;
            std::cout << i + 1 << ": ";
            for (auto&& j : g[i]) {
                std::cout << "{";
                std::cout << j.to + 1 << ' ' << j.w;
                std::cout << "} ";
            }
            std::cout << '\n';
        }
    }

    void dijkstra()
    {
        std::vector<ll> used(size, 0);
        std::vector<ull> d(size, INF);
        d[0] = 0;
        std::priority_queue<
                std::pair<ull, ll>,
                std::vector<std::pair<ull, ll>>,
                std::greater<std::pair<ull, ll>>>
                q;
        q.push({0, 0});
        while (!q.empty()) {
            auto c = q.top();
            q.pop();
            auto dist = c.first;
            auto v = c.second;
            if (dist > d[v])
                continue;
            for (auto&& i : g[v]) {
                auto u = i.to;
                auto w = i.w;
                if (d[u] > d[v] + w) {
                    d[u] = d[v] + w;
                    q.push({d[u], u});
                }
            }
        }
        for (auto&& i : d) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
};

int main()
{
    ll n, m, v, u, w;
    std::cin >> n >> m;
    Graph g(n);
    for (ll i = 0; i < m; i++) {
        std::cin >> v >> u >> w;
        g.add(v - 1, u - 1, w);
    }

    g.dijkstra();

    return 0;
}