#ifndef QUEUE_HH
#define QUEUE_HH

template <class T>
class Queue
{
    private:
        struct box
        {
            T data;
            box* next;
        };
        box* head;
        box* tail;
    public:
        Queue();
        Queue(Queue& other);
        ~Queue();
        Queue& operator=(Queue& other);
        int size() const;
        void enqueue(T&);
        void dequeue();
        T peek() const;
        bool isEmpty();
};


#endif