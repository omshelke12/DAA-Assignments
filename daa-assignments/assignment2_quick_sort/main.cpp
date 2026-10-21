#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Movie
{
    int id;
    string name;
    float rating;
    int year;
    int watchTime;
};

void quickSort(Movie a[], int low, int high, int choice)
{
    int i = low;
    int j = high;
    Movie pivot = a[(low + high) / 2];
    Movie temp;
    while(i <= j)
    {
        if(choice == 1)
        {
            while(a[i].rating > pivot.rating)
                i++;
            while(a[j].rating < pivot.rating)
                j--;
        }
        else if(choice == 2)
        {
            while(a[i].year > pivot.year)
                i++;
            while(a[j].year < pivot.year)
                j--;
        }
        else if(choice == 3)
        {
            while(a[i].watchTime > pivot.watchTime)
                i++;
            while(a[j].watchTime < pivot.watchTime)
                j--;
        }
        if(i <= j)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
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
    Movie movies[100];
    int n = 0;
    int choice;
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
        int p1 = line.find(',');
        int p2 = line.find(',', p1 + 1);
        int p3 = line.find(',', p2 + 1);
        int p4 = line.find(',', p3 + 1);
        movies[n].id = stoi(line.substr(0, p1));
        movies[n].name = line.substr(p1 + 1, p2 - p1 - 1);
        movies[n].rating = stof(line.substr(p2 + 1, p3 - p2 - 1));
        movies[n].year = stoi(line.substr(p3 + 1, p4 - p3 - 1));
        movies[n].watchTime = stoi(line.substr(p4 + 1));
        n++;
    }
    file.close();
    cout << "MOVIE RECOMMENDATION SYSTEM" << endl;
    cout << "----------------------------" << endl;
    cout << "1. Sort by IMDb Rating" << endl;
    cout << "2. Sort by Release Year" << endl;
    cout << "3. Sort by Watch Time" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    quickSort(movies, 0, n - 1, choice);
    cout << endl;
    cout << "Sorted Movie Dataset:" << endl;
    cout << "ID\tMovie\t\tRating\tYear\tWatchTime" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << movies[i].id << "\t"
             << movies[i].name << "\t\t"
             << movies[i].rating << "\t"
             << movies[i].year << "\t"
             << movies[i].watchTime << endl;
    }
    return 0;
}
