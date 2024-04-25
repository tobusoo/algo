#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

typedef long long ll;

#define INF LLONG_MAX

struct Node {
    ll value;
    ll equal;
    ll add;
};

struct SegmentTree {
    std::vector<Node> t;
    SegmentTree(ll n)
    {
        t.resize(4 * n, {0, INF, 0});
    }

    void push_set(ll v, ll lx, ll rx)
    {
        if (t[v].equal == INF) {
            return;
        }
        t[v].value = (rx - lx) * t[v].equal;
        if (rx - lx != 1) {
            t[2 * v + 1].equal = t[2 * v + 2].equal = t[v].equal;
            t[2 * v + 1].add = t[2 * v + 2].add = 0;
        }
        t[v].equal = INF;
    }

    void push_add(ll v, ll lx, ll rx)
    {
        if (t[v].add == 0) {
            return;
        }
        t[v].value += (rx - lx) * t[v].add;
        if (rx - lx != 1) {
            t[2 * v + 1].add += t[v].add;
            t[2 * v + 2].add += t[v].add;
            ll m = (lx + rx) >> 1;
            push_set(2 * v + 1, lx, m);
            push_set(2 * v + 2, m, rx);
            t[2 * v + 1].equal = t[2 * v + 2].equal = INF;
        }
        t[v].add = 0;
    }

    void update_set(ll v, ll l, ll r, ll val, ll lx, ll rx)
    {
        if (t[v].add == 0) {
            push_set(v, lx, rx);
        } else {
            push_add(v, lx, rx);
        }
        if (l >= rx || r <= lx) {
            return;
        }

        if (lx >= l && rx <= r) {
            t[v].equal = val;
            if (t[v].add == 0) {
                push_set(v, lx, rx);
            } else {
                push_add(v, lx, rx);
            }

        } else {
            ll m = (lx + rx) >> 1;
            update_set(l, r, val, 2 * v + 1, lx, m);
            update_set(l, r, val, 2 * v + 2, m, rx);

            t[v] = {t[2 * v + 1].value + t[2 * v + 2].value, INF, 0};
        }
    }

    void update_add(ll v, ll l, ll r, ll val, ll lx, ll rx)
    {
        if (t[v].add == 0) {
            push_set(v, lx, rx);
        } else {
            push_add(v, lx, rx);
        }
        if (l >= rx || r <= lx) {
            return;
        }
        if (lx >= l && rx <= r) {
            t[v].add = val;
            if (t[v].add == 0) {
                push_set(v, lx, rx);
            } else {
                push_add(v, lx, rx);
            }
        } else {
            ll m = (lx + rx) >> 1;
            update_add(l, r, val, 2 * v + 1, lx, m);
            update_add(l, r, val, 2 * v + 2, m, rx);

            t[v] = {t[2 * v + 1].value + t[2 * v + 2].value, INF, 0};
        }
    }

    ll get(ll v, ll l, ll r, ll lx, ll rx)
    {
        if (t[v].add == 0) {
            push_set(v, lx, rx);
        } else {
            push_add(v, lx, rx);
        }
        if (l >= rx || r <= lx) {
            return 0;
        }
        if (lx >= l && rx <= r) {
            return t[v].value;
        }

        ll m = (lx + rx) >> 1;
        ll left = get(l, r, 2 * v + 1, lx, m);
        ll right = get(l, r, 2 * v + 2, m, rx);

        return (left + right);
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    ll n, m;

    std::cin >> n >> m;
    SegmentTree s(n);

    ll act, l, r, v;
    for (int i = 0; i < m; i++) {
        std::cin >> act;
        if (act == 1) {
            std::cin >> l >> r >> v;
            s.update_set(0, l, r, v, 0, n);
        } else if (act == 2) {
            std::cin >> l >> r >> v;
            s.update_add(0, l, r, v, 0, n);
        } else {
            std::cin >> l >> r;
            std::cout << s.get(0, l, r, 0, n) << '\n';
        }
    }

    return 0;
}