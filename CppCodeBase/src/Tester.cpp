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
    std::set<int> coords;

    for(int i = 0; i < 10; i++)
    {
        coords.insert(i);
        coords.insert(-i);
    }

    typedef std::pair<int, int> Interval;

    SegmentTree<int, Interval > tree(coords);

    Interval i1 = std::pair<int, int>(0, 100);
    Interval i2 = std::pair<int, int>(20, 80);

    std::cout << i1.first << ", " << i1.second << std::endl;

    tree.addSegment(0, 100, i1);
    tree.addSegment(0, 100, i2);

    std::vector<Interval> segments;

    tree.pointQuery(1, segments);

    ASSERT(segments.size() == 1);

}

void Tester::testKDTree()
{

}
