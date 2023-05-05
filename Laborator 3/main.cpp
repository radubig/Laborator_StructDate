#include <iostream>
#include "SortedLinkedList.h"

using namespace std;

int main()
{
    SortedLinkedList<string> list;
    int n;
    cin >> n; cin.get();
    for(int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        list.insert(s);
    }
    cout << list << "\n";
    return 0;
}
