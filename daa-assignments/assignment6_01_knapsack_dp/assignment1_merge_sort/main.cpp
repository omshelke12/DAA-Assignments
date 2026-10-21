#include <iostream>
using namespace std;

struct Order
{
    int orderId;
    int timestamp;
};

void merge(Order a[], int low, int mid, int high)
{
    Order temp[100];
    int i = low;
    int j = mid + 1;
    int k = low;
    while(i <= mid && j <= high)
    {
        if(a[i].timestamp <= a[j].timestamp)
        {
            temp[k] = a[i];
            i++;
        }
        else
        {
            temp[k] = a[j];
            j++;
        }
        k++;
    }
    while(i <= mid)
    {
        temp[k] = a[i];
        i++;
        k++;
    }
    while(j <= high)
    {
        temp[k] = a[j];
        j++;
        k++;
    }
    for(i = low; i <= high; i++)
    {
        a[i] = temp[i];
    }
}

void mergeSort(Order a[], int low, int high)
{
    if(low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

int main()
{
    Order a[100];
    int n;
    cout << "Enter number of orders: ";
    cin >> n;
    cout << "Enter Order ID and Timestamp:" << endl;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i].orderId >> a[i].timestamp;
    }
    mergeSort(a, 0, n - 1);
    cout << "\nOrders sorted according to timestamp:" << endl;
    cout << "Order ID\tTimestamp" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << a[i].orderId << "\t\t" << a[i].timestamp << endl;
    }
    return 0;
}
