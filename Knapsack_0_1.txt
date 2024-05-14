#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Recursive approach
int knapsackRecursive(int W, const vector<int>& wt, const vector<int>& val, int n) {
    if (n == 0 || W == 0)
        return 0;

    if (wt[n - 1] > W)
        return knapsackRecursive(W, wt, val, n - 1);
    
    return max(val[n - 1] + knapsackRecursive(W - wt[n - 1], wt, val, n - 1), knapsackRecursive(W, wt, val, n - 1));
}

// Memoized recursive approach
int knapsackMemoized(int W, const vector<int>& wt, const vector<int>& val, int n, vector<vector<int>>& dp) {
    if (n == 0 || W == 0)
        return 0;

    if (dp[n][W] != -1)
        return dp[n][W];

    if (wt[n - 1] > W)
        return dp[n][W] = knapsackMemoized(W, wt, val, n - 1, dp);

    return dp[n][W] = max(val[n - 1] + knapsackMemoized(W - wt[n - 1], wt, val, n - 1, dp), knapsackMemoized(W, wt, val, n - 1, dp));
}

// Iterative approach
int knapsackIterative(int W, const vector<int>& wt, const vector<int>& val, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= W; ++w) {
            if (wt[i - 1] <= w) {
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main() {
    vector<int> val = {3,4,5,6};
    vector<int> wt = {2,3,4,5};
    int W = 5;
    int n = val.size();

    // Recursive
    cout << endl << "Recursive: " << knapsackRecursive(W, wt, val, n) << endl;

    // Memoized recursive
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1));
    cout << "Memoized Recursive: " << knapsackMemoized(W, wt, val, n, dp) << endl;

    // Iterative
    cout << "Iterative: " << knapsackIterative(W, wt, val, n) << endl;

    return 0;
}
