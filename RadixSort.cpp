#include <iostream>
#include <vector>
#include <cstdint>
using std::cin;
using std::cout;

const int max_N = 1000000;
uint64_t arr[max_N];
uint64_t tmp[max_N];

inline int BinarySearch(const uint64_t* arr, int left, int right, uint64_t key) {

    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        (arr[mid] < key) ? (left = mid + 1) : (right = mid - 1);
    }
    return left;
}

inline void swap(uint64_t& a, uint64_t& b) {

    if (&a != &b) {
        a ^= b;
        b ^= a;
        a ^= b;
    }
}

inline int Partition(uint64_t* arr, int low, int high) {

    int mid = low + ((high - low) >> 1);
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);

    uint64_t pivot = arr[mid];
    swap(arr[mid], arr[high - 1]);

    int i = low;
    int j = high - 1;
    while (true) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }
    swap(arr[i], arr[high - 1]);
    return i;
}

void QuickSort(uint64_t* arr, int low, int high) {

    while (high - low > 32) {
        int p = Partition(arr, low, high);
        if (p - low < high - p) {
            QuickSort(arr, low, p - 1);
            low = p + 1;
        } else {
            QuickSort(arr, p + 1, high);
            high = p - 1;
        }
    }

    for (int i = low + 1; i <= high; ++i) {
        uint64_t key = arr[i];
        int pos = BinarySearch(arr, low, i - 1, key);
        for (int j = i - 1; j >= pos; --j) {
            arr[j + 1] = arr[j];
        }
        arr[pos] = key;
    }
}

void radixSort(uint64_t* arr, int n) {

    const int passes = 8;
    const int bits = 8;
    const int base = 1 << bits;
    int count[base];

    for (int pass = 0; pass < passes; ++pass) {
        int shift = pass * bits;
        std::fill(count, count + base, 0);

        for (int i = 0; i < n; ++i)
            count[(arr[i] >> shift) & (base - 1)]++;

        for (int i = 1; i < base; ++i)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; --i) {
            int idx = (arr[i] >> shift) & (base - 1);
            tmp[--count[idx]] = arr[i];
        }

        for (int i = 0; i < n; ++i)
            arr[i] = tmp[i];
    }

    QuickSort(arr, 0, n - 1);
}

int main() {

    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    radixSort(arr, N);

    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << arr[i];
    }
    cout << '\n';

    return 0;
}