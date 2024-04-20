#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

typedef long long ll;

ll mod = 1000000007;

struct Fenwick {
    std::vector<std::pair<ll, ll>> f;
    ll size;

    Fenwick(ll size) : size(size)
    {
        f.assign(size, {0, 0});
    }

    void update(ll i, const std::pair<ll, ll>& v)
    {
        while (i < size) {
            if (f[i].first < v.first)
                f[i] = v;
            else if (f[i].first == v.first)
                f[i].second = (f[i].second + v.second) % mod;

            i = i | (i + 1);
        }
    }

    std::pair<ll, ll> query(ll i)
    {
        std::pair<ll, ll> ans = {0, 1};
        while (0 <= i) {
            if (ans.first < f[i].first)
                ans = f[i];
            else if (f[i].first == ans.first)
                ans.second = (f[i].second + ans.second) % mod;

            i = (i & (i + 1)) - 1;
        }

        return ans;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll n;
    std::cin >> n;
    std::vector<ll> v(n, 0);
    for (ll i = 0; i < n; i++) {
        std::cin >> v[i];
    }

    ll j = 0;
    std::set<ll> s(v.begin(), v.end());
    std::unordered_map<ll, ll> id;

    for (auto&& i : s) {
        id[i] = j++;
    }

    Fenwick f(s.size() + 1);
    for (auto&& i : v) {
        ll index = id[i];
        auto k = f.query(index - 1);
        f.update(index, {k.first + 1, k.second});
    }

    std::cout << f.query(n - 1).second << '\n';

    return 0;
}