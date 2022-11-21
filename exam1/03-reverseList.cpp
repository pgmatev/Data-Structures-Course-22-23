#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <stack>

template <typename T>
struct box {T data; box *next;};

/*Поставете тук реализация на функцията reverseList*/
template <typename T>
void reverseList(box<T>*& first, unsigned int n) // O(n^2) time complexity, O(1) memory complexity
{
    if (n > 0)
    {
        box<T>* curr = first;
        int i = n - 1;
        while (i > 0)
        {
            if (curr != nullptr && curr->next != nullptr)
            {
                int temp = curr->next->data;
                curr->next->data = curr->data;
                curr->data = temp;
                curr = curr->next;
                i--;
            }
            else
            {
                return;
            }

        }
        reverseList(first, n-1);
    }
}

template <typename T>
void reverseListStack(box<T>*& first, unsigned int n) // O(n+n) time complexity O(n) memory complexity
{
    std::stack<T> stack;
    box<T>* curr = first;
    while (n > 0)
    {
        if (curr == nullptr)
        {
            break;
        }

        stack.push(curr->data);
        curr = curr->next;
        n--;
    }
    curr = first;
    while (stack.size() > 0)
    {
        curr->data = stack.top();
        stack.pop();
        curr = curr->next;
    }
}

TEST_CASE("Reverse basic")
{
    box<int> *l1 = new box<int>{1,
                         new box<int>{2,
                             new box<int>{3,
                                 new box<int>{4,
                                      new box<int>{5,
                                          new box<int>{6,
                                              new box<int>{7,
                                                  new box<int>{8,nullptr}}}}}}}};
    box<int> *l2 = new box<int>{1,
                         new box<int>{2,
                             new box<int>{3,
                                 new box<int>{4,
                                      new box<int>{5,
                                          new box<int>{6,
                                              new box<int>{7,
                                                  new box<int>{8,nullptr}}}}}}}};
    reverseList(l1,4);
    reverseListStack(l2, 3);
    int expected[] = {4,3,2,1,5,6,7,8};
    int expected2[] = {3,2,1,4,5,6,7,8};
    for (int x: expected)
    {
        CHECK(x==l1->data);
        l1=l1->next;
    }
    for (int x: expected2)
    {
        CHECK(x==l2->data);
        l2=l2->next;
    }

}

TEST_CASE("Reverse edges")
{
    box<int> *l1 = new box<int>{1, new box<int>{2,nullptr}};
    box<int> *l2 = new box<int>{1, new box<int>{2,nullptr}};
    reverseList(l1,10);
    reverseListStack(l2,10);
    CHECK(l1->data == 2);
    CHECK(l1->next->data == 1);
    CHECK(l2->data == 2);
    CHECK(l2->next->data == 1);

    // CHECK_NOTHROW(reverseList(l1->next,10));
    // CHECK_NOTHROW(reverseList<int>(nullptr,10));
}


