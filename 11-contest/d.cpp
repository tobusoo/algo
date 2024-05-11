#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

#define INF LONG_LONG_MAX

using ll = long long;

int main()
{
    ll l, n;
    std::cin >> l >> n;
    std::vector<ll> a(n + 2, 0);
    std::vector<std::vector<ll>> dp(n + 2, std::vector<ll>(n + 2, 0));
    for (ll i = 1; i <= n; i++)
        std::cin >> a[i];
    a[n + 1] = l;

    for (ll i = n + 1; i >= 0; i--) {
        for (ll j = i + 1; j <= n + 1; j++) {
            if (j - i == 1) {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = INF;
            for (ll k = i + 1; k < j; k++) {
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j] + a[j] - a[i]);
            }
        }
    }

    std::cout << dp[0][n + 1] << '\n';
    return 0;
}