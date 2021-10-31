#ifndef BINARYTREE_H
#define BINARYTREE_H

struct Node
{
    int value;
    int index;
    Node *parent = nullptr;
    Node *child1 = nullptr;
    Node *child2 = nullptr;
};

#endif
