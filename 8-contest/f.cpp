#include <algorithm>
#include <iostream>
#include <vector>

#define N 100001
typedef long long ll;

struct Fenwick {
    ll f[N];
    ll size;

    ll get(ll i)
    {
        ll ans = 0;
        for (; i; i -= i & -i) {
            ans += f[i];
        }
        return ans;
    }

    void up(ll i)
    {
        for (; i <= size; i += i & -i) {
            f[i]++;
        }
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::pair<ll, ll> arr[N];
    ll idx[N];
    Fenwick f;

    std::cin >> f.size;
    for (ll i = 1; i <= f.size; ++i) {
        std::cin >> arr[i].first;
        arr[i].second = i;
    }

    std::sort(arr + 1, arr + 1 + f.size, std::greater<std::pair<ll, ll>>());

    for (int i = 1; i <= f.size; ++i) {
        idx[arr[i].second] = i;
    }

    ll ans = 0;
    for (int i = 1; i <= f.size; ++i) {
        auto temp = f.get(idx[i]);
        ans += temp * (f.size - i - idx[i] + temp + 1);
        f.up(idx[i]);
    }

    std::cout << ans << '\n';

    return 0;
}