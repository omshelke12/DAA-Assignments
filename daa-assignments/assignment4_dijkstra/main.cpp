#include <iostream>
#include <fstream>
using namespace std;
#define INF 9999

struct Road
{
    int source;
    int destination;
    int time;
};

int main()
{
    Road roads[50];
    int roadCount = 0;
    ifstream file("traffic.csv");
    if(!file)
    {
        cout << "File not found!" << endl;
        return 0;
    }
    string line;
    getline(file, line);
    while(file >> roads[roadCount].source)
    {
        file.ignore();
        file >> roads[roadCount].destination;
        file.ignore();
        file >> roads[roadCount].time;
        roadCount++;
    }
    file.close();

    int n = 6;
    int graph[10][10];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            graph[i][j] = INF;
        }
    }
    for(int i = 0; i < roadCount; i++)
    {
        graph[roads[i].source][roads[i].destination] = roads[i].time;
        graph[roads[i].destination][roads[i].source] = roads[i].time;
    }

    int source, destination;
    cout << "Enter ambulance source: ";
    cin >> source;
    cout << "Enter hospital destination: ";
    cin >> destination;

    int distance[10];
    int visited[10];
    int previous[10];
    for(int i = 0; i < n; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
        previous[i] = -1;
    }
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
            if(graph[current][i] != INF)
            {
                if(distance[current] + graph[current][i] < distance[i])
                {
                    distance[i] = distance[current] + graph[current][i];
                    previous[i] = current;
                }
            }
        }
    }

    cout << "\nShortest travel time = " << distance[destination] << " minutes";
    int path[10];
    int count = 0;
    int current = destination;
    while(current != -1)
    {
        path[count] = current;
        count++;
        current = previous[current];
    }
    cout << "\nShortest path = ";
    for(int i = count - 1; i >= 0; i--)
    {
        cout << path[i];
        if(i != 0)
            cout << " -> ";
    }
    cout << endl;
    return 0;
}
