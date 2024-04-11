#include <iostream>
#include <vector>

typedef long long ll;

std::pair<ll, ll> combine(const std::pair<ll, ll>& a, const std::pair<ll, ll>& b)
{
    if (a.first < b.first)
        return a;
    if (b.first < a.first)
        return b;

    return {a.first, a.second + b.second};
}

class DO {
public:
    const ll null;
    std::vector<std::pair<ll, ll>> t;

    DO(ll null, const std::vector<ll>& a) : null(null), t(4 * a.size(), std::pair<ll, ll>{null, 1})
    {
        build(a, 1, 0, a.size() - 1);
    }

    void build(const std::vector<ll>& a, ll i, ll left, ll right)
    {
        if (left == right) {
            t[i] = {a[left], 1};
        } else {
            ll mid = (left + right) >> 1;
            build(a, i * 2, left, mid);
            build(a, i * 2 + 1, mid + 1, right);

            t[i] = combine(t[i * 2], t[i * 2 + 1]);
        }
    }

    std::pair<ll, ll> query(ll i, ll left, ll right, ll i_left, ll i_right)
    {
        if (i_left > i_right)
            return {null, 0};
        if (left == i_left && right == i_right)
            return t[i];

        ll mid = (left + right) >> 1;
        auto ans = combine(
                query(i * 2, left, mid, i_left, std::min(mid, i_right)),
                query(i * 2 + 1, mid + 1, right, std::max(mid + 1, i_left), i_right));

        return ans;
    }

    void update(ll i, ll left, ll right, ll update_index, ll value)
    {
        if (left == right)
            t[i] = {value, 1};
        else {
            ll mid = (left + right) >> 1;
            if (update_index <= mid)
                update(i * 2, left, mid, update_index, value);
            else
                update(i * 2 + 1, mid + 1, right, update_index, value);

            t[i] = combine(t[i * 2], t[i * 2 + 1]);
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
    for (ll i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    DO d(INT32_MAX, a);

    ll l = 0;
    ll r = a.size() - 1;

    ll status, v, u;
    for (ll i = 0; i < m; i++) {
        std::cin >> status >> v >> u;
        if (status == 1)
            d.update(1, l, r, v, u);
        else {
            auto ans = d.query(1, l, r, v, u - 1);
            std::cout << ans.first << ' ' << ans.second << '\n';
        }
    }

    return 0;
}