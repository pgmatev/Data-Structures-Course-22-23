#ifndef STACK_HH
#define STACK_HH

template <class T>
class Stack
{
    private:
    struct box
    {
        T data;
        box *next;
    };
    box* head;
    size_t count;
    public:
    Stack();
    Stack(const Stack&);
    ~Stack();
    Stack& operator=(const Stack&);

    T top();
    void pop();
    void push(const T&);
    bool isEmpty();
    size_t size();
    box* copy(box*);
    void clear();

};

#endif