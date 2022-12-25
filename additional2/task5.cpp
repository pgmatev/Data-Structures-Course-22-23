template <class T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;
};

template <class T>
void reverseTree(Node<T>* root)
{
    if (!root)
    {
        return;
    }
    Node<T>* swap = root->left;
    root->left = root->right;
    root->right = swap;
    reverseTree(root->left);
    reverseTree(root->right);
}