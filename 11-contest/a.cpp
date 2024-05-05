#include <iostream>
#include <vector>

using ll = long long;
using ull = unsigned long long;

std::vector<std::vector<ll>> g;
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

int main()
{
    ll n, m, u, v, temp;
    std::cin >> n;
    g.resize(n, std::vector<ll>()), tin.resize(n), tout.resize(n), up.resize(n);

    for (ll i = 0; i < n - 1; i++) {
        std::cin >> temp;
        g[temp].push_back(i + 1);
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
        std::cout << lca(u, v) << '\n';
    }

    return 0;
}