#include <climits>
#include <iostream>
#include <vector>

using ll = long long;
using ull = unsigned long long;
#define INF LONG_LONG_MAX

std::vector<std::vector<ll>> g;
std::vector<std::pair<ll, ll>> p;
std::vector<ll> tin, tout;
std::vector<std::vector<ll>> up;
ll timer;
ll log_n;

void dfs(ll v, int p = 0)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (ll i = 1; i <= log_n; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (ull i = 0; i < g[v].size(); ++i) {
        ll to = g[v][i];
        if (to != p)
            dfs(to, v);
    }
    tout[v] = ++timer;
}

bool upper(ll a, ll b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

ll lca(ll u, ll v)
{
    if (upper(u, v))
        return u;
    if (upper(v, u))
        return v;
    for (ll i = log_n; i >= 0; --i) {
        if (!upper(up[u][i], v))
            u = up[u][i];
    }

    return up[u][0];
}

ll low_cost(ll u, ll v)
{
    ll lca_ = lca(u, v);
    ll min_u = INF;
    ll min_v = INF;
    if (lca_ != v) {
        while (p[v].first != lca_) {
            min_v = std::min(min_v, p[v].second);
            v = p[v].first;
        }
        min_v = std::min(min_v, p[v].second);
    }

    if (lca_ != u) {
        while (p[u].first != lca_) {
            min_u = std::min(min_u, p[u].second);
            u = p[u].first;
        }
        min_u = std::min(min_u, p[u].second);
    }

    return std::min(min_u, min_v);
}

int main()
{
    ll n, m, u, v, temp, cost;
    std::cin >> n;
    g.resize(n, std::vector<ll>()), tin.resize(n), tout.resize(n), up.resize(n);
    p.resize(n);

    for (ll i = 0; i < n - 1; i++) {
        std::cin >> temp >> cost;
        g[temp].push_back(i + 1);
        p[i + 1] = {temp, cost};
    }

    log_n = 1;
    while ((1 << log_n) <= n)
        ++log_n;
    for (ll i = 0; i < n; ++i)
        up[i].resize(log_n + 1);

    dfs(0);
    std::cin >> m;
    for (ll i = 0; i < m; i++) {
        std::cin >> u >> v;
        std::cout << low_cost(u, v) << '\n';
    }

    return 0;
}