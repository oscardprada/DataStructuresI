#include <iostream>

const int max_N = 100000;
int arr[max_N];

inline int BinarySearch(const int* arr, int left, int right, int key) {
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        (arr[mid] < key) ? (left = mid + 1) : (right = mid - 1);
    }
    return left;
}

inline void swap(int& a, int& b) {
    if (&a != &b) {
        a ^= b;
        b ^= a;
        a ^= b;
    }
}

inline int Partition(int* arr, int low, int high) {
    int mid = low + ((high - low) >> 1);
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    
    int pivot = arr[mid];
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

void QuickSort(int* arr, int low, int high) {
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
        int key = arr[i];
        int pos = BinarySearch(arr, low, i - 1, key);
        for (int j = i - 1; j >= pos; --j) {
            arr[j + 1] = arr[j];
        }
        arr[pos] = key;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    for (int i = 0; i < N; ++i) {
        std::cin >> arr[i];
    }
    
    QuickSort(arr, 0, N - 1);
    
    for (int i = 0; i < N; ++i) {
        if (i) std::cout << ' ';
        std::cout << arr[i];
    }
    std::cout << '\n';
    
    return 0;
}