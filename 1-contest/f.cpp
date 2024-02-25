#include <iostream>
#include <vector>

int merge(std::vector<int>& arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int inversions = 0;

    std::vector<int> left_arr(n1);
    std::vector<int> right_arr(n2);

    for (int i = 0; i < n1; i++) {
        left_arr[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        right_arr[j] = arr[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j])
            arr[k++] = left_arr[i++];
        else {
            arr[k++] = right_arr[j++];
            inversions += n1 - i;
        }
    }

    while (i < n1) {
        arr[k++] = left_arr[i++];
    }

    while (j < n2) {
        arr[k++] = right_arr[j++];
    }

    return inversions;
}

int mergeSort(std::vector<int>& arr, int l, int r)
{
    int inversions = 0;
    if (l < r) {
        int m = l + (r - l) / 2;

        inversions += mergeSort(arr, l, m);
        inversions += mergeSort(arr, m + 1, r);

        inversions += merge(arr, l, m, r);
    }

    return inversions;
}

int main()
{
    size_t n;
    std::cin >> n;
    std::vector<int> arr;
    for (size_t i = 0; i < n; i++) {
        int temp;
        std::cin >> temp;
        arr.push_back(temp);
    }

    int inversions = mergeSort(arr, 0, arr.size() - 1);

    std::cout << inversions << '\n';
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << '\n';

    return 0;
}
