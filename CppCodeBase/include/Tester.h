#ifndef TESTER_H
#define TESTER_H

#include "LeftistHeap.h"

// cout.
#include <iostream>

// Used for Custom runtime error.
#include <stdexcept>

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
