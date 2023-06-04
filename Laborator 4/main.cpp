#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stack>

using namespace std;

const int lim = 300000;

template<typename T>
struct Node
{
    enum class node_type
    {
        none, number, symbol
    };
    node_type type = node_type::none;
    union
    {
        T number;
        char symbol;
    }value{0};
    Node *left = nullptr, *right = nullptr;
};

template<typename T>
class SyntaxTree
{
public:
    SyntaxTree() : root(nullptr) {}
    ~SyntaxTree();
    void buildFromString(char* sir);
    T evaluate() const;

private:
    Node<T> *root;
    void deleteTree(Node<T>*& node);
    T getValue(Node<T>* node) const;
};

template<typename T> void SyntaxTree<T>::buildFromString(char* sir)
{
    if(root)
        deleteTree(root);
    root = new Node<T>;
    stack<Node<T>*> st;
    st.push(root);

    char* p = strtok(sir, " ");
    while(p)
    {
        if(*p == '(')
        {
            auto nod = st.top();
            st.pop();
            nod->left = new Node<T>;
            nod->right = new Node<T>;
            nod->type = Node<T>::node_type::symbol;
            st.push(nod->right);
            st.push(nod->left);
            st.push(nod);
        }
        else if(*p == ')')
            ;
        else if(*p == '+' || *p == '-' || *p == '*' || *p == '/')
        {
            auto nod = st.top();
            st.pop();
            nod->type = Node<T>::node_type::symbol;
            nod->value.symbol = *p;
        }
        else // e numar
        {
            stringstream ss;
            ss << p;
            T number;
            ss >> number;
            auto nod = st.top();
            st.pop();
            nod->type = Node<T>::node_type::number;
            nod->value.number = number;
        }

        p = strtok(nullptr, " ");
    }
}

template<typename T> SyntaxTree<T>::~SyntaxTree()
{
    if(root)
        deleteTree(root);
}

template<typename T> void SyntaxTree<T>::deleteTree(Node<T>*& node)
{
    if(node->left)
        deleteTree(node->left);
    if(node->right)
        deleteTree(node->right);
    delete node;
    node = nullptr;
}

template<typename T> T SyntaxTree<T>::evaluate() const
{
    return getValue(root);
}

template<typename T> T SyntaxTree<T>::getValue(Node<T>* node) const
{
    if(node->type == Node<T>::node_type::number)
        return node->value.number;

    T left = getValue(node->left);
    T right = getValue(node->right);
    if(node->value.symbol == '+')
        return left + right;
    else if(node->value.symbol == '-')
        return left - right;
    else if(node->value.symbol == '*')
        return left * right;
    else if(node->value.symbol == '/')
        return left / right;
    else // eroare
        return 0;
}

void citire_sir(char* sir)
{
    ifstream in("input.txt");
    in.getline(sir, lim+1);
    in.close();
}

int main()
{
    char* sir = new char[lim+5]{0};
    citire_sir(sir);

    SyntaxTree<int> tree;
    tree.buildFromString(sir);
    cout << tree.evaluate() << endl;

    delete[] sir;
    return 0;
}
