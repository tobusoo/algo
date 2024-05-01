#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using ll = long long;
using ull = unsigned long long;

struct PromiseNode {
    ll add;
    ll len;
};

struct Event {
    ll x;
    ll y1;
    ll y2;
    ll type;
};

struct SegmentTree {
    ll n;
    std::vector<ll> t;
    std::vector<PromiseNode> p;

    SegmentTree(std::vector<ll>& distance) : n(distance.size()), t(4 * n, 0), p(4 * n, {0, 0})
    {
        build(1, 0, n, distance);
    }

    void build(ll v, ll l, ll r, std::vector<ll>& distance)
    {
        if (l + 1 == r) {
            p[v].len = distance[l];
        } else {
            ll m = (l + r) >> 1;
            build(2 * v, l, m, distance);
            build(2 * v + 1, m, r, distance);
            p[v].len = p[v * 2].len + p[v * 2 + 1].len;
        }
    }

    void up(ll v)
    {
        t[2 * v] += p[v].add;
        t[2 * v + 1] += p[v].add;
        p[2 * v].add += p[v].add;
        p[2 * v + 1].add += p[v].add;

        p[v].add = 0;
    }

    void update(ll v, ll l, ll r, ll lx, ll rx, ll val)
    {
        if (r <= lx || rx <= l) {
            return;
        }
        if (lx <= l && r <= rx) {
            p[v].add += val;
            t[v] += val;
            return;
        }

        up(v);
        ll m = (l + r) >> 1;
        update(2 * v, l, m, lx, rx, val);
        update(2 * v + 1, m, r, lx, rx, val);

        if (t[2 * v] == t[2 * v + 1]) {
            t[v] = t[2 * v];
            p[v].len = p[v * 2].len + p[v * 2 + 1].len;
        } else if (t[2 * v] < t[2 * v + 1]) {
            t[v] = t[2 * v];
            p[v].len = p[v * 2].len;
        } else {
            t[v] = t[2 * v + 1];
            p[v].len = p[v * 2 + 1].len;
        }
    }

    void update(ll lx, ll rx, ll val)
    {
        update(1, 0, n, lx, rx, val);
    }

    ll query()
    {
        return (t[1] ? 0 : p[1].len);
    }
};

int32_t main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll n;
    std::cin >> n;

    std::vector<Event> ev(2 * n);
    std::set<ll> y;
    ll x1, y1, x2, y2;

    for (ll i = 0; i < n; ++i) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2 || y1 > y2) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        x2++;
        y2++;
        y.insert(y1);
        y.insert(y2);
        ev[2 * i] = {x1, y1, y2, 1};
        ev[2 * i + 1] = {x2, y1, y2, -1};
    }

    std::sort(ev.begin(), ev.end(), [](Event& a, Event& b) {
        return std::make_pair(a.x, -a.type) < std::make_pair(b.x, -b.type);
    });

    std::vector<ll> y_sorted;
    for (auto&& i : y) {
        y_sorted.push_back(i);
    }

    std::map<ll, ll> y_id;
    for (ll i = 0; i < y_sorted.size(); ++i) {
        y_id[y_sorted[i]] = i;
    }

    std::vector<ll> distance(y_sorted.size() - 1);
    for (ll i = 1; i < y_sorted.size(); ++i) {
        distance[i - 1] = y_sorted[i] - y_sorted[i - 1];
    }
    ll sum = accumulate(distance.begin(), distance.end(), 0ll);
    SegmentTree seg_tree(distance);

    ll ans = 0;
    ll prev_x = ev[0].x;
    for (auto&& i : ev) {
        ans += (sum - seg_tree.query()) * (i.x - prev_x);
        seg_tree.update(y_id[i.y1], y_id[i.y2], i.type);
        prev_x = i.x;
    }
    std::cout << ans << '\n';

    return 0;
}