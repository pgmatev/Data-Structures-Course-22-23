#include <iostream>

#include "linked_list.cpp"

int main()
{
    LinkedList l;
    l.insertFirst(1);
    l.insertLast(2);
    l.insertFirst(0);
    // l.insertAfter(1, l[0]);
    l.insertAfter(7, l[1]);
    l.removeFirst();
    l.removeLast();
    l.backwards_print();
    l.print();
}