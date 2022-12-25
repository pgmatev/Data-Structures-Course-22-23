#define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest.h"
#include "../treeutils.cpp"

#include <vector>

/*
======================
Решение на задачата:
======================
*/

// Разлика на дървета: Ако при еднакво обхождане на двете дървета, 
// тоест съпоставяме позициите на елементите, съществуват елементи на същите позиции и в двете дървета
// трябва да ги извадим, а ако съществува само в първото дърво и на същата позиция във второто нямаме елемент,
// (тоест nullptr) не трябва да го извадим.
template <typename T>
void diffHelperOneT(box<T>* t1, std::vector<T>& v)
{
    if (!t1)
    {
        return;
    }
    v.push_back(t1->data);
    diffHelperOneT(t1->left, v);
    diffHelperOneT(t1->right, v);
}

template <typename T>
void diffHelper(box<T>* t1, box<T>* t2, std::vector<T>& v)
{
    if (!t1)
    {
        return;
    }
    if (t1 && !t2)
    {
        diffHelperOneT(t1,v); //ако няма елементи в т2 на позициите, започваме да добавяме тези от т1
    }
    else //т2 съществува, продължаваме обхождането
    {
        diffHelper(t1->left, t2->left, v);
        diffHelper(t1->right, t2->right, v);
    }
    return;
}

template <typename T>
std::vector<T>  diff(box<T>* t1, box<T>* t2)
{
    std::vector<T> v;
    diffHelper(t1, t2, v);
    return v;
}


/*
======================
Тестове
======================
*/
TEST_CASE("Test Edges")
{
     box<int> *t1=nullptr,
              *t2=nullptr;

    setAt(t2,"",0);
    setAt(t2,"R",0);

    CHECK(diff(t1,t2).size()==0);
    CHECK(set_equals(diff(t2,t1),{0}));
   
}

TEST_CASE("Test Diff") 
{
    box<int> *t1=nullptr,
             *t2=nullptr;

    setAt(t1,"",10);
    setAt(t1,"L",20);
    setAt(t1,"R",30);
    setAt(t1,"RL",40);
    setAt(t1,"RR",50);
    setAt(t1,"RRL",60);

    setAt(t2,"",0);
    setAt(t2,"R",0);

    CHECK(set_equals(diff(t1,t2),{20,40,50,60}));

}

int main()
{
    doctest::Context().run();
}