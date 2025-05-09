#include <iostream>
#include <vector>
#include <algorithm>

const int mod = 10004321;

inline void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void InsertionSort(int* arr, int low, int high) {
    for (int i = low + 1; i <= high; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int MedianOfFive(int* arr, int low, int high) {
    InsertionSort(arr, low, high);
    return low + (high - low) / 2;
}

int MedianOfMedians(int* arr, int low, int high) {
    if (high - low < 5) {
        return MedianOfFive(arr, low, high);
    }

    for (int i = low; i <= high; i += 5) {
        int groupHigh = std::min(i + 4, high);
        int medianPos = MedianOfFive(arr, i, groupHigh);
        swap(arr[medianPos], arr[low + (i - low) / 5]);
    }

    return MedianOfMedians(arr, low, low + (high - low) / 5);
}

int Partition(int* arr, int low, int high, int pivotIndex) {
    
    swap(arr[pivotIndex], arr[high]);
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

int QuickSelect(int* arr, int low, int high, int k) {

    while (low < high) {
        int pivotIndex = MedianOfMedians(arr, low, high);
        pivotIndex = Partition(arr, low, high, pivotIndex);
        if (k == pivotIndex) {
            return arr[pivotIndex];
        } else if (k < pivotIndex) {
            high = pivotIndex - 1;
        } else {
            low = pivotIndex + 1;
        }
    }
    return arr[low];
}

int KthOrderStatistic(int n, int k, int A0, int A1) {
    
    if (n == 1) return A0;
    std::vector<int> sequence(n);
    sequence[0] = A0;
    sequence[1] = A1;

    for (int i = 2; i < n; ++i) {
        sequence[i] = (static_cast<long long>(sequence[i-1]) * 123 + 
                      static_cast<long long>(sequence[i-2]) * 45) % mod;
    }
    return QuickSelect(sequence.data(), 0, n - 1, k - 1);
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k, A0, A1;
    std::cin >> n >> k >> A0 >> A1;
    
    std::cout << KthOrderStatistic(n, k, A0, A1) << '\n';
    
    return 0;
}