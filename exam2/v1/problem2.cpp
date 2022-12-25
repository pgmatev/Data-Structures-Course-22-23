#define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest.h"
#include "../treeutils.cpp"

#include <vector>

/*
======================
Решение на задачата:
======================
*/

#include <queue>
#include <stack>

template <typename T>
std::vector<T> levelsReverse(box<T>* root)
{
    if(!root) //празно дърво => празен вектор
    {
        return std::vector<T>();
    }

    std::queue<box<T>*> queue;
    queue.push(root);
    std::stack<box<T>*> visited;

    while(!queue.empty()) //bfs за да обходя дървото по нива
    {
        box<T>* node = queue.front();
        queue.pop();
        visited.push(node); //стек, за да обърна реда на елементите

        if(node->left)
        {
            queue.push(node->left);
        }
        if(node->right)
        {
            queue.push(node->right);
        }
    }
    std::vector<T> v;
    while(!visited.empty())
    {
        v.push_back(visited.top()->data);
        visited.pop();
    }
    return v;
}


/*
======================
Тестове
======================
*/
TEST_CASE("Edges") 
{
    box<int> *t=nullptr;
    CHECK(levelsReverse(t).size()==0);

    setAt(t,"",10);

    std::vector<int> expected = {10};
    CHECK(expected==levelsReverse(t));

}


TEST_CASE("Test Levels Reverse") 
{
    box<int> *t=nullptr;

    setAt(t,"",10);
    setAt(t,"L",20);
    setAt(t,"R",30);
    setAt(t,"RL",40);
    setAt(t,"RR",50);
    setAt(t,"RRL",60);

    std::vector<int> expected = {60, 50, 40, 30, 20, 10};
    CHECK(expected==levelsReverse(t));
    for (auto it : levelsReverse(t))
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;

}


int main()
{
    doctest::Context().run();
}