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
    ll limit;
};

struct Graph {
    std::vector<std::vector<Edge>> g;
    ll size;

    Graph(ll n) : g(n, std::vector<Edge>()), size(n)
    {
    }

    void add(ll from, ll to, ll weight, ll limit)
    {
        g[from].push_back({.w = weight, .to = to, .limit = limit});
        g[to].push_back({.w = weight, .to = from, .limit = limit});
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

    bool dijkstra(ll cups)
    {
        ll track_weight = cups * 100 + 3'000'000;

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
                auto lim = i.limit;
                if (d[u] > d[v] + w && lim >= track_weight) {
                    d[u] = d[v] + w;
                    q.push({d[u], u});
                }
            }
        }

        if (d[size - 1] > 24 * 60)
            return false;
        return true;
    }
};

int main()
{
    ll n, m, v, u, w, lim;
    std::cin >> n >> m;
    Graph g(n);

    for (ll i = 0; i < m; i++) {
        std::cin >> v >> u >> w >> lim;
        g.add(v - 1, u - 1, w, lim);
    }

    ll l = 0;
    ll r = 10'000'000;
    while (r - l > 1) {
        ll mid = (r + l) >> 1;
        if (g.dijkstra(mid))
            l = mid;
        else
            r = mid;
    }

    std::cout << l << '\n';

    return 0;
}