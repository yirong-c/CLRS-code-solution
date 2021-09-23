#ifndef _RED_BLACK_TREE_TEST_HPP
#define _RED_BLACK_TREE_TEST_HPP

#define RBT_TESTING

#include "red_black_tree.hpp"

#include <iostream>

template <class Key, class T>
class RedBlackTreeTest : public RedBlackTree<Key, T>
{
public:
    typedef typename RedBlackTree<Key, T>::Node RbtNode;

    void SetNodeRelation(RbtNode* const node, RbtNode* parent, RbtNode* left, RbtNode* right)
    {
        node->parent = parent;
        node->left = left;
        node->right = right;
    }

    RbtNode* TreeMinimum(RbtNode* sub_tree_root)
    {
        while (sub_tree_root->left != this->nil_)
            sub_tree_root = sub_tree_root->left;
        return sub_tree_root;
    }

    RbtNode* TreeSuccessor(RbtNode* node)
    {
        RbtNode* parent;
        if (node->right != this->nil_)
            return TreeMinimum(node->right);
        parent = node->parent;
        while (parent != this->nil_ && parent->right == node)
        {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }

    bool CheckNodeValid(const RbtNode* node)
    {
        // check parent
        if (node->parent != this->nil_ && node->parent->left != node && node->parent->right != node)
        {
            return false;
        }
        if (node->right != this->nil_ && node->right->parent != node)
        {
            return false;
        }
        if (node->left != this->nil_ && node->left->parent != node)
        {
            return false;
        }
        return true;
    }

    bool CheckTreeValid()
    {
        RbtNode* now;
        const Key* last_key_ptr;
        last_key_ptr = nullptr;
        now = TreeMinimum(this->root_);
        while (now != this->nil_)
        {
            if (last_key_ptr && *last_key_ptr > now->value.first)
                return false;
            if (CheckNodeValid(now) == false)
                return false;
            last_key_ptr = &now->value.first;
            now = TreeSuccessor(now);
        }
        return true;
    }

};

#endif
