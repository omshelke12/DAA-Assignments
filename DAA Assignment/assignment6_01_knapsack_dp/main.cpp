#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(int n, int capacity, vector<int>& weight, vector<int>& value, vector<int>& selected) {
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weight[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], value[i - 1] + dp[i - 1][w - weight[i - 1]]);
            } else {
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
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;
    vector<int> weight(n), value(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter weight of item " << i + 1 << ": ";
        cin >> weight[i];
        cout << "Enter value of item " << i + 1 << ": ";
        cin >> value[i];
    }
    cout << "Enter truck capacity (kg): ";
    cin >> capacity;

    vector<int> selected;
    int maximumUtility = knapsack(n, capacity, weight, value, selected);

    cout << "\nDisaster Relief Resource Allocation" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Truck Capacity: " << capacity << " kg" << endl;
    cout << "Maximum Utility: " << maximumUtility << endl;
    cout << "Selected Items: ";
    int totalWeight = 0;
    for (int i : selected) {
        cout << "Item " << i + 1 << " ";
        totalWeight += weight[i];
    }
    cout << endl;
    cout << "Total Weight: " << totalWeight << " kg" << endl;
    return 0;
}
