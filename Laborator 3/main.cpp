#include <iostream>
#include <fstream>
#include "SortedLinkedList.h"
#include "SkipList.h"

using namespace std;

int main()
{
    SortedLinkedList<string, int> linkedList;
    SkipList<string, int> skipList(5);

    // Read linkedList
    ifstream in("input.txt");
    int n;
    in >> n; in.get();
    for(int i = 0; i < 40; i++)
    {
        string s;
        int x;
        in >> s >> x;
        cout << s << " " << x << endl;
        linkedList.insert(s, x);
        skipList.insert(s, x);
    }
    in.close();

    cout << linkedList << "\n";
    cout << "\n";
    cout << skipList;
    return 0;
}
