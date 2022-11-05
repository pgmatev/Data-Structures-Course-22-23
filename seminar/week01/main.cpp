#include <iostream>

#include "linked_list.cpp"

int main()
{
    LinkedList l;
    l.insertFirst(1);
    l.insertLast(2);
    l.insertLast(21);
    l.insertLast(22);
    l.insertFirst(0);
    l.removeAfter(l[0]);
    // l.insertAfter(7, l[1]);
    // l.removeFirst();
    // l.removeLast();
    // l.backwards_print();
    l.print();
    l.reverseList();
    l.print();
}