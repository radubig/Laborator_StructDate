#pragma once

#include "Node.h"
#include <ostream>
#include <cstring>
#include <random>

template <typename KeyType, typename ValueType>
class SkipList
{
    const int maxLevel;
    int level;
    SkipNode<KeyType, ValueType> *head;

public:
    typedef SkipNode<KeyType, ValueType> SkipNodeType;

    explicit SkipList(int _maxLevel)
        : maxLevel(_maxLevel), level(0)
    {
        head = new SkipNodeType (maxLevel, KeyType(), ValueType());
    }

    ~SkipList()
    {
        delete head;
    }

    int getRandomLevel() const
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, 1);

        int lvl = 0;
        while (dist(gen) && lvl < maxLevel) {
            lvl++;
        }

        return lvl;
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        SkipNodeType *current = head;
        SkipNodeType *update[maxLevel + 1];
        memset(update, 0, sizeof(SkipNodeType*) * (maxLevel + 1));

        for(int i = level; i >= 0; i--)
        {
            while (current->forward[i] != nullptr && current->forward[i]->key < key)
            {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if(current != nullptr && current->key == key)
        {
            current->value = value;
            return;
        }

        int newLevel = getRandomLevel();
        if(newLevel > level)
        {
            for (int i = level + 1; i <= newLevel; i++)
                update[i] = head;

            level = newLevel;
        }

        auto* newNode = new SkipNodeType (newLevel, key, value);
        for (int i = 0; i <= newLevel; i++)
        {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    ValueType search(KeyType key)
    {
        SkipNode<KeyType, ValueType>* current = head;

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key <= key) {
                if (current->forward[i]->key == key) {
                    return current->forward[i]->value;
                }
                current = current->forward[i];
            }
        }

        return ValueType();
    }

    void remove(const KeyType& key)
    {
        SkipNodeType *current = head;
        SkipNodeType *update[maxLevel + 1];
        memset(update, 0, sizeof(SkipNodeType*) * (maxLevel + 1));

        for (int i = level; i >= 0; i--)
        {
            while (current->forward[i] != nullptr && current->forward[i]->key < key)
                current = current->forward[i];
            update[i] = current;
        }

        current = current->forward[0];
        if (current != nullptr && current->key == key)
        {
            for (int i = 0; i <= level; i++)
            {
                if (update[i]->forward[i] != current)
                    break;
                update[i]->forward[i] = current->forward[i];
            }

            delete current;

            while (level > 0 && head->forward[level] == nullptr)
                level--;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const SkipList<KeyType, ValueType>& skipList)
    {
        SkipNodeType* current = skipList.head->forward[0];
        while (current != nullptr)
        {
            os << "{" << current->key << " : " << current->value << "}\n";
            current = current->forward[0];
        }
        return os;
    }
};