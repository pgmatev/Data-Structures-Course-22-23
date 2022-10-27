#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "linked_list.cpp"
#include "iterator_tasks.cpp"

TEST_CASE("Inserting elements tests")
{
    SUBCASE("Push test")
    {
        LList<int> l;
        l.push(5);
        l.push(3);
        l.push(2);

        CHECK(l.size() == 3);
        CHECK(l[0] == 2);
        CHECK(l[1] == 3);
        CHECK(l[2] == 5);
    }
    SUBCASE("Push back test")
    {
        LList<int> l(1,3);
        l.push_back(4);
        CHECK(l.size() == 4);
        CHECK(l[3] == 4);
    }
    SUBCASE("Append test")
    {
        LList<int> l1(1,3);
        LList<int> l2(4,6);
        CHECK(l1.size() == 3);
        l1.append(l2);
        CHECK(l1.size() == 6);
        CHECK(l1[0] == 1);
        CHECK(l1[5] == 6);

        LList<int> l3;
        LList<int> l4;
        l3.append(l2);
        CHECK(l3.size() == l2.size());
        l2.append(l4);
        CHECK(l2.size() == l3.size());
    }
}

TEST_CASE("Integral functions tests")
{
    SUBCASE("Interval constructor test")
    {
        LList<int> l(1, 5);
        CHECK(l[0] == 1);
        CHECK(l[4] == 5);
        CHECK(l.size() == 5);

        LList<int> l2(5,1);
        CHECK(l2.size() == 0);
    }

    SUBCASE("Clear test")
    {
        LList<int> l;
        l.push(5);
        l.push(3);
        l.push(2);

        l.clear();
        CHECK(l.size() == 0);

        l.clear();
        l.push(0);
        CHECK(l.size() == 1);

        LList<int> l2;
        l2.clear();
        CHECK(l2.size() == 0);
    }

    SUBCASE("Copy test")
    {
        LList<int> l1(0,2);
        LList<int> l2(l1);

        CHECK(l1.size() == l2.size());
        CHECK(l1[0] == l2[0]);

        l1[1] = 3;
        CHECK(l1[1] != l2[1]);

        l1.clear();

        CHECK(l2.size() > 0);
    }
}

TEST_CASE("Count test")
{
    LList<int> l;
    l.push(5);
    l.push(3);
    l.push(2);
    l.push(5);
    l.push(1);

    CHECK(l.count(5) == 2);
    l.clear();
    CHECK(l.count(5) == 0);
}

TEST_CASE("Operator += test")
{
    LList<int> l(1,3);
    l+=4;
    l+=5;
    l+=6;
    CHECK(l.size() == 6);
    CHECK(l[0] == 1);
    CHECK(l[5] == 6);
}

// TEST_CASE("Iterator -- test")
// {
//     LList<int> l1(1,3);

//     CHECK(reverse_sum(l1) == 6);
// }

TEST_CASE("Iterator tasks tests")
{
    SUBCASE("Sum test")
    {
        LList<int> l1(1,3);
        CHECK(sum(l1) == 6);
    }
    SUBCASE("Map test")
    {
        LList<int> l1(1,3);
        l1 = map(l1, *square<int>);

        CHECK(l1[0] == 1);
        CHECK(l1[1] == 4);
        CHECK(l1[2] == 9);
        CHECK(l1.size() == 3);
    }
    SUBCASE("Dublicates test")
    {
        LList<int> l(1,3);
        CHECK(dublicates(l) == false);
        l.push(1);
        CHECK(dublicates(l) == true); 
    }
}