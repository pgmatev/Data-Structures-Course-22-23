#include <string>


template <class T>
struct Node
{
    T value;
    Node<T>* left;
    Node<T>* right;
};

template <class T, class U>
class Dictionary
{
    Node<std::pair<T, U>> root;

    bool exists(T& key, Node<std::pair<T, U>>& root)
    {
        if (!root)
        {
            return false;
        }
        if (root.value.first == key)
        {
            return true;
        }
        return exists(key, root.left) || exists(key, root.right);
    }

    void addHelper(Node<std::pair<T,U>>& node, Node<std::pair<T,U>>& root)
    {
        T key = node.value.first;
        T root_key = root.value.first;

        if (key < root_key)
        {
            if (!root.left)
            {
                root.left = node;
            }
            else
            {
                addHelper(node, root.left);
            }

        }
        else if (key > root_key)
        {
            if (!root.right)
            {
                root.right = node;
            }
            else
            {
                addHelper(node, root.right);
            }
        }
    }
    
    public:
    void add(T& key, U& value)
    {
        Node<std::pair<T,U>> new_node = new Node{std::pair(key, value), nullptr, nullptr};
        if (!exists(key, this->root))
        {
            addHelper(new_node, this->root);
        }
    }
    void addIt(T& key, U& value)
    {
        Node<std::pair<T,U>> new_node = new Node{std::pair(key, value), nullptr, nullptr};
        Node<std::pair<T,U>> curr = this->root;
        while ((curr->left && cur->value > new_node.value) || (cur->right && cur->value <= new_node.value))
        {
            if (new_node.value >= curr.value)
            {
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        }
        if(cur->value > new_node.value)
        {
            cur->left = new_node;
        }
        else
        {
            cur->right = new_node;
        }
    }

    void remove(T& key)
    {
        Node<std::pair<T,U>* parent;
        Node<std::pair<T,U>* toDeleteNode = find(key, &parent);
        //to do
    }
    void traverse(Node<T>* root) //in order
    {
        if (root == nullptr)
        {
            return;
        }
        traverse(root->left);
        std::cout << root->value;
        traverse(root->right);
    }

    void bfs(Node<T>* root)
    {
        if (root == nullptr)
        {
            return;
        }
        std::cout << 
    }
};
