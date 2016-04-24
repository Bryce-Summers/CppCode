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

/*
namespace std
{

    bool operator< (std::pair<int, int> &p1, std::pair<int, int> &p2)
    {
        if(p1.first < p2.first)
        {
            return true;
        }

        if(p1.first == p2.first &&
           p1.second == p2.second)
        {
            return true;
        }

        return false;
    }

}*/

#endif // TESTER_H
