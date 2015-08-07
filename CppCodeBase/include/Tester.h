#ifndef TESTER_H
#define TESTER_H

#include "LeftistHeap.h"
#include "SegmentTree.h"

// cout.
#include <iostream>

// Used for Custom runtime error.
#include <stdexcept>

#include <set>
//#include <vector>


class Tester
{
    public:
        Tester();
        virtual ~Tester();

    protected:
    private:

        void ASSERT(bool b);

        void testLeftistHeap();
        void testSegmentTree();
        void testKDTree();

};

#endif // TESTER_H
