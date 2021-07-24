#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "stdafx.h"

class BinaryTree
{
public:
	int key_;
    BinaryTree* left_ = NULL;
    BinaryTree* right_ = NULL;

    BinaryTree(int key)
    {
        key_ = key;
        left_;
    }
};

#endif