#include <algorithm>
#include <iostream>
#include <vector>

std::string ans_str, str;

std::vector<std::vector<int>> dp;
std::vector<char> check(300, '?');

void solve(int l, int r, int n)
{
    if (l > r)
        return;

    if (l == r) {
        ans_str[r] = '/';
        return;
    }

    if (dp[l][r] == dp[l][r - 1] + 1) {
        ans_str[r] = '/';

        solve(l, r - 1, n);

        return;
    }

    for (int a = l; a < r; ++a) {
        if (check[str[r]] == str[a]) {
            if (a == l) {
                if (dp[l][r] == dp[l + 1][r - 1]) {
                    solve(l + 1, r - 1, n);
                    return;
                }

            } else if (dp[l][r] == dp[l][a - 1] + dp[a][r]) {
                solve(l, a - 1, n);
                solve(a, r, n);

                return;
            }
        }
    }
}

int main()
{
    std::cin >> str;

    int n = str.size();

    dp.resize(n, std::vector<int>(n));

    check[')'] = '(';
    check[']'] = '[';
    check['}'] = '{';

    for (int i = 0; i < n; ++i)
        dp[i][i] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j + i >= n)
                break;

            int l = j;
            int r = j + i;

            dp[l][r] = dp[l][r - 1] + 1;

            for (int a = l; a < r; ++a) {
                if (check[str[r]] == str[a]) {
                    if (a == l)
                        dp[l][r] = std::min(dp[l][r], dp[l + 1][r - 1]);
                    else
                        dp[l][r] = std::min(dp[l][r], dp[l][a - 1] + dp[a][r]);
                }
            }
        }
    }

    ans_str.resize(n, '?');

    solve(0, n - 1, n);

    for (int i = 0; i < n; ++i)
        if (ans_str[i] == '?')
            std::cout << str[i];

    std::cout << '\n';
    return 0;
}