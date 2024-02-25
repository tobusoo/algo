#include <algorithm>
#include <iostream>
#include <vector>

void count_sort(std::vector<char>& v)
{
    auto max = std::max_element(v.begin(), v.end());
    size_t n = *max - 'A' + 1;
    std::vector<size_t> temp(n);
    for (auto&& i : v) {
        temp[i - 'A']++;
    }
    int k = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < temp[i]; j++) {
            v[k++] = 'A' + i;
        }
    }
}

int main()
{
    size_t n = 0;
    std::cin >> n;
    std::vector<char> v;
    for (size_t i = 0; i < n; i++) {
        char temp;
        std::cin >> temp;
        v.push_back(temp);
    }

    if (v.size() == 1) {
        std::cout << v[0] << '\n';
        return 0;
    }
    count_sort(v);

    std::string str;
    char loh = '\0';
    bool flag_idk = false;
    for (size_t i = 1; i < v.size(); i++) {
        size_t str_size = str.size();
        if (v[i] == v[i - 1]) {
            str = str.substr(0, str_size / 2) + std::string(2, v[i]) + str.substr(str_size / 2);
            i++;
        } else if (!flag_idk) {
            loh = v[i - 1];
            flag_idk = true;
        }
    }
    if (v.size() % 2 != 0 && !flag_idk) {
        size_t str_size = str.size();
        str = str.substr(0, str_size / 2) + std::string(1, v[v.size() - 1]) + str.substr(str_size / 2);
    }

    if (flag_idk) {
        size_t str_size = str.size();
        str = str.substr(0, str_size / 2) + std::string(1, loh) + str.substr(str_size / 2);
    }
    std::cout << str << '\n';

    return 0;
}