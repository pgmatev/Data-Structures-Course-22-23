template <class T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;
};

template <class T>
bool areEqual(Node<T>* root1, Node<T>* root2)
{
    if (!root1 && !root2)
    {
        return true;
    }
    if (!root1 || !root2)
    {
        return false;
    }
    if (root1->data != root2->data)
    {
        return false;
    }
    return areEqual(root1->left, root2->left) && areEqual(root1->right, root2->right);
}

template <class T>
bool isSubTree(Node<T>* root, Node<T>* sub)
{
    if (!sub)
    {
        return true;
    }
    if (!root)
    {
        return false;
    }
    if (areEqual(root, sub))
    {
        return true;
    }
    return isSubTree(root->left, sub) || isSubTree(root->right, sub);
}