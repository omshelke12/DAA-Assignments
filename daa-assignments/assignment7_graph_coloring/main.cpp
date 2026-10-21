
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

string colorNames[] = {
    "Red", "Green", "Yellow", "Blue",
    "Magenta", "Cyan", "Orange", "Purple"
};

int main() {
    int n, m;

    cout << "Enter number of courses: ";
    cin >> n;

    cout << "Enter number of students: ";
    cin >> m;

    if (n <= 0 || m < 0) {
        cout << "Invalid number of courses or students!" << endl;
        return 0;
    }

    vector<vector<bool>> conflict(
        n, vector<bool>(n, false)
    );

    cout << "\nEnter courses for each student.\n";
    cout << "Enter the number of courses followed by course IDs (1 to "
         << n << ").\n";

    // Input courses and build the conflict graph
    for (int i = 0; i < m; i++) {
        int k;

        cout << "\nStudent " << i + 1
             << " - number of courses: ";
        cin >> k;

        if (k < 0 || k > n) {
            cout << "Invalid number of courses!" << endl;
            return 0;
        }

        cout << "Enter course IDs: ";

        vector<bool> enrolled(n, false);

        for (int j = 0; j < k; j++) {
            int course;
            cin >> course;

            if (course < 1 || course > n) {
                cout << "Invalid course ID!" << endl;
                return 0;
            }

            enrolled[course - 1] = true;
        }

        // Courses taken by the same student conflict
        for (int u = 0; u < n; u++) {
            for (int v = u + 1; v < n; v++) {
                if (enrolled[u] && enrolled[v]) {
                    conflict[u][v] = true;
                    conflict[v][u] = true;
                }
            }
        }
    }

    // Calculate degree of each course
    vector<pair<int, int>> courses;

    for (int i = 0; i < n; i++) {
        int degree = 0;

        for (int j = 0; j < n; j++) {
            if (conflict[i][j]) {
                degree++;
            }
        }

        // Store {degree, course index}
        courses.push_back({degree, i});
    }

    // Welsh-Powell: sort by decreasing degree
    // Break ties by course index
    sort(courses.begin(), courses.end(),
         [](const pair<int, int>& a,
            const pair<int, int>& b) {
             if (a.first != b.first) {
                 return a.first > b.first;
             }
             return a.second < b.second;
         });

    // Greedy graph coloring
    vector<int> color(n, -1);
    int totalSlots = 0;

    for (const auto& course : courses) {
        int u = course.second;

        vector<bool> used(n, false);

        // Find colors used by neighboring courses
        for (int v = 0; v < n; v++) {
            if (conflict[u][v] && color[v] != -1) {
                used[color[v]] = true;
            }
        }

        // Assign the smallest available color
        int c = 0;

        while (c < n && used[c]) {
            c++;
        }

        color[u] = c;
        totalSlots = max(totalSlots, c + 1);
    }

    // Display examination timetable
    cout << "\n--- Examination Timetable ---\n";

    cout.width(10);
    cout << left << "Course";
    cout.width(12);
    cout << left << "Time Slot";
    cout.width(10);
    cout << left << "Color" << endl;

    for (int i = 0; i < n; i++) {
        cout.width(10);
        cout << left << ("C" + to_string(i + 1));

        cout.width(12);
        cout << left << ("Slot " + to_string(color[i] + 1));

        cout.width(10);
        cout << left
             << colorNames[color[i] % 8] << endl;
    }

    cout << "\nTotal time slots required: "
         << totalSlots << endl;

    // Display graph coloring
    cout << "\n--- Graph Coloring ---\n";

    for (int i = 0; i < n; i++) {
        cout << "[ C" << i + 1 << " ] --> Slot "
             << color[i] + 1
             << " | Color: "
             << colorNames[color[i] % 8] << endl;
    }

    // Display conflict graph edges
    cout << "\n--- Conflict Graph Edges ---\n";

    bool hasEdges = false;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (conflict[i][j]) {
                cout << "C" << i + 1
                     << " -- C" << j + 1 << endl;

                hasEdges = true;
            }
        }
    }

    if (!hasEdges) {
        cout << "No conflicts between courses." << endl;
    }

    return 0;
}
