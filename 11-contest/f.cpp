#include <iostream>
#include <vector>

using ll = long long;

int main()
{
    ll n, m;
    std::cin >> n >> m;
    std::vector<ll> a(2 * m, 0);

    ll j = 0;
    for (ll i = 0; i < m; i++) {
        std::cin >> a[j];
        a[j + 1] = a[j];
        j += 2;
    }
    m *= 2;

    ll ans = 0;
    ll k = 30;
    bool find_solution = false;

    for (ll i = 0; i < (1 << m); i++) {
        ll sum = 0, digit_cnt = 0;
        for (ll j = 0; j < m; j++) {
            if ((i >> j) & 1) {
                sum += a[j];
                digit_cnt++;
            }
        }
        if (sum == n && digit_cnt < k) {
            ans = i;
            k = digit_cnt;
            find_solution = true;
        } else if (sum > n && !find_solution)
            ans = 0;
        else if (!find_solution && sum < n)
            ans = -1;
    }

    if (ans != 0 && ans != -1) {
        std::cout << k << '\n';
        for (ll j = 0; j < m; j++) {
            if ((ans >> j) & 1)
                std::cout << a[j] << ' ';
        }
        std::cout << '\n';
    } else
        std::cout << ans << '\n';

    return 0;
}