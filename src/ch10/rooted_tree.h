#ifndef _ROOTED_TREE_H
#define _ROOTED_TREE_H

#include "../stdafx.h"

class RootedTreeNode
{
public:
	int key_;
    RootedTreeNode* left_child_;
    RootedTreeNode* right_sibling_;
    void* temp_;
    void* data_;

    RootedTreeNode(int key)
    {
        key_ = key;
        left_child_ = NULL;
        right_sibling_ = NULL;
        temp_ = NULL;
        data_ = NULL;
    }
};

#endif