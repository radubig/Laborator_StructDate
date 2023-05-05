#ifndef LABORATOR_3_SORTEDLINKEDLIST_H
#define LABORATOR_3_SORTEDLINKEDLIST_H

#include "Node.h"
#include <ostream>

template<typename T>
concept comparabil = std::three_way_comparable<T>;

template<comparabil T>
class SortedLinkedList
{
public:
    SortedLinkedList() : first(nullptr), last(nullptr) {}
    SortedLinkedList(const SortedLinkedList&) = delete;
    SortedLinkedList& operator= (const SortedLinkedList&) = delete;
    ~SortedLinkedList()
    {
        while(first != nullptr)
        {
            auto *aux = first;
            first = first->next;
            delete aux;
        }
    }

    void insert(const T& val)
    {
        if(first == nullptr)
        {
            first = new Node<T>{val, nullptr, nullptr};
            last = first;
        }
        else
        {
            auto *nod = first;
            while(nod != nullptr && nod->data < val)
                nod = nod->next;
            if(nod == nullptr)
            {
                last->next = new Node<T>{val, nullptr, last};
                last = last->next;
            }
            else
            {
                nod->prev->next = new Node<T>{val, nod, nod->prev};
                nod->prev = nod->prev->next;
            }
        }
    }

    friend std::ostream& operator<<  (std::ostream& os, const SortedLinkedList<T>& list)
    {
        auto nod = list.first;
        while(nod)
        {
            os << nod->data << " ";
            nod = nod->next;
        }
        return os;
    }

    // TODO: write the rest of the interface after getting it.

private:
    Node<T> *first, *last;
};

#endif //LABORATOR_3_SORTEDLINKEDLIST_H
