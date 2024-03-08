#include <iostream>

struct Heap {
    int* nodes;
    int size;

    void print()
    {
        for (int i = 1; i <= size; i++) {
            std::cout << nodes[i] << ' ';
        }
        std::cout << '\n';
    }

    Heap(int capacity = 1000000) : size(0)
    {
        try {
            nodes = new int[capacity + 1];
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
        nodes[0] = INT32_MAX;
    };

    void insert(int x)
    {
        size++;
        nodes[size] = x;

        int i = size;
        int parent = size / 2;

        while (i > 0 && nodes[parent] < nodes[i]) {
            std::swap(nodes[parent], nodes[i]);
            i = parent;
            parent = i / 2;
        }
    }

    void heapify(int index)
    {
        while (true) {
            int left = 2 * index;
            int right = left + 1;
            int largest = index;
            if (left <= size && nodes[left] > nodes[largest])
                largest = left;
            if (right <= size && nodes[right] > nodes[largest])
                largest = right;
            if (largest == index)
                break;

            std::swap(nodes[index], nodes[largest]);
            index = largest;
        }
    }

    int extract_max()
    {
        int max = nodes[1];
        nodes[1] = nodes[size--];

        heapify(1);

        return max;
    }

    ~Heap()
    {
        delete[] nodes;
    }
};

int main()
{
    size_t n;
    std::cin >> n;
    Heap h(n);
    int temp;

    for (size_t i = 0; i < n; i++) {
        std::cin >> temp;
        h.insert(temp);
    }

    for (size_t i = 1; i < n; i++) {
        h.nodes[h.size] = h.extract_max();
        h.heapify(i);
    }
    for (size_t i = 0; i < n; i++) {
        std::cout << h.nodes[i + 1] << ' ';
    }
    std::cout << '\n';

    return 0;
}