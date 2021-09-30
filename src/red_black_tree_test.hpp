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

    RbtNode* TreeSuccessor(RbtNode* node)
    {
        RbtNode* parent;
        if (node->right != this->nil_)
            return this->TreeMinimum(node->right);
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

    // return number of black nodes on the simple path from the subtree_root to descendant leaves
    // return -1 means the RBT is invalid
    int CheckRBSubtreeValid(const RbtNode* subtree_root)
    {
        int black_node_num, left_black_node_num, right_black_node_num;
        if (subtree_root == this->nil_)
            return 1;
        if (subtree_root->color == RbtNode::RED && (subtree_root->left->color != RbtNode::BLACK || subtree_root->right->color != RbtNode::BLACK))
            return -1;
        left_black_node_num = CheckRBSubtreeValid(subtree_root->left);
        right_black_node_num = CheckRBSubtreeValid(subtree_root->right);
        if (left_black_node_num == -1 || right_black_node_num == -1 || left_black_node_num != right_black_node_num)
            return -1;
        return left_black_node_num + ((subtree_root->color == RbtNode::BLACK) ? 1 : 0);
    }

    bool CheckTreeValid()
    {
        RbtNode* now;
        const Key* last_key_ptr;
        last_key_ptr = nullptr;
        now = this->TreeMinimum(this->root_);
        if (this->root_->color != RbtNode::BLACK || this->nil_->color != RbtNode::BLACK)
            return false;
        while (now != this->nil_)
        {
            //test node relationship
            if (CheckNodeValid(now) == false)
                return false;
            //test BST
            if (last_key_ptr && *last_key_ptr > now->value.first)
                return false;
            last_key_ptr = &now->value.first;
            now = TreeSuccessor(now);
        }
        if (CheckRBSubtreeValid(this->root_) == -1)
            return false;
        return true;
    }

};

#endif
