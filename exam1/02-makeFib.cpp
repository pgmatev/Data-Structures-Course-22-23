#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>

template <typename T>
struct box {T data; box *next;};

/*Поставете тук реализация на функцията makeFib*/
template <typename T>
void makeFib(box<T>*& first)
{
    if (first == nullptr || first->next == nullptr || first->next->next == nullptr)
    {
        return;
    }
    if (first->next->next->data = first->data + first->next->data)
    {
        return makeFib(first->next);
    }
    else 
    {
        box<int>* temp = first->next->next;
        first->next->next = temp->next;
        delete temp;
        return makeFib(first->next);
    }
}

TEST_CASE("makeFib basic")
{
    box<int> *l1 = new box<int>{1,
                         new box<int>{1,
                             new box<int>{2,
                                 new box<int>{2,
                                      new box<int>{2,
                                          new box<int>{3,
                                              new box<int>{5,
                                                  new box<int>{9,nullptr}}}}}}}};
    makeFib(l1);
    int expected[] = {1,1,2,3,5};
    for (int x: expected)
    {
        CHECK(x==l1->data);
        l1=l1->next;
    }

}

TEST_CASE("makeFib edges")
{
    box<int> *l2 = new box<int>{1,nullptr};
    CHECK_NOTHROW(makeFib(l2));
    CHECK(l2->data == 1);

    box<int> *l3 = new box<int>{1,new box<int>{2,nullptr}};
    CHECK_NOTHROW(makeFib(l3));
    CHECK(l3->next->data == 2);

    // CHECK_NOTHROW(makeFib<int>(nullptr));
}


