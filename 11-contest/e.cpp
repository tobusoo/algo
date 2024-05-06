#include <iostream>
#include <vector>

int main()
{
    std::string s, temp, min;
    std::cin >> s;
    int n = s.size();
    std::vector<std::vector<std::string>> dp(n, std::vector<std::string>(n));

    for (int len = 1; len <= n; len++) {
        for (int left = 0; left + len - 1 < n; left++) {
            int right = left + len - 1;
            min = s.substr(left, len);
            if (len > 4) {
                for (int right1 = left; right1 < right; right1++) {
                    int left2 = right1 + 1;
                    temp = dp[left][right1] + dp[left2][right];
                    if (temp.size() < min.size())
                        min = temp;
                }
                for (int p = 1; p < len; p++) {
                    if (len % p == 0) {
                        bool is_pereodic = true;
                        for (int i = left + p; i <= right; i++) {
                            if (s[i] != s[i - p]) {
                                is_pereodic = false;
                                break;
                            }
                        }
                        if (is_pereodic) {
                            temp = std::to_string(len / p) + "(" + dp[left][left + p - 1] + ")";
                            if (temp.size() < min.size())
                                min = temp;
                        }
                    }
                }
            }
            dp[left][right] = min;
        }
    }

    std::cout << dp[0][n - 1] << '\n';

    return 0;
}