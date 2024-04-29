#include <algorithm>
#include <iostream>
#include <vector>

typedef long long ll;

ll N = 1 << 19;
ll offset = 200000;

struct Node {
    ll max;
    ll y;
    ll add;
};
std::vector<Node> t(2 * N - 1);

struct Query {
    ll x;
    ll y1;
    ll y2;
    bool is_open;
};

std::vector<Query> q;

void SegmentTreebuild()
{
    ll cur = N - 1;

    while (cur < 2 * N - 1) {
        t[cur] = {0, cur - N + 1, 0};
        cur++;
    }

    ll cur1 = N - 2;
    while (cur1 > 0) {
        t[cur1] = {0, t[2 * cur1 + 1].y, 0};
        --cur1;
    }
}

void update(ll v, ll tl, ll tr, ll l, ll r, ll value)
{
    if (tr <= l || r <= tl)
        return;
    if (l >= tl && r <= tr) {
        t[v].add += value;
        t[v].max += value;
        return;
    }

    t[2 * v + 1].max += t[v].add;
    t[2 * v + 2].max += t[v].add;
    t[2 * v + 1].add += t[v].add;
    t[2 * v + 2].add += t[v].add;
    t[v].add = 0;

    ll mid = (l + r) >> 1;
    update(2 * v + 1, tl, tr, l, mid, value);
    update(2 * v + 2, tl, tr, mid, r, value);
    if (t[2 * v + 1].max > t[2 * v + 2].max) {
        t[v].max = t[2 * v + 1].max;
        t[v].y = t[2 * v + 1].y;
    } else {
        t[v].max = t[2 * v + 2].max;
        t[v].y = t[2 * v + 2].y;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll n;
    std::cin >> n;

    ll x1, y1, x2, y2;
    for (ll i = 0; i < n; ++i) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        q.push_back({x1 + offset, y1 + offset, y2 + offset, true});
        q.push_back({x2 + offset, y2 + offset, y1 + offset, false});
    }

    std::sort(q.begin(), q.end(), [](const Query& a, const Query& b) {
        if (a.x == b.x)
            return a.is_open > b.is_open;
        return a.x < b.x;
    });
    SegmentTreebuild();
    ll x_max = 0, y_max = 0, max = 0;

    for (auto i = 0ull; i < q.size(); i++) {
        if (q[i].is_open)
            update(0, q[i].y1 + N - 1, q[i].y2 + N, N - 1, 2 * N - 1, 1);
        else
            update(0, q[i].y2 + N - 1, q[i].y1 + N, N - 1, 2 * N - 1, -1);

        auto res = t[0];
        if (res.max > max) {
            max = res.max;
            y_max = res.y;
            x_max = q[i].x;
        }
    }

    std::cout << max << '\n' << x_max - offset << ' ' << y_max - offset << '\n';
    return 0;
}