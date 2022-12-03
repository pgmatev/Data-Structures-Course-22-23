#include "bot.cpp"
#include <fstream>

int main()
{
    BinOrdTree<int> t;
    t.addRec(50);
    t.addRec(30);
    t.addRec(20);
    t.addRec(40);
    t.addRec(90);
    t.addRec(99);
    t.addRec(70);

    BinOrdTree<int> t2(t);
    std::ofstream diagraph("binOrdTree.dot");
    t2.toDotty(diagraph);
    std::cout << std::boolalpha << t2.checkOrder() << std::endl;
    std::cout << t2.count() << std::endl;
    std::cout << std::boolalpha << t2.member(90) << std::endl;
}