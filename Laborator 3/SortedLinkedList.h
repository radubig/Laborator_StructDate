#pragma once

#include "Node.h"
#include <ostream>

template<comparabil KeyType, typename ValueType>
class SortedLinkedList
{
public:
    typedef Node<KeyType, ValueType> NodeType;

    SortedLinkedList() : first(nullptr), last(nullptr) {}
    SortedLinkedList(const SortedLinkedList&) = delete;
    SortedLinkedList& operator= (const SortedLinkedList&) = delete;
    ~SortedLinkedList()
    {
        while(first != nullptr)
        {
            NodeType *aux = first;
            first = first->next;
            delete aux;
        }
    }

    void insert(const KeyType& key, const ValueType& val)
    {
        if(first == nullptr)
        {
            first = new NodeType {key, val, nullptr};
            last = first;
        }
        else if(key < first->key)
        {
            auto *node = new NodeType {key, val, first};
            first = node;
        }
        else
        {
            NodeType *node = first;
            while(node->next != nullptr && node->next->key < key)
                node = node->next;
            if(node != last)
            {
                auto *aux = new NodeType {key, val, nullptr};
                aux->next = node->next;
                node->next = aux;
            }
            else
            {
                last->next = new NodeType {key, val, nullptr};
                last = last->next;
            }
        }
    }

    void remove(const KeyType& key)
    {
        NodeType *node = first;
        if(node == nullptr)
            return;
        if(first->key == key)
        {
            first = first->next;
            delete node;
            return;
        }

        while(node->next != last)
        {
            if(node->next->key == key)
            {
                NodeType *aux = node->next;
                node->next = aux->next;
                delete aux;
                return;
            }
            node = node->next;
        }

        if(last->key == key)
        {
            delete last;
            last = node;
        }
    }

    friend std::ostream& operator<<  (std::ostream& os, const SortedLinkedList<KeyType, ValueType>& list)
    {
        NodeType *nod = list.first;
        while(nod)
        {
            os << "{" << nod->key << " : " << nod->data << "}\n";
            nod = nod->next;
        }
        return os;
    }

private:
    NodeType *first, *last;
};
