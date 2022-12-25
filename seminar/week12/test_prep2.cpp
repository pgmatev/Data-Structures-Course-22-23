#include <vector>

#include "node.h"

/***********************************************************************
  Задача 2. Даден е вектор v от цели числа. Казваме, че двоичното
  дърво с положителни числа по върховете t представя v при следните
  условия:

    * v е празният вектор и t е празното дърво; или
    * ако v = v[0],…,v[k-1], a m = ⌊k / 2⌋ (долна цяла част), то коренът
    на t съдържа числото v[m], лявото поддърво на t представя вектора
    v[0],…,v[m-1], а дясното поддърво на t представя вектора
    v[m+1],…,v[k-1].

  Забележка: ако k = 2, то десния подвектор считаме за празен.

  Нека е даден следният шаблонът Node, дефиниран в node.h.
************************************************************************/

/***********************************************************************
  а) Да се реализира функция, която построява дърво, представящо
  вектора v, и връща указател към корена му.

  Упътване: Ако v е вектор, то с помощта на следния конструктор
  std::vector<unsigned> L(v.begin(), v.begin() + count) ще получите
  първите count елемента от v,
  а с std::vector<unsigned> R (v.begin() + start, v.end()), ще
  получите суфикса на v, започващ от елемента с индекс start.

  Пример:
  std::vector<unsigned> v{1, 2, 3, 4, 5, 6},
                        L(v.begin(), v.begin() + 3),
                        R(v.begin() + 4, v.end());

  Тогава L е векторът 1, 2, 3, а R е векторът 5, 6.

 РЕШЕНИЕ:
************************************************************************/

Node<unsigned>* buildTreeHelper(const std::vector<unsigned>& v, int start, int end)
{
    if (start > end)
    {
        return nullptr;
    }

    int middle = (start + end + 1) / 2;
    Node<unsigned>* root = new Node<unsigned>{v[middle], nullptr, nullptr};
    root->left = buildTreeHelper(v, start, middle-1);
    root->right = buildTreeHelper(v, middle+1, end);
    return root;
}

Node<unsigned>* buildTree (const std::vector<unsigned>& v)
{
    return buildTreeHelper(v, 0, v.size() - 1);
}



/***********************************************************************
 б) Да се реализира функция, която връща вектор, съставен от възлите
 по път в дървото от корен до листо, в който сумата на елементите е
 максимална.

 РЕШЕНИЕ:
************************************************************************/


#include <algorithm>

void treeSum(Node<unsigned>* t, unsigned current_sum, unsigned max_sum, std::vector<unsigned>& current_path, std::vector<unsigned>& max_path)
{
    if (!t)
    {
        return;
    }
    current_path.push_back(t->data);
    if(!t->left && !t->right)
    {
        if (current_sum + t->data > max_sum)
        {
            max_sum = current_sum + t->data;
            max_path = current_path;
        }
        current_path.clear();
    }

    treeSum(t->left, current_sum + t->data, max_sum, current_path, max_path);
    treeSum(t->right, current_sum + t->data, max_sum, current_path, max_path);
}



std::vector<unsigned> sumMax(Node<unsigned>* t)
{
    std::vector<unsigned> max_path;
    std::vector<unsigned> current_path;
    treeSum(t, 0, 0, current_path, max_path);
    return max_path;

}

/***********************************************************************
 КРАЙ НА РЕШЕНИЕТО
************************************************************************/

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

/***********************************************************************
  РАЗКОМЕНТИРАЙТЕ СЛЕДВАЩИЯ РЕД, ЗА ДА ВКЛЮЧИТЕ ТЕСТОВЕТЕ
************************************************************************/
#include "prob2_tests.h"

int main ()
{
    // пускане на тестовете
    doctest::Context().run();
    return 0;
}