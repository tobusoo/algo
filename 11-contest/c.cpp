#include <iostream>
#include <vector>

using ll = long long;

int main()
{
    std::string s;
    std::cin >> s;
    ll n = s.length();
    std::string dp[n + 1][n + 1];

    auto str_max = [](const std::string& a, const std::string& b) -> auto {
        if (a.length() >= b.length())
            return a;
        return b;
    };

    for (ll i = 0; i < n; i++)
        dp[i][i] = s[i];

    for (ll i = 1; i < n; i++) {
        for (ll j = i; j < n; j++) {
            ll g = j - i;
            if (s[g] != s[j]) {
                dp[g][j] = str_max(dp[g][j - 1], dp[g + 1][j]);
            } else {
                dp[g][j] = str_max(dp[g][j - 1], str_max(dp[g + 1][j], s[g] + dp[g + 1][j - 1] + s[j]));
            }
        }
    }

    std::cout << dp[0][n - 1].length() << '\n';
    std::cout << dp[0][n - 1] << '\n';

    return 0;
}