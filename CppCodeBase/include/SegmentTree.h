#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H

/* A segment tree for a fixed number of locations.
 * ADD_SEGMENT, POINT_QUERY, and remove_Segment run in n*log(n), where n is the total number of possible locations.
 *
 * Written by Bryce Summers on 8/3/2015
 *
 * Does not destroy inputs.
 */

// Coordinates and Segments.
template <typename Coord, typename Segment>
class SegmentTree
{

    class Node
    {
        Coord left;
        Coord right;
        std::set<Segment *> segments;
        Node * left;
        Node * right;
    };

    private:
        Node * root;

    public:

        SegmentTree(std::vector<T> & possible_coordinates);
        virtual ~SegmentTree();

        void addSegment(Coord left, Coord right, Segment * seg);

        // appends all of the segments that overlap the given point into the output vector.
        void pointQuery(Coord point, std::vector<Segment *> & output);

        // RETURNS true iff the given segment has been removed.
        bool removeSegment(Coord left, Coord right, Segment * seg);

    private:

        Node * buildTree(std::vector<T> & sorted_coordinate_list, int index_start, int index_end);

};

#endif // SEGMENTTREE_H
