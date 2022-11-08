#include <iostream>
#include <stack>

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

int getSize(Node<int>* head)
{
    int counter = 0;
    while (head != nullptr)
    {
        counter++;
        head = head->next;
    }
    return counter;
}

bool isPalindrome(Node<int>* head)
{
    int i = getSize(head) / 2;
    std::stack<Node<int>*> s;
    Node<int>* curr = head;
    for (int j = 0; j < i; j++)
    {
        s.push(curr);
        curr = curr->next;
    }
    if (i % 2 != 0)
    {
        curr = curr->next;
    }

}

int main()
{

}