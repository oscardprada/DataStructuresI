#include <iostream>
using std::cin;
using std::cout;

bool BinarySearch(const int* begin, const int* end, int target){
    while (begin < end){
        const int* mid = begin + (end-begin)/2;
        
        if (*mid == target)
            return true;

        else if (*mid<target)
            begin = mid + 1;

        else 
            end = mid;
    }
    return false;
}

int main(){
    int N;
    cin >> N;

    int* arr = new int[N];

    for (int i = 0; i < N; ++i) {
        cin>>arr[i];
    }

    int Q;
    cin >> Q;

    while (Q--){
        int i, j, t;
        bool val;
        cin >> i >> j >> t;
        val = BinarySearch(arr + i, arr + j, t);

        if (val){
            cout << "YES\n";
        }
        else{
        cout << "NO\n";
        }
    }

delete[] arr;
return 0;
}