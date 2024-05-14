#include <iostream>
#include <vector>

using namespace std;

void countSort(vector<int>& arr) {
    int maxElem = arr[0];
    int minElem = arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] > maxElem) {
            maxElem = arr[i];
        }
        if (arr[i] < minElem) {
            minElem = arr[i];
        }
    }

    int range = maxElem - minElem + 1;

    vector<int> count(range), output(arr.size());
    for (int i = 0; i < arr.size(); i++)
        count[arr[i] - minElem]++;

    for (int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];

    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - minElem] - 1] = arr[i];
        count[arr[i] - minElem]--;
    }

    for (int i = 0; i < arr.size(); i++)
        arr[i] = output[i];
}

int main() {
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};
    
    cout << "Original array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    countSort(arr);

    cout << "Sorted array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    return 0;
}
