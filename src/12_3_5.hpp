#include <iostream>

template <typename T1, typename T2>
struct BinaryTreeNode
{
    BinaryTreeNode<T1, T2>* succ;
    BinaryTreeNode<T1, T2>* left;
    BinaryTreeNode<T1, T2>* right;
    T1 data;
    T2 key;

    BinaryTreeNode(T2 key)
    {
        this->key = key;
        this->succ = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    void SetRelation(BinaryTreeNode<T1, T2>* succ,
        BinaryTreeNode<T1, T2>* left, 
        BinaryTreeNode<T1, T2>* right)
    {
        this->succ = succ;
        this->left = left;
        this->right = right;
    }
};

//12.3-5
template <typename T1, typename T2>
class BinarySearchTree
{
public:
    BinaryTreeNode<T1, T2>* root_node_;

    //O(h)
    //root_node cannot be nullptr
    BinaryTreeNode<T1, T2>* TreeMinimum(BinaryTreeNode<T1, T2>* root_node)
    {
        while (root_node->left)
            root_node = root_node->left;
        return root_node;
    }

    //O(h)
    //root_node cannot be nullptr
    BinaryTreeNode<T1, T2>* TreeMaximum(BinaryTreeNode<T1, T2>* root_node)
    {
        while (root_node->right)
            root_node = root_node->right;
        return root_node;
    }

    //O(h)
    //h: height (h >= lgn)
    //space complexity: O(h)
    BinaryTreeNode<T1, T2>* TreeSearchRecursive(BinaryTreeNode<T1, T2>* root_node, T2 key)
    {
        if (root_node == nullptr || root_node->key == key)
            return root_node;
        if (key < root_node->key)
            return TreeSearchRecursive(root_node->left, key);
        else
            return TreeSearchRecursive(root_node->right, key);
    }

    //O(h)
    //h: height (h >= lgn)
    //space complexity: O(h)
    BinaryTreeNode<T1, T2>* TreeSearchRecursive(T2 key)
    {
        return TreeSearchRecursive(root_node_, key);
    }

    //O(h)
    void TreeInsert(BinaryTreeNode<T1, T2>* to_insert)
    {
        BinaryTreeNode<T1, T2> **now_ptr, *pred;
        if (root_node_ == nullptr)
        {
            root_node_ = to_insert;
        }
        else
        {
            now_ptr = &root_node_;
            pred = nullptr;
            while (*now_ptr)
            {
                if (to_insert->key < (*now_ptr)->key)
                {
                    to_insert->succ = *now_ptr;
                    now_ptr = &((*now_ptr)->left);
                }
                else
                {
                    pred = *now_ptr;
                    now_ptr = &((*now_ptr)->right);
                }
            }
            *now_ptr = to_insert;
            if (pred)
                pred->succ = to_insert;
        }
    }

    //O(n)
    void GetParentAndPred(const BinaryTreeNode<T1, T2>* node, 
        BinaryTreeNode<T1, T2>** parent_ptr, BinaryTreeNode<T1, T2>** pred_ptr)
    {
        BinaryTreeNode<T1, T2>* now;
        now = root_node_;
        *pred_ptr = *parent_ptr = nullptr;
        while (now != node)
        {
            *parent_ptr = now;
            if (node->key < now->key)
            {
                now = now->left;
            }
            else
            {
                *pred_ptr = now;
                now = now->right;
            }
        }
        if (node->left)
            *pred_ptr = TreeMaximum(node->left);
    }

    //replace subtree rooted at node u with subtree rooted at node v
    //DO remove u from u_pred->succ
    //u cannot be nullptr
    //O(n)
    void TransplantRemoveU(BinaryTreeNode<T1, T2>* u, BinaryTreeNode<T1, T2>* v)
    {
        BinaryTreeNode<T1, T2> *u_parent, *u_pred;
        GetParentAndPred(u, &u_parent, &u_pred);
        if (u_parent == nullptr)
            root_node_ = v;
        else if (u == u_parent->left)
            u_parent->left = v;
        else
            u_parent->right = v;
        if (u_pred != nullptr)
            u_pred->succ = u->succ;
    }

    //replace subtree rooted at node u with subtree rooted at node v
    //do NOT remove u from u_pred->succ
    //u cannot be nullptr
    //O(n)
    void TransplantNotRemoveU(BinaryTreeNode<T1, T2>* u, BinaryTreeNode<T1, T2>* v)
    {
        BinaryTreeNode<T1, T2> *u_parent, *u_pred;
        GetParentAndPred(u, &u_parent, &u_pred);
        if (u_parent == nullptr)
            root_node_ = v;
        else if (u == u_parent->left)
            u_parent->left = v;
        else
            u_parent->right = v;
    }

    //O(h)
    //to_delete cannot be nullptr
    void TreeDelete(BinaryTreeNode<T1, T2>* to_delete)
    {
        BinaryTreeNode<T1, T2>* will_replace;
        if (to_delete->left == nullptr)
        {
            TransplantRemoveU(to_delete, to_delete->right);
        }
        else if (to_delete->right == nullptr)
        {
            TransplantRemoveU(to_delete, to_delete->left);
        }
        else
        {
            will_replace = to_delete->succ;
            if (will_replace != to_delete->right)
            {
                TransplantNotRemoveU(will_replace, will_replace->right);
                will_replace->right = to_delete->right;
            }
            TransplantRemoveU(to_delete, will_replace);
            will_replace->left = to_delete->left;
        }
    }

    //O(n)
    void InorderTreeWalkRecursive(BinaryTreeNode<T1, T2>* x)
    {
        if (x != nullptr)
        {
            InorderTreeWalkRecursive(x->left);
            std::cout << x->key << std::endl;
            InorderTreeWalkRecursive(x->right);
        }
    }

    //O(n)
    void InorderTreeWalkRecursive()
    {
        InorderTreeWalkRecursive(root_node_);
    }

};
