#include <iostream>
#include <stdexcept>

class Node
{
public:
    int value;
    Node* previous;
    Node* next;

    Node(int value) : value(value), next(nullptr), previous(nullptr)
    {}

    Node(int value, Node* previous) : value(value), previous(previous)
    {}

    Node(int value, Node* previous, Node* next) : value(value), previous(previous), next(next)
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

    // ~LinkedList()
    // {
    //     while(this->head != nullptr)
    //     {
    //         this->head = this->head->next;
    //         delete this->head->previous;
    //     }
    // }

    void print() const
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
        if (this->head == nullptr)
        {
            this->head = new Node(value, nullptr, nullptr);
        }
        else
        {
            this->head->previous = new Node(value, nullptr, this->head);
            this->head = this->head->previous;
        }
        if(tail == nullptr)
        {
            this->tail = this->head;
        }
    }

    void insertLast(int value)
    {
        if (this->tail == nullptr)
        {
            insertFirst(value);
        }
        else 
        {
            Node* new_node = new Node(value, this->head, nullptr);
            this->tail->next = new_node;
            this->tail = this->tail->next;
        }
    }

    void insertAfter(int value, Node* iterator)
    {
        if (iterator != nullptr)
        {
            Node* node = new Node(value, iterator, iterator->next);
            if (iterator->next == nullptr)
            {
                this->tail = node;
            }
            iterator->next = node;
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
        if (this->head == this->tail)
        {
            return removeFirst();
        }
        if (this->tail != nullptr)
        {
            this->tail = this->tail->previous;
            int value_cpy = this->tail->next->value;
            delete this->tail->next;
            this->tail->next = nullptr;
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
                throw;
            }

            else
            {
                Node* node_cpy = iterator->next;
                if (node_cpy == this->tail)
                {
                    return removeLast();
                }
                int value_cpy = node_cpy->value;
                iterator->next = node_cpy->next;
                delete node_cpy;
                return value_cpy;
            }
        }
        throw;
    }

    Node* operator[](size_t index)
    {
        Node* curr = head;
        for (int i = 0; i < index; i++)
        {
            if (curr->next != nullptr)
            {
                curr = curr->next;
            }
            else
            {
                throw std::out_of_range("Invalid index");
            }
        }
        return curr;
    }
};