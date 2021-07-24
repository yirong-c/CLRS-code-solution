#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "stdafx.h"

class BinaryTreeNode
{
public:
	int key_;
    BinaryTreeNode* left_ = NULL;
    BinaryTreeNode* right_ = NULL;
    void* data_;

    BinaryTreeNode(int key)
    {
        key_ = key;
        left_;
    }
};

#endif