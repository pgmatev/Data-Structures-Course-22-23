#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;
};

Node<int>* abs_sort(Node<int>* head, Node<int>* end)
{
    if (head != end)
    {
        Node<int>* current = head;
        while (current->next != end)
        {
            if (abs(current->data) > abs(current->next->data))
            {
                int a = current->data;
                current->data = current->next->data;
                current->next->data = a;
            }
            current = current->next;
        }
        end = current;
        return abs_sort(head, end);
    }
    return head;
}

void printNode(Node<int>* head)
{
    while (head != nullptr)
    {
        std::cout << head->data << std::endl;
        head = head->next;
    }
}

void sort_after_abs(Node<int>*& head)
{
    Node<int>* crr = head;
    while (crr->next != nullptr)
    {
        if (crr->next->data < 0)
        {
            Node<int>* temp = crr->next;
            crr->next = temp->next;
            temp->next = head;
            head = temp;
        }
        else
        {
            crr = crr->next;
        }
    }
}

int main()
{
    Node<int>* h3 = new Node<int>{3, nullptr};
    Node<int>* h2 = new Node<int>{-2, h3};
    Node<int>* h1 = new Node<int>{-4, h2};
    Node<int>* h0 = new Node<int>{5, h1};
    abs_sort(h0, nullptr);
    printNode(h0);
    std::cout << std::endl;
    sort_after_abs(h0);
    printNode(h0);
    delete h3;
    delete h2;
    delete h1; 
    delete h0;
}