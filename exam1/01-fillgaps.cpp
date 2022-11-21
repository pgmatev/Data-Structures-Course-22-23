#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
template <typename T>
struct box {T data; box *next;};

/*Поставете тук реализация на функцията fillGaps*/
template <typename T>
box<T>* fillGaps(box<T>* L)
{
    if (L == nullptr)
    {
        return nullptr;
    }
    while (L->next != nullptr)
    {
        if (L->next->data > L->data + 1)
        {
            box<T>* save = L->next;
            L->next = new box<T>{L->data + 1, save};
            L = L->next;
        }
        else
        {
            L = L->next;
        }
    }
    return L;
}


TEST_CASE("fillGaps basic")
{
    box<int> *l1 = new box<int>{1,
                         new box<int>{3,
                             new box<int>{5,nullptr}}};

    fillGaps(l1);
    for (int i = 1; i <= 5; ++i)
    {
        CHECK(l1->data == i);
        l1 = l1->next;
    }
}

TEST_CASE("fillGaps edges")
{

    box<int> *l2 = new box<int>{1,nullptr};
    fillGaps(l2);
    CHECK(l2->next == nullptr);

    CHECK_NOTHROW(fillGaps<int>(nullptr));
}

