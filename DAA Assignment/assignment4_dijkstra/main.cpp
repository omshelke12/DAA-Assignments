#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#define INF 1000000000

struct Road
{
    int source;
    int destination;
    int time;
};

int main()
{
    vector<Road> roads;
    ifstream file("traffic.csv");
    if(!file)
    {
        cout << "File not found!" << endl;
        return 0;
    }
    string line;
    getline(file, line);
    int n = 0;
    Road r;
    while(file >> r.source)
    {
        file.ignore();
        file >> r.destination;
        file.ignore();
        file >> r.time;
        roads.push_back(r);
        if(r.source + 1 > n) n = r.source + 1;
        if(r.destination + 1 > n) n = r.destination + 1;
    }
    file.close();
    int roadCount = roads.size();
    cout << "Roads read from traffic.csv: " << roadCount << ", Junctions: " << n << endl;

    vector<vector<int>> graph(n, vector<int>(n, INF));
    for(int i = 0; i < roadCount; i++)
    {
        int s = roads[i].source, d = roads[i].destination, t = roads[i].time;
        if(t < graph[s][d])
        {
            graph[s][d] = t;
            graph[d][s] = t;
        }
    }

    int source, destination;
    cout << "Enter ambulance source: ";
    cin >> source;
    cout << "Enter hospital destination: ";
    cin >> destination;
    if(source < 0 || source >= n || destination < 0 || destination >= n)
    {
        cout << "Invalid junction!" << endl;
        return 0;
    }

    vector<int> distance(n, INF), visited(n, 0), previous(n, -1);
    distance[source] = 0;

    for(int count = 0; count < n - 1; count++)
    {
        int minDistance = INF;
        int current = -1;
        for(int i = 0; i < n; i++)
        {
            if(visited[i] == 0 && distance[i] < minDistance)
            {
                minDistance = distance[i];
                current = i;
            }
        }
        if(current == -1)
            break;
        visited[current] = 1;
        for(int i = 0; i < n; i++)
        {
            if(graph[current][i] != INF && distance[current] + graph[current][i] < distance[i])
            {
                distance[i] = distance[current] + graph[current][i];
                previous[i] = current;
            }
        }
    }

    if(distance[destination] == INF)
    {
        cout << "\nNo route available!" << endl;
        return 0;
    }
    cout << "\nShortest travel time = " << distance[destination] << " minutes";
    vector<int> path;
    for(int current = destination; current != -1; current = previous[current])
        path.push_back(current);
    cout << "\nShortest path = ";
    for(int i = path.size() - 1; i >= 0; i--)
    {
        cout << path[i];
        if(i != 0)
            cout << " -> ";
    }
    cout << endl;
    return 0;
}
