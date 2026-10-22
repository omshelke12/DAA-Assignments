#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
using namespace std;

struct Movie
{
    int id;
    string name;
    float rating;
    int year;
    int watchTime;
};

// Returns true if movie x must come BEFORE movie y (descending order).
// Ties on the main key are broken by rating, then year, then watch time, then id,
// so the output order is always the same.
bool comesBefore(const Movie& x, const Movie& y, int choice)
{
    if(choice == 1 && x.rating != y.rating)       return x.rating > y.rating;
    if(choice == 2 && x.year != y.year)           return x.year > y.year;
    if(choice == 3 && x.watchTime != y.watchTime) return x.watchTime > y.watchTime;
    if(x.rating != y.rating)       return x.rating > y.rating;
    if(x.year != y.year)           return x.year > y.year;
    if(x.watchTime != y.watchTime) return x.watchTime > y.watchTime;
    return x.id < y.id;
}

void quickSort(vector<Movie>& a, int low, int high, int choice)
{
    int i = low;
    int j = high;
    Movie pivot = a[(low + high) / 2];
    while(i <= j)
    {
        while(comesBefore(a[i], pivot, choice))
            i++;
        while(comesBefore(pivot, a[j], choice))
            j--;
        if(i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if(low < j)
        quickSort(a, low, j, choice);
    if(i < high)
        quickSort(a, i, high, choice);
}

int main()
{
    vector<Movie> movies;
    ifstream file("movies.csv");
    if(!file)
    {
        cout << "File not found!" << endl;
        return 0;
    }
    string line;
    getline(file, line);
    while(getline(file, line))
    {
        if(line.empty())
            continue;
        int p1 = line.find(',');
        int p2 = line.find(',', p1 + 1);
        int p3 = line.find(',', p2 + 1);
        int p4 = line.find(',', p3 + 1);
        Movie m;
        m.id = stoi(line.substr(0, p1));
        m.name = line.substr(p1 + 1, p2 - p1 - 1);
        m.rating = stof(line.substr(p2 + 1, p3 - p2 - 1));
        m.year = stoi(line.substr(p3 + 1, p4 - p3 - 1));
        m.watchTime = stoi(line.substr(p4 + 1));
        movies.push_back(m);
    }
    file.close();
    int n = movies.size();

    cout << "MOVIE RECOMMENDATION SYSTEM" << endl;
    cout << "---------------------------" << endl;
    cout << "Movies loaded from movies.csv: " << n << endl << endl;
    cout << "1. Sort by IMDb Rating" << endl;
    cout << "2. Sort by Release Year" << endl;
    cout << "3. Sort by Watch Time" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    if(choice < 1 || choice > 3)
    {
        cout << "Invalid choice! Please enter 1, 2 or 3." << endl;
        return 0;
    }
    string keyName[] = {"", "IMDb Rating", "Release Year", "Watch Time"};

    auto start = chrono::high_resolution_clock::now();
    quickSort(movies, 0, n - 1, choice);
    auto stop = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(stop - start).count();

    bool sorted = true;
    for(int i = 1; i < n; i++)
        if(comesBefore(movies[i], movies[i - 1], choice))
            sorted = false;

    const int SHOW = 20;
    cout << "\nTop " << SHOW << " movies sorted by " << keyName[choice] << " (high to low):" << endl;
    cout << string(70, '=') << endl;
    cout << left << setw(6) << "Rank" << setw(6) << "ID" << setw(28) << "Movie"
         << right << setw(8) << "Rating" << setw(8) << "Year" << setw(14) << "WatchTime" << endl;
    cout << string(70, '-') << endl;
    for(int i = 0; i < n && i < SHOW; i++)
    {
        cout << left << setw(6) << i + 1 << setw(6) << movies[i].id << setw(28) << movies[i].name
             << right << setw(8) << fixed << setprecision(1) << movies[i].rating
             << setw(8) << movies[i].year << setw(14) << movies[i].watchTime << endl;
    }
    cout << string(70, '=') << endl;
    cout << "Total movies sorted : " << n << endl;
    cout << "Sorted correctly    : " << (sorted ? "Yes" : "No") << endl;
    cout << "Sorting time        : " << fixed << setprecision(3) << ms << " ms" << endl;
    return 0;
}
