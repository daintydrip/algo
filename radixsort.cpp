#include <iostream>
#include <vector>

using namespace std;

int getMax(vector<int>& arr) {
    int maxElem = arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] > maxElem) {
            maxElem = arr[i];
        }
    }
    return maxElem;
}

void countingSort(vector<int>& arr, int exp) {
    vector<int> output(arr.size());
    vector<int> count(10, 0);

    for (int i = 0; i < arr.size(); ++i)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; ++i)
        count[i] += count[i - 1];

    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < arr.size(); ++i)
        arr[i] = output[i];
}

void radixSort(vector<int>& arr) {
    int maxElem = getMax(arr);

    for (int exp = 1; maxElem / exp > 0; exp *= 10)
        countingSort(arr, exp);
}

int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    
    cout << "Original array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    radixSort(arr);

    cout << "Sorted array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    return 0;
}
