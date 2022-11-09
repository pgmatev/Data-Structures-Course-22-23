#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;
};

void printNode(Node<int>* head)
{
    while (head != nullptr)
    {
        std::cout << head->data << std::endl;
        head = head->next;
    }
}
Node<int>* fibonaciList(int n)
{
    if (n == 0)
    {
        return new Node<int>{1, nullptr};
    }
    if (n == 1)
    {
        return new Node<int>{1, fibonaciList(n-1)};
    }
    return new Node<int>{fibonaciList(n-1)->data + fibonaciList(n-2)->data, fibonaciList(n-1)};
}

int main()
{
    Node<int>* ll = fibonaciList(5);
    printNode(ll);
}