#ifndef JOSEPHUS_PROBLEM_LINKEDLIST_H
#define JOSEPHUS_PROBLEM_LINKEDLIST_H

#include <ostream>
#include "Node.h"

template <typename T>
class CircularList
{
public:
    CircularList() : first(nullptr), last(nullptr), current(nullptr), size(0){}
    ~CircularList()
    {
        Node<T> *aux = first->next;
        while(aux != first)
        {
            Node<T> *k = aux;
            aux = aux->next;
            delete k;
        }
        delete first;
    }
    // No copy allowed for now
    CircularList(const CircularList&) = delete;
    CircularList& operator=(const CircularList&) = delete;

    void add_back(const T& value)
    {
        if(first == nullptr)
        {
            first = new Node<T>{value, nullptr};
            first->next = first;
            last = first;
        }
        else
        {
            last->next = new Node<T>{value, first};
            last = last->next;
        }
        size++;
    }

    void set_current(unsigned int index)
    {
        current = first;
        if(index == 0)
            current = last;
        else while(--index > 0)
            current = current->next;
    }

    void move_current(unsigned int positions)
    {
        while(positions-- > 0) current = current->next;
    }

    void delete_next()
    {
        Node<T> *aux = current->next;
        current->next = current->next->next;
        if(aux == first) first = current->next;
        else if(aux == last) last = current;
        delete aux;
        size--;
        if(size == 0) first = last = current = nullptr;
    }

    T& get_next() {return current->next->value;}

    T& get_current() {return current->value;}

    size_t get_size() const {return size;}

    friend std::ostream& operator<< (std::ostream& os, const CircularList<T>& list)
    {
        Node<T> *i = list.first;
        os << i->value << " ";
        i = i->next;
        while(i != list.first)
        {
            os << i->value << " ";
            i = i->next;
        }
        return os;
    }

private:
    Node<T> *first, *last, *current;
    size_t size;
};

#endif //JOSEPHUS_PROBLEM_LINKEDLIST_H
