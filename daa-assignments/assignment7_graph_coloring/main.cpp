#include <iostream>
#include <vector>
using namespace std;

void greedyColoring(vector<vector<int>>& graph, vector<int>& color) {
    int n = graph.size();
    for (int u = 0; u < n; u++) {
        vector<bool> used(n, false);
        for (int v : graph[u]) {
            if (color[v] != -1) {
                used[color[v]] = true;
            }
        }
        int c = 0;
        while (c < n && used[c]) {
            c++;
        }
        color[u] = c;
    }
}

int findSlots(vector<int>& color) {
    int maxColor = 0;
    for (int c : color) {
        if (c > maxColor) {
            maxColor = c;
        }
    }
    return maxColor + 1;
}

void displayTimetable(vector<int>& color) {
    cout << "\nExam Timetable:\n";
    for (int i = 0; i < color.size(); i++) {
        cout << "Course " << i + 1 << " -> Slot " << color[i] + 1 << endl;
    }
}

void roomAllocation(vector<int>& color, int rooms, vector<int>& roomCapacity) {
    int slots = findSlots(color);
    cout << "\nRoom Allocation:\n";
    for (int slot = 0; slot < slots; slot++) {
        cout << "\nSlot " << slot + 1 << ":\n";
        int roomIndex = 0;
        for (int i = 0; i < color.size(); i++) {
            if (color[i] == slot) {
                if (roomIndex < rooms) {
                    cout << "Course " << i + 1 << " -> Room " << roomIndex + 1
                         << " (Capacity: " << roomCapacity[roomIndex] << ")" << endl;
                    roomIndex++;
                }
                else {
                    cout << "Course " << i + 1 << " -> No room available" << endl;
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of courses: ";
    cin >> n;
    vector<vector<int>> graph(n);
    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x == 1) {
                graph[i].push_back(j);
            }
        }
    }
    vector<int> color(n, -1);
    greedyColoring(graph, color);
    int slots = findSlots(color);
    displayTimetable(color);
    cout << "\nMinimum Slots Used: " << slots << endl;
    int rooms;
    cout << "\nEnter number of rooms: ";
    cin >> rooms;
    vector<int> roomCapacity(rooms);
    cout << "Enter capacity of each room:\n";
    for (int i = 0; i < rooms; i++) {
        cin >> roomCapacity[i];
    }
    roomAllocation(color, rooms, roomCapacity);
    return 0;
}
