#ifndef BOT_HH
#define BOT_HH

#include <iostream>
#include <functional>

template <typename T>
struct Maybe
{
    T value;
    bool defined;
    Maybe() : defined(false)
    {}
    Maybe(const T& value) : value(value), defined(true)
    {}
};

template <typename T>
class BinOrdTree
{
    public:
    BinOrdTree();
    BinOrdTree(const BinOrdTree<T>&);
    ~BinOrdTree();
    BinOrdTree<T>& operator=(const BinOrdTree<T>&);
    
    void add(const T&);
    void addRec(const T&);
    void toDotty(std::ostream& out);

    bool member(const T&);
    size_t count();
    bool checkOrder();
    size_t countF(box*, std::function<bool(const T&>));


    private:
    struct box
    {
        T data;
        box* left;
        box* right;
    };
    box* root;
    void add(box*&, const T&);
    void toDotty(box* root, std::ostream& out);
    void toDottyHelper(box* root, std::ostream& out);

    bool member(box*, const T&);
    size_t count(box*);
    bool checkOrder(box*, const Maybe<T>&, const Maybe<T>&);

    box* copy(const box*);
    void clear(const box*);
    size_t countF(std::function<bool(const T&>));
};

#endif