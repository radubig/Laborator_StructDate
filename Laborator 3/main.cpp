#include <iostream>
#include <fstream>
#include <chrono>
#include "SortedLinkedList.h"
#include "SkipList.h"

using namespace std;

inline auto now()
{
    return std::chrono::high_resolution_clock::now();
}

int main()
{
    SortedLinkedList<string, int> linkedList;
    SkipList<string, int> skipList(5);
    ifstream in;
    int n;

    // Create linkedList
    auto start = now();
    in.open("input.txt");
    in >> n; in.get();
    for(int i = 0; i < n; i++)
    {
        string s;
        int x;
        in >> s >> x;
        linkedList.insert(s, x);
    }
    in.close();
    auto end = now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "linkedList construction time: " << duration << " ms\n";

    // Create skipList
    start = now();
    in.open("input.txt");
    in >> n; in.get();
    for(int i = 0; i < n; i++)
    {
        string s;
        int x;
        in >> s >> x;
        skipList.insert(s, x);
    }
    in.close();
    end = now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "skipList construction time: " << duration << " ms\n";



    // Remove from linkedList
    start = now();
    in.open("input.txt");
    in >> n; in.get();
    for(int i = 0; i < n; i++)
    {
        string s;
        int x;
        in >> s >> x;
        linkedList.remove(s);
    }
    in.close();
    end = now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "linkedList total removal time: " << duration << " ms\n";

    // Remove from skipList
    start = now();
    in.open("input.txt");
    in >> n; in.get();
    for(int i = 0; i < n; i++)
    {
        string s;
        int x;
        in >> s >> x;
        skipList.remove(s);
    }
    in.close();
    end = now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "skipList total removal time: " << duration << " ms\n";
    return 0;
}
