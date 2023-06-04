#pragma once

template<typename T>
concept comparabil = std::three_way_comparable<T>;

template<typename T1, typename T2>
struct Node
{
    T1 key;
    T2 data;
    Node* next;
};

template <typename KeyType, typename ValueType>
struct SkipNode
{
    KeyType key;
    ValueType value;
    SkipNode<KeyType, ValueType>** forward;

    SkipNode(int _level, const KeyType& _key, const ValueType& _value)
            :key(_key), value(_value)
    {
        forward = new SkipNode<KeyType, ValueType>*[_level + 1] {nullptr};
//        memset(forward, 0, sizeof(SkipNode<KeyType, ValueType>*) * (_level + 1));
    }

    ~SkipNode() {
        delete[] forward;
    }
};
