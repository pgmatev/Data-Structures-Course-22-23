#include <iostream>


class Node
{
public:
    int value;
    Node* next;

    Node(int value) : value(value), next(nullptr)
    {}

    Node(int value, Node* pointer) : value(value), next(pointer)
    {}
};

class LinkedList
{
private:
    Node* head;
    Node* tail;
public:
    LinkedList() : head(nullptr), tail(nullptr)
    {}
    // LinkedList(Node* first) : first(first)
    // {}

    void print()
    {
        Node* current = this->head;
        while (current != nullptr)
        {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void insertFirst(int value)
    {
        Node* new_node = new Node(value, this->head);
        this->head = new_node;
        if(tail == nullptr)
        {
            this->tail = new_node;
        }
    }

    void insertLast(int value)
    {
        Node* new_node = new Node(value);
        if (this->tail == nullptr)
        {
            insertFirst(value);
        }
        else 
        {
            this->tail->next = new_node;
            this->tail = this->tail->next;
        }
    }

    void insertAfter(int value, Node* iterator)
    {
        if (iterator != nullptr)
        {
            Node* node = new Node(value);
            node->next = iterator->next;
            iterator->next = node;

            if (iterator->next == nullptr)
            {
                this->tail = node;
            }
        }
    }

    int removeFirst()
    {
        if (this->head != nullptr)
        {
            Node* head_cpy = this->head;
            this->head = this->head->next;
            int value_cpy = head_cpy->value;
            delete head_cpy;
            return value_cpy;
        }
        throw;
    }

    int removeLast()
    {
        if (this->tail != nullptr)
        {
            Node* current = this->head;
            while (current->next != this->tail)
            {
                current = current->next;
            }
            this->tail = current;
            int value_cpy = current->next->value;
            delete current->next;
            current->next = nullptr;
            return value_cpy;
        }
        throw;
    }

    int removeAfter(Node* iterator)
    {
        if (this->tail != nullptr)
        {
            if (iterator == nullptr || iterator == this->tail)
            {
                return;
            }

            else
            {
                Node* node_cpy = iterator->next;
                if (node_cpy == this->tail)
                {
                    removeLast();
                }
                int value_cpy = node_cpy->value;
                iterator->next = node_cpy->next;
                delete node_cpy;
                return value_cpy;
            }
        }
        throw;
    }
};

int main()
{
    LinkedList ll;
    ll.insertFirst(0);
    ll.insertLast(1);
    ll.insertFirst(2);
    ll.insertLast(3);
    std::cout << "Removed first element: " << ll.removeFirst() << std::endl;
    std::cout << "Removed last element: " << ll.removeLast() << std::endl;
    ll.print();
}