#ifndef LEFTISTHEAP_H
#define LEFTISTHEAP_H

#include "ADT_PriorityQueue.h"

// NULL, size_t, etc...
#include <cstddef>

/*
 * Standard Leftist Heap.
 * Ephemeral, destroys inputs to meld.
 *
 * Written by Bryce Summers on 8/3/2015.
 *
 * All allocated nodes contain data, terminals are represented by null pointers.
 *
 * this is a MIN heap implementation.
 */

template <typename T>
class LeftistHeap : public ADT_PriorityQueue<T>
{

    private:

        class Node // Destructor only deletes this one node.
        {
            public:
                Node * left;
                Node * right;
                T elem;
                int rank;

            public:
                // Constructor.
                Node(T elem_in)
                {
                    left = NULL;
                    right = NULL;
                    elem = elem_in;
                    rank = 0;
                }

                // Consumes the nodes in both trees and deletes nodes as appropiate.
                // Only use the returned node in the future, all other nodes may not be stable.
                Node * meld(Node * other)
                {
                    if(other == NULL)
                    {
                        return this;
                    }

                    // 'This' node is not NULL and contains proper data.

                    // Determine Root and not root.
                    Node * root;
                    Node * not_root;

                    if(elem < other -> elem)
                    {
                        root = this;
                        not_root = other;
                    }
                    else
                    {
                        root = other;
                        not_root = this;
                    }

                    // Recursively determine the right child.
                    root -> right = not_root->meld(root->right);

                    if(root -> left == NULL)
                    {
                        root -> left = root -> right;
                        root -> right = NULL;
                        root -> rank = 0;
                        return root;
                    }

                    // Swap the left and right children if necessary to maintain the invariant.
                    if(root->left->rank < root->right->rank)
                    {
                        Node * temp = root -> left;
                        root -> left = root -> right;
                        root -> right = temp;
                    }

                    // Update the root's rank.
                    root -> rank = root -> right -> rank + 1;

                    // Return the root.
                    return root;
                }
        };

    public:

    LeftistHeap()
    {
        root = NULL;
    }

    // Frees the entire tree of heap Nodes.
    virtual ~LeftistHeap<T>()
    {
        freeNode(root);

    }

    void meld(LeftistHeap * other)
    {
        if(isEmpty())
        {
            root = other -> root;
            other->root = NULL;// Makes sure that other does not delete the memory that has been transferred.
            delete other;
            return;
        }

        if(other->isEmpty())
        {
            delete other;
            return;
        }

        // Meld the internal data together.
        root = root -> meld(other -> root);
        other -> root = NULL;
        delete other;

        return;
    }

    void insert(T elem)
    {
        Node * node = new Node(elem);

        if(isEmpty())
        {
            root = node;
            return;
        }

        root = root->meld(node);
    }

    T findMin()
    {
        return root -> elem;
    }

    T extractMin()
    {
        // Output is at the top of the heap.
        T min = root -> elem;

        Node * left  = root -> left;

        // Left always has the longer path, so if it is null, then right will also be null.
        if(left == NULL)
        {
            delete root;
            root = NULL;
            return min;
        }

        Node * right = root -> right;
        delete root;
        root = left -> meld(right);

        return min;
    }

    bool isEmpty()
    {
        return root == NULL;
    }

    private:

    void freeNode(Node * node)
    {
        if(node == NULL)
        {
            return;
        }

        freeNode(node -> left);
        freeNode(node -> right);
        delete node;
    }

    Node * root;

};

#endif // LEFTISTHEAP_H
