#include <queue>
#include <iostream>

template<typename T>
struct Node {
    T data;   
    Node<T> *left; 
    Node<T> *right;

    Node(T data, Node<T>* left, Node<T>* right) {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

// interface used to visit nodes
template<typename T>
class NodeVisitor {
   public:
      // pure virtual function providing interface framework.
      virtual void visit(Node<T> node) = 0;
};
 
  
// we want to visit all node in level order
/*
     ┌──────┐
     │ root │.        (First level)
     └──┬───┘
   ┌────┴─────┐
   │          │
┌──┴───┐  ┌───┴───┐
│   L  │  │   R   │   (Second Level)
└──────┘  └───┬───┘
         ┌────┴─────┐
         │          │
      ┌──┴───┐  ┌───┴───┐
      │  R.L │  │  R.R  │   (Thrid Level)
      └──────┘  └───┬───┘
Root -> L -> R -> R.L -> R.R 
*/
template<typename T>
void bfs(Node<T>* root, const NodeVisitor<T> &visitor) {
    // first check base case if tree is empty - no nodes -then we have visited everything 
    if (!root)
    {
        return;
    }

    // Then we need to create empty queue to keep visited nodes with a name "queue"
    std::queue<Node<T>*> queue;
    
    // then we put the root (we will visit the root as it's the 0 level)
    queue.push(root);

    while ( !queue.empty() ) {
        // visit the first node 
        Node<T> node = queue.front(); 
        visitor.visit(node);
        queue.pop();

        // then we add to the queue the current visited node children
        queue.push(node.left);
        queue.push(node.right);
        std::cout << node.data << " ";
    }
    std::cout << std::endl;
}

int main()
{
    Node<int>* tree = new Node<int>{3, new Node<int>{9, nullptr, nullptr}, new Node<int>{20, new Node<int>{15, nullptr, nullptr}, new Node<int>{7, nullptr, nullptr}}};
    NodeVisitor<int> visitor;
    bfs(tree, visitor);
}