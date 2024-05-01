#include <iostream>
#include <vector>

typedef long long ll;

class DO {
public:
    using BIN_FUNC = ll(ll, ll);

    const ll null;
    std::vector<ll> t;
    BIN_FUNC* func;

    DO(ll null, BIN_FUNC* f, const std::vector<ll>& a) : null(null), t(4 * a.size(), null), func(f)
    {
        build(a, 1, 0, a.size() - 1);
    }

    void build(const std::vector<ll>& a, ll i, ll left, ll right)
    {
        if (left == right) {
            t[i] = a[left];
        } else {
            ll mid = (left + right) >> 1;
            build(a, i * 2, left, mid);
            build(a, i * 2 + 1, mid + 1, right);
            t[i] = func(t[i * 2], t[i * 2 + 1]);
        }
    }

    ll query(ll i, ll left, ll right, ll i_left, ll i_right)
    {
        if (i_left > i_right)
            return null;
        if (left == i_left && right == i_right)
            return t[i];

        ll mid = (left + right) >> 1;
        ll left_son = query(i * 2, left, mid, i_left, std::min(mid, i_right));
        ll right_son = query(i * 2 + 1, mid + 1, right, std::max(mid + 1, i_left), i_right);

        return func(left_son, right_son);
    }

    void update(ll i, ll left, ll right, ll update_index, ll value)
    {
        if (left == right)
            t[i] = value;
        else {
            ll mid = (left + right) >> 1;
            if (update_index <= mid)
                update(i * 2, left, mid, update_index, value);
            else
                update(i * 2 + 1, mid + 1, right, update_index, value);
            t[i] = func(t[i * 2], t[i * 2 + 1]);
        }
    }
};

inline ll sum(ll a, ll b) noexcept
{
    return a + b;
}

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
    DO d(0, sum, a);

    ll l = 0;
    ll r = a.size() - 1;

    ll status, v, u;
    for (ll i = 0; i < m; i++) {
        std::cin >> status >> v >> u;
        if (status == 1)
            d.update(1, l, r, v, u);
        else
            std::cout << d.query(1, l, r, v, u - 1) << '\n';
    }

    return 0;
}