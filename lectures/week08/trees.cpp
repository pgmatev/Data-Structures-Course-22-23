#include <iostream>
#include <fstream>
#include <assert.h>

template <typename T>
struct box
{
    T data;
    box* left;
    box* right;
};

template <typename T>
void setAt(box<T>*& root, const char* trace, const T& data)
{
    if (trace[0] == 0)
    {
        if (!root)
        {
            root = new box<T>{data, nullptr, nullptr};
        } else
        {
            root->data = data;
        }
        return;
    } else if (!root)
    {
        throw;
    }
    if (trace[0] == 'L')
    {
        return setAt(root->left, trace+1, data);
    }
    if (trace[0] == 'R')
    {
        return setAt(root->right, trace+1, data);
    }
    throw;
}

template <typename T>
void toDotty(box<T>* root, std::ostream& out)
{
    out << "Digraph G {\n";
    toDottyHelper(root, out);
    out << "}";
}

template <typename T>
void toDottyHelper(box<T>* root, std::ostream& out)
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
void toScheme(box<T>* root, std::ostream& out)
{
    if (!root)
    {
        out << "()";
        return;
    }
    out << "(" << root->data << " ";
    toScheme(root->left, out);
    out << " ";
    toScheme(root->right, out);
    out << ")";
}

template <typename T>
box<T>* fromScheme(std::istream& in)
{
    assert(in.get() == '(');

    if(in.peek() == ')') // if it is a closing bracket we have to remove it
    {
        in.get();
        return nullptr;
    }
    T data;
    in >> data;
    assert(in.get() == ' ');
    box<T> *left = fromScheme<T>(in);
    assert(in.get() == ' ');
    box<T>* right = fromScheme<T>(in);
    assert(in.get() == ')');
    return new box<T>{data, left, right};
}

template <typename T>
bool elem(box<T>* root, const T& x)
{
    return (root) && ((root->data == x) || elem(root->left, x) || elem(root->right, x));
}

template <typename T>
T count(box<T>* root, T& x)
{
    if (!root)
    {
        return 0;
    }

    return (root->data == x) + sum(root->left) + sum(root->right);
}

template <typename T>
bool equalTrees(box<T>* t1, box<T>* t2)
{
    return (!t1 && !t2) || (t1->data == t2->data) || (t1 && t2 && equalTrees<T>(t1->left, t2->left) && equalTrees<T>(t1->right, t2->right));
}

int main()
{
    box<char> *myTree = nullptr;
    setAt(myTree, "", 'I');
    setAt(myTree, "L", 'L');
    setAt(myTree, "R", 'O');
    setAt(myTree, "LR", 'V');
    setAt(myTree, "RL", 'E');
    setAt(myTree, "LRL", 'U');

    std::ofstream dot("trees.dot");
    std::ofstream scheme("trees.txt");
    toScheme(myTree, scheme);
    scheme.close();
    std::ifstream fscheme("trees.txt");
    box<char>* myTree2 = fromScheme<char>(fscheme);
    toDotty(myTree2, dot);

    std::cout << std::boolalpha << elem(myTree, 'C');

}