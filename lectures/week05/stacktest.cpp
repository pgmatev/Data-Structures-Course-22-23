#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../week02/doctest.h"

#include "stack.cpp"

TEST_CASE("Inserting test")
{
    SUBCASE("Push test")
    {
        Stack<int> st;
        st.push(1);
        st.push(2);
        CHECK(st.size() == 2);
        st.push(3);
        CHECK(st.size() == 3);
        CHECK(st.top() == 3);
    }
}

TEST_CASE("Basic principles test")
{
    SUBCASE("Copy test")
    {
        Stack<int> st1;
        st1.push(1);
        st1.push(2);
        st1.push(3);
        Stack<int> st2(st1);
        CHECK(st1.size() == st2.size());
        CHECK(st2.top() == 3);
    }
}