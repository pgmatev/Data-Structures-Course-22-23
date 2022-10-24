#pragma once

template <typename T>
class ListIterator;


template <typename T>
class LList
{
    public:
        struct box
        {
            T data;
            box* next;
        };

    private:

        // struct box //capsulation, cannot access the data outside a linked list
        // {
        //     T data;
        //     box* next;
        // };
        box* first;

        void copy(const LList<T>::box* other_first);
        LList<T>::box* copy_rec(const LList<T>::box* other_first);

    public:
        using value_type = T;
        using iterator = ListIterator<T>;

        LList();
        LList(const LList<T>& other);
        LList(int x, int y);

        ~LList();

        void push(const T& x);
        void clear();
        int count(T x);
        void push_back(const T& x);
        void append(const LList<T>& other);
        // void print() const; --not oop 
        size_t size() const;

        T& operator[](size_t i);
        T operator[](size_t i) const; //if we want a const ll we cannot allow the user to access the data,
                                     // so we dont pass the adress
        LList<T>& operator=(const LList<T>& other);
        LList<T>& operator+=(const T& x);

        ListIterator<T> begin() const;
        ListIterator<T> end() const;
};

template <typename T>
class ListIterator
{
    private:
        // typename LList<T>::box* current;
        typename LList<T>::box* first;
    public:
        typename LList<T>::box* current;
        ListIterator(typename LList<T>::box* first, typename LList<T>::box* current);

        T operator*() const;
        T& operator*();
        ListIterator<T>& operator++();
        ListIterator<T>& operator--(); //not possible, as we don't save the context of previous elements in the Iterator, we need the LL instance to be able to go back and its still O(n), DLL can do it easily and it is O(1)
        bool operator!=(const ListIterator<T>& other) const;
        bool operator==(const ListIterator<T>& other) const;
};