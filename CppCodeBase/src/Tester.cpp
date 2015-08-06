#include "Tester.h"

Tester::Tester()
{
    testLeftistHeap();
    testSegmentTree();
    testKDTree();

    std::cout << "All Tests have PASSED!!!" << std::endl;
}

Tester::~Tester()
{
    //dtor
}

void Tester::ASSERT(bool b)
{
    if(!b)
    {
        throw std::runtime_error("ASSERTION FAILED");
    }

    return;
}

void Tester::testLeftistHeap()
{
    LeftistHeap<int> heap;

    ASSERT(heap.isEmpty());

    heap.insert(0);
    ASSERT(!heap.isEmpty());
    heap.insert(-2);
    heap.insert(-1);
    heap.insert(3);
    heap.insert(2);
    heap.insert(1);
    heap.insert(-3);

    ASSERT(!heap.isEmpty());

    ASSERT(heap.findMin() == -3);
    ASSERT(heap.extractMin() == -3);

    ASSERT(heap.findMin() == -2);
    ASSERT(heap.extractMin() == -2);

    ASSERT(heap.findMin() == -1);
    ASSERT(heap.extractMin() == -1);

    ASSERT(heap.findMin() == 0);
    ASSERT(heap.extractMin() == 0);

    ASSERT(heap.findMin() == 1);
    ASSERT(heap.extractMin() == 1);

    ASSERT(heap.findMin() == 2);
    ASSERT(heap.extractMin() == 2);

    ASSERT(heap.findMin() == 3);
    ASSERT(heap.extractMin() == 3);


}

void Tester::testSegmentTree()
{

}

void Tester::testKDTree()
{

}
