# DAA Assignments (PCCOE) — Omraje Shelke, PRN 124B1F002

Each folder contains the C++ source (`main.cpp`), the input used (`input.txt` / CSV), and the real program output (`output.txt`).

| # | Folder | Topic |
|---|--------|-------|
| 1 | assignment1_merge_sort | Merge Sort – customer orders by timestamp |
| 2 | assignment2_quick_sort | Quick Sort – movies by rating / year / watch time |
| 3 | assignment3_fractional_knapsack | Fractional Knapsack – relief supplies on a boat |
| 4 | assignment4_dijkstra | Dijkstra – ambulance shortest route |
| 5 | assignment5_multistage_graph | Multistage graph DP – logistics routing |
| 6 | assignment6_01_knapsack_dp | 0/1 Knapsack DP – relief truck |
| 7 | assignment7_graph_coloring | Graph coloring – exam timetable |
| 8 | assignment8_tsp_branch_bound | TSP – LC Branch and Bound |

## Run
```
cd assignmentN_xxx
g++ -std=c++17 main.cpp -o prog
./prog < input.txt        # assignments 1, 3, 4, 7
./prog                    # assignments 2 (enter 1/2/3), 5, 6, 8
```
Assignments 2 and 4 read `movies.csv` / `traffic.csv` from the current folder.
