#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
    // Josephus problem - varianta cu n persoane si k persoane skipped
    int n, k;
    cin >> n >> k;
    CircularList<int> list;
    for(int i = 1; i <= n; i++)
        list.add_back(i);
    list.set_current(n-1);
    while(list.get_size() > 1)
    {
        list.move_current(k-1);
        list.delete_next();
    }
    cout << "The last person alive is " << list.get_current();
    return 0;
}
