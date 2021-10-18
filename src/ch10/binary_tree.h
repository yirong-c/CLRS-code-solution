#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "../stdafx.h"

class BinaryTreeNode
{
public:
	int key_;
    BinaryTreeNode* left_;
    BinaryTreeNode* right_;
    void* temp_;
    void* data_;

    BinaryTreeNode(int key)
    {
        key_ = key;
        left_ = NULL;
        right_ = NULL;
        temp_ = NULL;
        data_ = NULL;
    }
};

#endif