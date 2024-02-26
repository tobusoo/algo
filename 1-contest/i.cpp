#include <iostream>
#include <vector>

int main()
{
    size_t n = 0;
    std::cin >> n;
    std::vector<int> v(n, 0);

    size_t max = n + 1;
    size_t iter = 1;
    std::cout << 1 << ' ';
    for (size_t i = 0; i < n - 1; i++) {
        size_t temp;
        std::cin >> temp;
        v[temp - 1] = 1;
        if (temp == max - 1 && v[temp - 2] == 0) {
            max--;
            std::cout << iter << ' ';
        } else if (temp == max - 1 && v[temp - 2] == 1) {
            int i = temp - 2;
            while (i >= 0 && v[i] == 1) {
                max--;
                iter--;
                i--;
            }
            max--;
            i--;
            std::cout << iter << ' ';
        } else {
            iter++;
            std::cout << iter << ' ';
        }
    }
    std::cout << 1 << '\n';

    return 0;
}