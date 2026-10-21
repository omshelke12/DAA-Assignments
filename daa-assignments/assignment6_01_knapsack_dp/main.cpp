#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(int n, int capacity, vector<int>& weight, vector<int>& value, vector<int>& selected) {
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    dp[i - 1][w],
                    value[i - 1] + dp[i - 1][w - weight[i - 1]]
                );
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    int w = capacity;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(i - 1);
            w = w - weight[i - 1];
        }
    }
    reverse(selected.begin(), selected.end());
    return dp[n][capacity];
}

int main() {
    int n = 5;
    int capacity = 50;
    vector<int> weight = {10, 20, 30, 15, 25};
    vector<int> value = {100, 80, 120, 60, 90};
    vector<int> selected;
    int maximumUtility = knapsack(n, capacity, weight, value, selected);
    cout << "Disaster Relief Resource Allocation" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Truck Capacity: " << capacity << " kg" << endl;
    cout << "Maximum Utility: " << maximumUtility << endl;
    cout << "Selected Items: ";
    for (int i : selected) {
        cout << "Item " << i + 1 << " ";
    }
    cout << endl;
    cout << "Total Weight: ";
    int totalWeight = 0;
    for (int i : selected) {
        totalWeight += weight[i];
    }
    cout << totalWeight << " kg" << endl;
    return 0;
}
