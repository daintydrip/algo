#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Recursive approach
bool subsetSumRecursive(int target, const vector<int>& arr, int n, vector<int>& subset) {
    if (target == 0)
        return true;
    if (n == 0)
        return false;

    if (arr[n - 1] > target)
        return subsetSumRecursive(target, arr, n - 1, subset);

    bool include = subsetSumRecursive(target - arr[n - 1], arr, n - 1, subset);
    bool exclude = subsetSumRecursive(target, arr, n - 1, subset);
    
    if (include) {
        subset[n - 1] = 1;
        return true;
    } else if (exclude) {
        subset[n - 1] = 0;
        return true;
    }

    return false;
}

// Memoized recursive approach
bool subsetSumMemoized(int target, const vector<int>& arr, int n, vector<vector<int>>& dp, vector<int>& subset) {
    if (target == 0)
        return true;
    if (n == 0)
        return false;

    if (dp[n][target] != -1)
        return dp[n][target];

    if (arr[n - 1] > target)
        return dp[n][target] = subsetSumMemoized(target, arr, n - 1, dp, subset);

    bool include = subsetSumMemoized(target - arr[n - 1], arr, n - 1, dp, subset);
    bool exclude = subsetSumMemoized(target, arr, n - 1, dp, subset);

    if (include) {
        subset[n - 1] = 1;
        return dp[n][target] = true;
    } else if (exclude) {
        subset[n - 1] = 0;
        return dp[n][target] = true;
    }

    return dp[n][target] = false;
}

// Iterative approach
bool subsetSumIterative(int target, const vector<int>& arr, vector<int>& subset) {
    int n = arr.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    for (int i = 0; i <= n; ++i)
        dp[i][0] = true;

    for (int i = 1; i <= n; ++i) {
        for (int t = 1; t <= target; ++t) {
            if (arr[i - 1] <= t) {
                dp[i][t] = dp[i - 1][t - arr[i - 1]] || dp[i - 1][t];
            } else {
                dp[i][t] = dp[i - 1][t];
            }
        }
    }

    if (!dp[n][target])
        return false;

    int i = n, t = target;
    while (i > 0 && t > 0) {
        if (dp[i][t] && !dp[i - 1][t - arr[i - 1]]) {
            subset[i - 1] = 1;
            t -= arr[i - 1];
        }
        --i;
    }

    return true;
}

int main() {
    vector<int> arr = {2, 3, 7, 8, 10};
    int target = 11;
    int n = arr.size();

    cout << endl;
    // Recursive
    vector<int> subset(n, 0);
    bool result = subsetSumRecursive(target, arr, n, subset);
    if (result) {
        cout << "Recursive: Possible" << endl;
        cout << "Subset: ";
        for (int i = 0; i < n; ++i)
            cout << subset[i] << " ";
        cout << endl;
    } else {
        cout << "Recursive: Not possible" << endl;
    }

    // Memoized recursive
    subset.assign(n, 0);
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));
    result = subsetSumMemoized(target, arr, n, dp, subset);
    if (result) {
        cout << "Memoized Recursive: Possible" << endl;
        cout << "Subset: ";
        for (int i = 0; i < n; ++i)
            cout << subset[i] << " ";
        cout << endl;
    } else {
        cout << "Memoized Recursive: Not possible" << endl;
    }

    // Iterative
    subset.assign(n, 0);
    result = subsetSumIterative(target, arr, subset);
    if (result) {
        cout << "Iterative: Possible" << endl;
        cout << "Subset: ";
        for (int i = 0; i < n; ++i)
            cout << subset[i] << " ";
        cout << endl;
    } else {
        cout << "Iterative: Not possible" << endl;
    }

    return 0;
}
