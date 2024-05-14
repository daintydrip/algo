#include <iostream>
#include <algorithm>
using namespace std;

struct Job
{
    int start, finish, weight;
};

bool jobComparator(Job s1, Job s2)
{
    return (s1.finish < s2.finish);
}

int latestNonConflict(Job arr[], int i)
{
    for (int j=i-1; j>=0; j--)
    {
        if (arr[j].finish <= arr[i-1].start)
            return j;
    }
    return -1;
}

int findMaxweightRec(Job arr[], int n)
{
    // Base case
    if (n == 1) return arr[n-1].weight;

    int inclProf = arr[n-1].weight;
    int i = latestNonConflict(arr, n);
    if (i != -1)
    inclProf += findMaxweightRec(arr, i+1);

    int exclProf = findMaxweightRec(arr, n-1);

    return max(inclProf,  exclProf);
}

int findMaxweight(Job arr[], int n)
{
    // Sort jobs according to finish time
    sort(arr, arr+n, jobComparator);
    return findMaxweightRec(arr, n);
}

int main()
{
    Job arr[] = {{1, 3, 5}, {2, 5, 6}, {4, 6, 5}, {6, 7, 4}};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << endl << "The Optimal Weight is " << findMaxweight(arr, n) << endl;
    return 0;
}