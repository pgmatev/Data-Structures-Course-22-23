#include <iostream>

template <class T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;
};

template <class T>
void nodesAtLevel(Node<T>* root, int k)
{
    if (!root)
    {
        return;
    }
    if (k == 0)
    {
        std::cout << root->data << " ";
        return;
    }

    nodesAtLevel(root->left, k-1);
    nodesAtLevel(root->right, k-1);
}