#include "stack.hh"

#include <cassert>

template <class T>
Stack<T>::Stack() : count(0), head(nullptr)
{}

template <class T>
Stack<T>::Stack(const Stack<T>& other)
{
    head = copy(other.head);
}

template <class T>
Stack<T>::~Stack()
{
    this->clear();
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if (*this != other)
    {
        clear();
        this->head = copy(other.head);
    }
    return *this;
}

template <class T>
void Stack<T>::push(const T& x)
{
    head = new Stack<T>::box{x, head};
    count++;
}

template <class T>
void Stack<T>::pop()
{
    assert(head != nullptr);
    Stack<T>::box* head_cpy = head;
    head = head->next;
    delete head_cpy;
    count--;
}

template <class T>
T Stack<T>::top()
{
    return head->data;
}

template <class T>
size_t Stack<T>::size()
{
    return count;
}


template <class T>
typename Stack<T>::box* Stack<T>::copy(typename Stack<T>::box *other_head)
{
    if (other_head == nullptr)
    {
        return nullptr;
    }
    return new Stack<T>::box {other_head->data, copy(head->next)};
}

template <class T>
void Stack<T>::clear()
{
    while (!this->isEmpty())
    {
        this->pop();
    }
}

template <class T>
bool Stack<T>::isEmpty()
{
    if (this->count > 0)
    {
        return false;
    }
    return true;
}

