#include <climits>
#include <iostream>
#include <vector>

typedef long long ll;
#define INF LLONG_MAX

class SegmentTree {
public:
    std::vector<ll> t;
    std::vector<ll> p; // promises
    std::vector<ll> s; // segments
    ll size;

    ll func(ll a, ll b)
    {
        return a + b;
    }

    void up(ll i, ll l, ll r)
    {
        if (i >= size || p[i] == INF)
            return;

        t[i] = p[i] * (r - l + 1);
        s[i] = p[i];
        if (l == r)
            return;

        if (i * 2 < size) {
            p[i * 2] = p[i];
        }
        if (i * 2 + 1 < size) {
            p[i * 2 + 1] = p[i];
        }

        p[i] = INF;
    }

    SegmentTree(ll size) : t(4 * size, 0), p(4 * size, INF), s(4 * size, 0), size(4 * size)
    {
    }

    ll query(ll i, ll left, ll right, ll i_left, ll i_right)
    {
        if (i_left > i_right) {
            return 0;
        }
        if (left == i_left && right == i_right) {
            up(i, left, right);
            return t[i];
        }

        up(i, left, right);
        ll mid = (left + right) >> 1;
        auto left_son = query(i * 2, left, mid, i_left, std::min(mid, i_right));
        auto right_son = query(i * 2 + 1, mid + 1, right, std::max(mid + 1, i_left), i_right);

        return func(left_son, right_son);
    }

    bool is_leftblack(ll v, ll l, ll r)
    {
        up(v, l, r);
        if (l == r)
            return t[v] == 1;

        return is_leftblack(v * 2, l, (l + r) >> 1);
    }

    bool is_rightblack(ll v, ll l, ll r)
    {
        up(v, l, r);
        if (l == r)
            return t[v] == 1;

        return is_rightblack(v * 2 + 1, ((l + r) >> 1) + 1, r);
    }

    void update(ll v, ll tl, ll tr, ll l, ll r, ll equal)
    {
        if (l > r || tl > tr)
            return;
        if (tl >= l && tr <= r && v < size) {
            p[v] = equal;
            up(v, tl, tr);
        } else {
            up(v, tl, tr);
            ll tm = (tl + tr) >> 1;
            update(v * 2, tl, tm, l, std::min(r, tm), equal);
            update(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, equal);

            bool left = is_rightblack(v * 2, tl, tm);
            bool right = is_leftblack(v * 2 + 1, tm + 1, tr);

            t[v] = t[v * 2] + t[v * 2 + 1];
            s[v] = s[v * 2] + s[v * 2 + 1];
            if (left && right)
                s[v]--;
        }
    }
};

int main()
{
    ll n;
    std::cin >> n;
    std::vector<std::vector<ll>> v;

    char type;
    ll x, l;
    for (ll i = 0; i < n; i++) {
        std::cin >> type >> x >> l;
        v.push_back({type, x, l});
    }

    ll size = 1000000;
    SegmentTree s(size);
    ll offset = 500000;

    for (ll i = 0; i < n; i++) {
        type = v[i][0];
        x = v[i][1];
        l = v[i][2];
        if (type == 'W') {
            s.update(1, 0, size - 1, x + offset, x + l - 1 + offset, 0);
        } else {
            s.update(1, 0, size - 1, x + offset, x + l - 1 + offset, 1);
        }

        std::cout << s.s[1] << ' ' << s.t[1] << '\n';
    }

    return 0;
}