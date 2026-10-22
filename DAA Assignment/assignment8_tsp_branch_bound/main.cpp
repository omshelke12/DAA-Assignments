#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Node {
    int level;
    int cost;
    int bound;
    int city;
    vector<int> path;
};

struct Compare {
    bool operator()(Node a, Node b) {
        return a.bound > b.bound;
    }
};

int calculateBound(vector<vector<int>> &cost, Node node) {
    int n = cost.size();
    int bound = node.cost;
    vector<bool> visited(n, false);
    for (int city : node.path) {
        visited[city] = true;
    }
    int current = node.city;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int minCost = INT_MAX;
            for (int j = 0; j < n; j++) {
                if (i != j && cost[i][j] < minCost) {
                    minCost = cost[i][j];
                }
            }
            bound += minCost;
        }
    }
    if (node.level < n - 1) {
        int minCost = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && cost[current][j] < minCost) {
                minCost = cost[current][j];
            }
        }
        bound += minCost;
    }
    return bound;
}

void tspBranchBound(vector<vector<int>> &cost) {
    int n = cost.size();
    priority_queue<Node, vector<Node>, Compare> pq;
    Node start;
    start.level = 0;
    start.cost = 0;
    start.city = 0;
    start.path.push_back(0);
    start.bound = calculateBound(cost, start);
    pq.push(start);
    int minCost = INT_MAX;
    vector<int> bestPath;
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        if (current.bound >= minCost) {
            continue;
        }
        if (current.level == n - 1) {
            int totalCost = current.cost + cost[current.city][0];
            if (totalCost < minCost) {
                minCost = totalCost;
                bestPath = current.path;
                bestPath.push_back(0);
            }
            continue;
        }
        for (int next = 0; next < n; next++) {
            bool visited = false;
            for (int city : current.path) {
                if (city == next) {
                    visited = true;
                    break;
                }
            }
            if (!visited) {
                Node child;
                child.level = current.level + 1;
                child.city = next;
                child.cost = current.cost + cost[current.city][next];
                child.path = current.path;
                child.path.push_back(next);
                child.bound = calculateBound(cost, child);
                if (child.bound < minCost) {
                    pq.push(child);
                }
            }
        }
    }
    cout << "Optimal Route: ";
    for (int city : bestPath) {
        cout << char('A' + city) << " ";
    }
    cout << endl;
    cout << "Minimum Cost: " << minCost << endl;
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;
    vector<vector<int>> cost(n, vector<int>(n));
    cout << "Enter cost matrix (" << n << " x " << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];
    tspBranchBound(cost);
    return 0;
}
