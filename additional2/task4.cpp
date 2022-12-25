template <class T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;
};

template <class T>
int sumOfTree(Node<T>* root)
{
    if (!root)
    {
        return 0;
    }
    return root->data + sumOfTree(root->left) + sumOfTree(root->right);
}

template <class T>
int subTreeSumCount(Node<T>* root, int k)
{
    if (!root)
    {
        return 0;
    }

    if (sumOfTree(root) == k)
    {
        return 1 + subTreeSumCount(root->left, k) + subTreeSumCount(root->right, k);
    }
    
    return subTreeSumCount(root->left, k) + subTreeSumCount(root->right, k);
}