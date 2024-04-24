#include <algorithm>
#include <climits>
#include <iostream>
#include <numeric>
#include <vector>

typedef long long ll;
#define INF LONG_LONG_MAX

class SegmentTree {
public:
    std::vector<ll> t;
    std::vector<ll> p; // promises
    ll size;

    ll func(ll a, ll b)
    {
        return std::min(a, b);
    }

    void up(ll i)
    {
        if (i >= size)
            return;
        t[i] += p[i];
        if (i * 2 < size)
            p[i * 2] += p[i];
        if (i * 2 + 1 < size)
            p[i * 2 + 1] += p[i];
        p[i] = 0;
    }

    SegmentTree(const std::vector<ll>& a) : t(4 * a.size(), 0), p(4 * a.size(), 0), size(4 * a.size())
    {
    }

    ll query(ll i, ll left, ll right, ll i_left, ll i_right)
    {
        if (i_left > i_right) {
            return INF;
        }
        if (left == i_left && right == i_right) {
            up(i);
            return t[i];
        }

        up(i);
        ll mid = (left + right) >> 1;
        ll left_son = query(i * 2, left, mid, i_left, std::min(mid, i_right));
        ll right_son = query(i * 2 + 1, mid + 1, right, std::max(mid + 1, i_left), i_right);

        return func(left_son, right_son);
    }

    void update(ll v, ll tl, ll tr, ll l, ll r, ll add)
    {
        if (l > r || tl > tr)
            return;
        if (tl >= l && tr <= r && v < size) {
            p[v] += add;
            up(v);
        } else {
            up(v);
            ll tm = (tl + tr) >> 1;
            update(v * 2, tl, tm, l, std::min(r, tm), add);
            update(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, add);
            up(v * 2);
            up(v * 2 + 1);

            t[v] = func(t[v * 2], t[v * 2 + 1]);
        }
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll n, m;
    std::cin >> n >> m;

    std::vector<ll> a(n, 0);
    SegmentTree s(a);

    ll act, l, r, v;
    for (ll i = 0; i < m; i++) {
        std::cin >> act;
        if (act == 1) {
            std::cin >> l >> r >> v;
            s.update(1, 0, n - 1, l, r - 1, v);
        } else {
            std::cin >> l >> r;
            std::cout << s.query(1, 0, n - 1, l, r - 1) << '\n';
        }
    }

    return 0;
}