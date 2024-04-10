#include <iostream>
#include <vector>

int n, m;
int** d;

int solve(int i, int j)
{
    if (i >= 0 && j >= 0 && i < n && j < m) {
        if (d[i][j] == -1)
            d[i][j] = solve(i - 2, j - 1) + solve(i - 2, j + 1) + solve(i - 1, j - 2) + solve(i + 1, j - 2);
    } else
        return 0;

    return d[i][j];
}

int main()
{
    std::cin >> n >> m;
    d = new int*[n];

    for (int i = 0; i < n; i++)
        d[i] = new int[m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            d[i][j] = -1;
        }
    }

    d[0][0] = 1;

    std::cout << solve(n - 1, m - 1) << '\n';

    return 0;
}