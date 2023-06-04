#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
    // Josephus problem - varianta cu n persoane si k persoane skipped
    unsigned int n, k, start;
    cout << "Enter total number of people: ";
    cin >> n;
    cout << "Enter number of people to be skipped: ";
    cin >> k;
    cout << "Enter starting person #: ";
    cin >> start;
    cout << "\n";

    CircularList<int> list;
    for(int i = 1; i <= n; i++)
        list.add_back(i);
    list.set_current(start);
    while(list.get_size() > 1)
    {
        cout << "People remaining: " << list << "\n";
        list.move_current(k-1);
        cout << "Killed person " << list.get_next() << "\n";
        list.delete_next();
    }
    cout << "The last person alive is " << list.get_current();
    return 0;
}
