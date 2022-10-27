#include <iostream>
#include <stdexcept>

//vili codi
#include "linked_list.h"

template <typename T>
void LList<T>::clear()
{
    LList<T>::box* save = first;
    while(first != nullptr)
    {
        save = first;
        first = first->next;
        delete save;
    }
}

template <typename T>
void LList<T>::copy(const LList<T>::box* other_first)
{
    //we assume the list is empty
    LList<T>::box* last_created = nullptr;
    while(other_first != nullptr) //we can directly parse with other_first because its a copy of the pointer to the first elem 
    {
        LList<T>::box* new_box = new LList<T>::box {other_first->data, nullptr};
        if (last_created != nullptr)
        {
            last_created->next = new_box;
        }
        else
        {
            first = new_box;
        }
        last_created = new_box;
        other_first = other_first->next;
    }
}

template <typename T>
typename LList<T>::box* LList<T>::copy_rec(const LList<T>::box* other_first)
{
    if (other_first == nullptr)
    {
        return nullptr;
    }

    LList<T>::box* tail = copy_rec(other_first->next);
    return new LList<T>::box {other_first->data, tail};
}

template <typename T>
LList<T>::LList() : first(nullptr)
{}

template <typename T>
LList<T>::LList(const LList<T>& other) : first(nullptr)
{
    copy(other.first);
    first = copy_rec(other.first);
}

template <typename T>
LList<T>::LList(int x, int y) : first(nullptr)
{
    if(x <= y)
    {
        first = new LList<int>::box {x};
        LList<int>::box* curr = first;
        for (int i = x + 1; i <= y; i++)
        {
            LList<int>::box* new_box = new LList<int>::box {i};
            curr->next = new_box;
            curr = curr->next;
        }
    }  
}

template <typename T>
LList<T>::~LList()
{
    clear();
}

template <typename T>
void LList<T>::push(const T& x)
{
    // LList<T>::box* newBox = new LList<T>::box; 
    // newBox->data = x;
    // newBox->next = first;
    // first = &newBox;
    first = new LList<T>::box {x, first}; //not requiring a constructor
}

template <typename T>
void LList<T>::push_back(const T& x) //if we implement pointer to last elem it would be O(1)
{
    LList<T>::box* curr = first;
    while (curr->next != nullptr)
    {
        curr = curr->next;
    }
    curr->next = new LList<T>::box {x};
}
// template <typename T>
// void LList<T>::print() const
// {
//     LList<T>::box* crr = first;
//     while (crr != nullptr)
//     {
//         std::cout << crr->data << " ";
//         crr = crr->next;
//     }
//     std::cout << std::endl;
// }

template <typename T>
size_t LList<T>::size() const
{
    size_t i = 0;
    LList<T>::box* crr = first;
    while (crr != nullptr)
    {
        i++;
        crr = crr->next;
    }
    return i;
}

template <typename T>
void LList<T>::append(const LList<T>& other)
{
    if (first != nullptr)
    {
        LList<T>::box* curr = first;
        while (curr->next != nullptr)
        {
            curr = curr->next;
        }
        const LList<T>::box* other_first = other.first;
        while (other_first != nullptr)
        {
            LList<T>::box* new_box = new LList<T>::box {other_first->data, nullptr}; // we want to create copies of the elements of the second list
            curr->next = new_box;                                                   // instead of linking both lists because we want to avoid the double free error
            curr = new_box;
            other_first = other_first->next;
        }
    }
    else
    {
        copy(other.first);
    }
}

template <typename T>
T& LList<T>::operator[](size_t i)
{
    LList<T>::box* crr = first;
    for (int k = 0; k < i; k++)
    {
        if (crr->next == nullptr)
        {
            throw std::out_of_range("Index out of range!");
        }
        crr = crr->next;
    }
    return crr->data;
}

template <typename T>
T LList<T>::operator[](size_t i) const
{
    LList<T>::box* crr = first;
    for (int k = 0; k < i; k++)
    {
        if (crr->next == nullptr)
        {
            throw std::out_of_range("Index out of range!");
        }
        crr = crr->next;
    }
    return crr->data;
}

template <typename T>
LList<T>& LList<T>::operator=(const LList<T>& other)
{
    if (this != &other)
    {
        clear();
        copy(other.first);
    }
    return *this;
}

template <typename T>
LList<T>& LList<T>::operator+=(const T& x)
{
    LList<T>::box* curr = this->first;
    while (curr->next != nullptr)
    {
        curr = curr->next;
    }
    curr->next = new LList<T>::box {x};
    return *this;
}

template <typename T>
int LList<T>::count(T x)
{
    LList<T>::box* curr = first;
    int count = 0;
    while(curr != nullptr)
    {
        if(curr->data == x)
        {
            count++;
        }
        curr = curr->next;
    }
    return count;
}

template <typename T>
ListIterator<T> LList<T>::begin() const
{
    return ListIterator<T>(first, first);
}

template <typename T>
ListIterator<T> LList<T>::end() const
{
    return ListIterator<T>(first, nullptr);
}

template <typename T>
ListIterator<T>::ListIterator(typename LList<T>::box* first, typename LList<T>::box* current) : first(first), current(current)
{}

template <typename T>
ListIterator<T>& ListIterator<T>::operator++()
{
    if (current == nullptr)
    {
        throw std::out_of_range("Iterator out of range.");
    }
    current = current->next;
    return *this;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator--()
{
    typename LList<T>::box* curr = first;

    while (curr->next != current)
    {
        curr = curr->next;
    }
    current = curr;
    return *this;
}

template <typename T>
T ListIterator<T>::operator*() const
{
    if (current == nullptr)
    {
        throw std::out_of_range("Iterator out of range.");
    }
    return current->data;
}

template <typename T>
T& ListIterator<T>::operator*()
{
    if (current == nullptr)
    {
        throw std::out_of_range("Iterator out of range.");
    }
    return current->data;
}

template <typename T>
bool ListIterator<T>::operator!=(const ListIterator<T>& other) const
{
    return this->current != other.current;
}

template <typename T>
bool ListIterator<T>::operator==(const ListIterator<T>& other) const
{
    return this->current == other.current;
}