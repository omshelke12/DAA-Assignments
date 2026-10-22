#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void createGraph(vector<vector<int>>& cost) {
    cost[0][1] = 2;
    cost[0][2] = 3;
    cost[1][3] = 4;
    cost[1][4] = 6;
    cost[2][3] = 3;
    cost[2][4] = 2;
    cost[3][5] = 5;
    cost[3][6] = 2;
    cost[4][5] = 4;
    cost[4][6] = 6;
    cost[5][7] = 3;
    cost[6][7] = 2;
}

int findMinimumCost(vector<vector<int>>& cost, vector<int>& path) {
    int n = cost.size();
    vector<int> dp(n, INT_MAX);
    dp[n - 1] = 0;
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (cost[i][j] != 0 && dp[j] != INT_MAX) {
                int newCost = cost[i][j] + dp[j];
                if (newCost < dp[i]) {
                    dp[i] = newCost;
                    path[i] = j;
                }
            }
        }
    }
    return dp[0];
}

void displayRoute(vector<int>& path) {
    int current = 0;
    cout << "Optimal Route: ";
    while (current != -1) {
        cout << "Node " << current;
        if (path[current] != -1) {
            cout << " -> ";
        }
        current = path[current];
    }
    cout << endl;
}

int main() {
    int n = 8;
    vector<vector<int>> cost(n, vector<int>(n, 0));
    vector<int> path(n, -1);
    createGraph(cost);
    int minimumCost = findMinimumCost(cost, path);
    cout << "SwiftCargo Logistics Route Optimization" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Minimum Delivery Cost: " << minimumCost << endl;
    displayRoute(path);
    return 0;
}
