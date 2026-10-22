#include <iostream>
using namespace std;

struct Item
{
    string name;
    float weight;
    float utility;
    float ratio;
    int divisible;
};

int main()
{
    int n, i, j;
    float capacity;
    cout << "Enter number of items: ";
    cin >> n;
    Item item[20];
    for(i = 0; i < n; i++)
    {
        cout << "\nEnter details of item " << i + 1 << endl;
        cout << "Name: ";
        cin >> item[i].name;
        cout << "Weight: ";
        cin >> item[i].weight;
        cout << "Utility: ";
        cin >> item[i].utility;
        cout << "Divisible (1-Yes, 0-No): ";
        cin >> item[i].divisible;
        item[i].ratio = item[i].utility / item[i].weight;
    }
    cout << "\nEnter boat capacity: ";
    cin >> capacity;

    // Sort items according to utility/weight ratio
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(item[i].ratio < item[j].ratio)
            {
                Item temp = item[i];
                item[i] = item[j];
                item[j] = temp;
            }
        }
    }

    float totalWeight = 0;
    float totalUtility = 0;
    cout << "\n--- Selected Supplies ---\n";
    for(i = 0; i < n; i++)
    {
        if(capacity == 0)
            break;
        if(item[i].weight <= capacity)
        {
            cout << item[i].name << " : Full item selected" << endl;
            capacity = capacity - item[i].weight;
            totalWeight = totalWeight + item[i].weight;
            totalUtility = totalUtility + item[i].utility;
        }
        else
        {
            if(item[i].divisible == 1)
            {
                float fraction = capacity / item[i].weight;
                float utility = item[i].utility * fraction;
                cout << item[i].name << " : " << fraction * 100 << "% selected" << endl;
                totalWeight = totalWeight + capacity;
                totalUtility = totalUtility + utility;
                capacity = 0;
            }
            else
            {
                cout << item[i].name << " : Cannot select (not divisible)" << endl;
            }
        }
    }
    cout << "\nTotal weight used = " << totalWeight << " kg";
    cout << "\nTotal utility = " << totalUtility << endl;
    return 0;
}
