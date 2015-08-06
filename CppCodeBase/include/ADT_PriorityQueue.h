#ifndef ADT_PRIORITYQUEUE_H
#define ADT_PRIORITYQUEUE_H


template <class T>
class ADT_PriorityQueue
{
    public:
        ADT_PriorityQueue(){};
        virtual ~ADT_PriorityQueue(){};

        virtual void insert(T elem) = 0;
        virtual T findMin() = 0;
        virtual T extractMin() = 0;
        virtual bool isEmpty() = 0;

    protected:
    private:
};

#endif // ADT_PRIORITYQUEUE_H
