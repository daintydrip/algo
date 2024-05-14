#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int comparisons = 0; // Global variable to track comparisons

int partition(int a[], int start, int end) {
    int pivot = a[end]; // pivot element
    int i = (start - 1); // Index of smaller element

    // Check if the pivot is the smallest or largest element
    if (a[start] > pivot) {
        swap(a[start], a[end]); // Swap the first and last elements
        end--; // Update end index as pivot is now in place
    } else if (a[end - 1] < pivot) {
        swap(a[end - 1], a[end]); // Swap the element before pivot
        end--; // Update end index as pivot is now in place
    }

    for (int j = start; j <= end - 1; j++) {
        comparisons++; // Count each comparison

        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[end]);
    return (i + 1);
}

void quickSort(int a[], int start, int end) {
    if (start < end) {
        int p = partition(a, start, end);
        quickSort(a, start, p - 1); // Recursive call for left subarray
        quickSort(a, p + 1, end);  // Recursive call for right subarray
    }
}

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

// Function to generate an array with random elements
void generateRandomArray(int a[], int n) {
    srand(time(0)); // Seed the random number generator

    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100; // Generate random numbers between 0 and 99
    }
}

int main() {
    int n = 80; // Array size (adjust as needed)

    // **Best case scenario (already sorted array):**
    int bestCaseArr[n];
    for (int i = 0; i < n; i++) {
        bestCaseArr[i] = i; // Create an array in ascending order
    }
    comparisons = 0; // Reset comparisons counter

    cout << "**Best case (already sorted):**" << endl;
    printArray(bestCaseArr, n);
    quickSort(bestCaseArr, 0, n - 1);
    cout << "Comparisons: " << comparisons << endl << endl;

    // **Worst case scenario (reverse sorted array):**
    int worstCaseArr[n];
    for (int i = 0; i < n; i++) {
        worstCaseArr[i] = n - 1 - i; // Create an array in descending order
    }
    comparisons = 0; // Reset comparisons counter

    cout << "**Worst case (reverse sorted):**" << endl;
    printArray(worstCaseArr, n);
    quickSort(worstCaseArr, 0, n - 1);
    cout << "Comparisons: " << comparisons << endl << endl;

    // **Average case scenario (randomly shuffled array):**
    int avgCaseArr[n];
    generateRandomArray(avgCaseArr, n); // Generate random elements
    comparisons = 0; // Reset comparisons counter

    cout << "**Average case (randomly shuffled):**" << endl;
    printArray(avgCaseArr, n);
    quickSort(avgCaseArr, 0, n - 1);
    cout << "Comparisons: " << comparisons << endl;

    return 0;
}