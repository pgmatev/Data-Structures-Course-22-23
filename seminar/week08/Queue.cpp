#include "Queue.hh"

template <class T>
Queue<T>::Queue() : head(nullptr), tail(nullptr)
{}

template <class T>
void Queue<T>::dequeue()
{
    Queue<T>::box* curr = head;
    head = head->next;
    delete curr;
}

template <class T>
void Queue<T>::enqueue(T& x)
{
    Queue<T>::box* new_box = {x, nullptr};
    tail->next = new_box;
    tail = tail->next;
}

template<class T>
T Queue<T>::peek() const
{
    return head->data;
}