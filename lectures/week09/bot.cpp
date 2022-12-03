#include "bot.hh"

template <typename T>
BinOrdTree<T>::BinOrdTree() : root(nullptr)
{}

template <typename T>
BinOrdTree<T>::BinOrdTree(const BinOrdTree<T>& other)
{
    root = copy(other.root);
}

template <typename T>
BinOrdTree<T>::~BinOrdTree()
{
    clear(root);
}

template <typename T>
BinOrdTree<T>& BinOrdTree<T>::operator=(const BinOrdTree<T>& other)
{
    if (this != &other)
    {
        clear(root);
        root = copy(other.root);
    }
    return *this;
}

template <typename T>
typename BinOrdTree<T>::box* BinOrdTree<T>::copy(const typename BinOrdTree<T>::box* other_root)
{
    if (!other_root)
    {
        return nullptr;
    }
    return new typename BinOrdTree<T>::box {other_root->data, copy(other_root->left), copy(other_root->right)};
}

template <typename T>
void BinOrdTree<T>::clear(const typename BinOrdTree<T>::box* current)
{
    if (!current)
    {
        return;
    }

    clear(current->left);
    clear(current->right);
    delete current;
}

template <typename T>
void BinOrdTree<T>::add(const T& x)
{    
    if (!root)
    {
        root = new BinOrdTree<T>::box {x, nullptr, nullptr};
        return;
    }
    else
    {
        BinOrdTree<T>::box* crr = root;
        while (!((crr->left == nullptr && x < crr->data) || (crr->right == nullptr && x >= crr->data)))
        {
            if (x < crr->data)
            {
                crr = crr->left;
            }
            else if (x >= crr->data)
            {
                crr = crr->right;
            }
        }

        if (x < crr->data)
        {
            crr->left = new BinOrdTree<T>::box {x, nullptr, nullptr};
        }
        if (x >= crr->data)
        {
            crr->right = new BinOrdTree<T>::box {x, nullptr, nullptr};
        }
    }
}

template <typename T>
void BinOrdTree<T>::addRec(const T& x)
{
    add(root, x);
}

template <typename T>
void BinOrdTree<T>::add(BinOrdTree<T>::box*& current, const T& x)
{
    if (current == nullptr)
    {
        current = new BinOrdTree<T>::box {x, nullptr, nullptr};
        return;
    }
    if (x < current->data)
    {
        add(current->left, x);
    }
    else
    {
        add(current->right, x);
    }
}

template <typename T>
void BinOrdTree<T>::toDotty(BinOrdTree<T>::box* root, std::ostream& out)
{
    out << "Digraph G {\n";
    toDottyHelper(root, out);
    out << "}";
}

template <typename T>
void BinOrdTree<T>::toDotty(std::ostream& out)
{
    return toDotty(this->root, out);
}

template <typename T>
void BinOrdTree<T>::toDottyHelper(BinOrdTree<T>::box* root, std::ostream& out)
{
    if(!root)
    {
        return;
    }   

    toDottyHelper(root->left, out);
    toDottyHelper(root->right, out);

    out << (long)root << "[label=\"" << root->data << "\"];\n"; //outputs as ###[label="###"];

    if (root->left)
    {
        out << (long)root << "->" << (long)root->left << "[label = \"L\" color = \"blue\"]\n"; //outputs as ###->###;
    }

    if (root->right)
    {
      out << (long)root << "->" << (long)root->right << "[label= \"R\" color = \"red\"]\n";
    }

}

template <typename T>
bool BinOrdTree<T>::member(const T& x)
{
    return member(root, x);
}

template <typename T>
bool BinOrdTree<T>::member(BinOrdTree<T>::box* root, const T& x)
{
    return root && (root->data == x || member(root->left, x) || member(root->right, x));
}

template <typename T>
size_t BinOrdTree<T>::count()
{
    return count(root);
}

template <typename T>
size_t BinOrdTree<T>::count(BinOrdTree<T>::box* current)
{
    if (!current)
    {
        return 0;
    }

    return 1 + count(current->left) + count(current->right);
}

template <typename T>
bool BinOrdTree<T>::checkOrder()
{
    return checkOrder(root, Maybe<T>(), Maybe<T>());
}

template <typename T>
bool BinOrdTree<T>::checkOrder(BinOrdTree<T>::box* current, const Maybe<T>& min, const Maybe<T>& max)
{
    if (!current)
    {
        return true;
    }

    if ((min.defined && current->data <= min.value) || (max.defined && current->data > max.value))
    {
        return false;
    }

    return checkOrder(current->left, min, Maybe<T>(current->data)) && checkOrder(current->right, Maybe<T>(current->data), max);
}