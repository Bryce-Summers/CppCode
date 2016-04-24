#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H

/* A segment tree for a fixed number of locations.
 * ADD_SEGMENT, POINT_QUERY, and remove_Segment run in n*log(n),
 * where n is the cardinality of the set of coordinates given as an input to the constructor.
 *
 * Written by Bryce Summers on 8/3/2015
 *
 * Does not destroy inputs.
 *
 * Coord is a type used to denote some numeric coordinate position.
 * -- The author expects Coords to be small values such as ints, floats, etc that will be passed by value.
 * -- Coords must have an well defined total order to them. standard types such as ints, floats,
 *    etc have this ordering already specified in the C++ standard library.
 * Segment should be some genaric type that will be stored in the tree.
 * -- In all of the functions, the user will need to manually associate Segments with useful coordinates.
 *
 * The primary purpose of this tree is to maintain a set of overlapping intervals on a 1 dimensional line,
 * where given any point on this line, the set of intervals overlapping that point may be efficiently
 * queried.
 */

#include <set>
#include <vector>
#include <stdexcept> // Custom Runtime errors.

// Coordinates and Segments.
template <typename Coord, typename Segment>
class SegmentTree
{

    class Node
    {
        public:
            Coord left_coord;
            Coord right_coord;
            std::set<Segment> segments;
            Node * left_node;
            Node * right_node;
    };

    private:
        Node * root;

    public:

        /* Constructor.
         *
         * Requiring the input to be a set mandates that there are no duplicates,
         * and the Coordinates are in sorted order.
         */
        SegmentTree(std::set<Coord> & possible_coordinates)
        {

            typename std::set<Coord>::iterator iter = possible_coordinates.begin();

            std::vector<Coord> sorted_coordinates;

            while(iter != possible_coordinates.end())
            {
                sorted_coordinates.push_back(*iter);
                iter++;
            }

            int len = sorted_coordinates.size();

            root = buildTree(sorted_coordinates, 0, len);
        }

        virtual ~SegmentTree()
        {
            freeTree(root);
        }

        void addSegment(Coord left, Coord right, Segment seg)
        {
            // Reduce to a helper function.
            // true means 'add'
            addRemoveSegment(root, left, right, seg, true);
        }

        // appends all of the segments that overlap the given point into the output vector.
        // REQUIRES: point can be any Coordinate point, even those not in the initial set.
        void pointQuery(Coord point, std::vector<Segment> & output)
        {
            pointQuery(root, point, output);
        }

        // RETURNS true iff the given segment has been removed.
        bool removeSegment(Coord left, Coord right, Segment seg)
        {
            // Reduce to a helper function.
            // 'false' means 'remove'
            return addRemoveSegment(root, left, right, seg, false);
        }

    private:

        // Allocates a fixed tree for the given range of coordinate locations.
        Node * buildTree(std::vector<Coord> & sorted_coordinate_list, int index_start, int index_end)
        {
            if(index_start >= index_end)
            {
                return NULL;
            }

            Node * root = new Node();
            root ->  left_coord = sorted_coordinate_list[index_start];
            root -> right_coord = sorted_coordinate_list[index_end - 1];

            //root ->segments.clear();

            int split_index  = (index_start + index_end)/2;

            if(split_index > index_start)
            {
                root->left_node  = buildTree(sorted_coordinate_list, index_start, split_index);

                root->right_node = buildTree(sorted_coordinate_list, split_index, index_end);
            }
            else
            {

                root ->left_node = NULL;
                root ->right_node = NULL;
            }

            // The list of segments has already been allocated automatically.
        }

        void freeTree(Node * node)
        {
            if(node == NULL)
            {
                return;
            }

            freeTree(node -> left_node);
            freeTree(node -> right_node);
            delete node;
        }

        // This recursion REQUIRES that left and right were members of the
        // -- initial set used in the construction of this tree.
        // returns TRUE iff a segment has been properly removed from the tree.
        bool addRemoveSegment(Node * node, Coord left, Coord right, Segment seg, bool add)
        {
            if(node == NULL)
            {
                throw std::runtime_error("Malformed Coordinates or malformed tree.");
            }

            // seg INTERSECT node_interval == node_interval.
            // seg contains entire node interval.
            if(left <= node->left_coord && node->right_coord <= right)
            {
                if(add)
                {
                    (node ->segments).insert(seg);
                    return false;
                }
                else
                {
                    // Find the segment and then remove it through erasure if found.
                    typename std::set<Segment>::iterator iter = (node->segments).find (seg);
                    if(iter != (node->segments).end())
                    {
                        node->segments.erase(iter);
                        return true;
                    }
                    // Not Found.
                    return false;
                }
            }

            // seg INTERSECT node_interval == Empty set.
            // segment does not intersect the node interval.
            if(left >= node->right_coord || right <= node->left_coord)
            {
                return false;
            }

            // Segment partially intersects this interval.
            // Decompose into smaller and smaller intervals
            // until the intersection is not partial.
            bool b1, b2;
            b1 = addRemoveSegment(node->left_node,  left, right, seg, add);
            b2 = addRemoveSegment(node->right_node, left, right, seg, add);
            return b1 || b2;
        }

        void pointQuery(Node * node, Coord point, std::vector<Segment> & output)
        {
            // Dead end.
            if(node == NULL)
            {
                return;
            }

            // Point out of node's interval.
            if((point < node->left_coord) || (point > node->right_coord))
            {
                return;
            }

            // Point inside of node's interval.
            typename std::set<Segment>::iterator iter = node->segments.begin();

            while(iter != node->segments.end())
            {
                output.push_back(*iter);
                iter++;
            }

            pointQuery(node->left_node, point, output);
            pointQuery(node->right_node, point, output);

        }
};

#endif // SEGMENTTREE_H
