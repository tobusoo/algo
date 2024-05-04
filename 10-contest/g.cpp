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

    std::pair<ull, ull> dijkstra(ull start, ull a, ull b)
    {
        std::vector<ll> used(size, 0);
        std::vector<ull> d(size, INF);
        std::priority_queue<
                std::pair<ull, ll>,
                std::vector<std::pair<ull, ll>>,
                std::greater<std::pair<ull, ll>>>
                q;
        d[start] = 0;
        q.push({0, start});

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

        return {d[a], d[b]};
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll n, m, v, u, w, a, b, c;
    std::cin >> n >> m;
    Graph g(n);
    for (ll i = 0; i < m; i++) {
        std::cin >> v >> u >> w;
        g.add(v - 1, u - 1, w);
    }
    std::cin >> a >> b >> c;
    a--;
    b--;
    c--;
    auto [ab, ac] = g.dijkstra(a, b, c); // shortest path from a to b and from a to c
    auto [ba, bc] = g.dijkstra(b, a, c); // shortest path from b to a and from b to c
    // auto [ca, cb] = g.dijkstra(c, a, b);

    ll way_1 = ab + bc;
    if (ab == INF || bc == INF)
        way_1 = INF;
    ll way_2 = ba + ac;
    if (ba == INF || ac == INF)
        way_2 = INF;
    ll way_3 = ac + bc;
    if (ac == INF || bc == INF)
        way_3 = INF;

    ll ans = std::min(way_1, std::min(way_2, way_3));
    if (ans == INF)
        std::cout << -1 << '\n';
    else
        std::cout << ans << '\n';
    return 0;
}