#ifndef _RED_BLACK_TREE_HPP
#define _RED_BLACK_TREE_HPP

#include <utility>
#include <iterator>

// ---------- declaration ----------

template <class Key, class T>
class RedBlackTree
{
public:
    typedef std::pair<const Key, T> ValueType;

#ifdef RBT_TESTING
protected:
#else
private:
#endif
    struct Node
    {
        Node* parent;
        Node* left;
        Node* right;
        ValueType value;
        enum { BLACK, RED } color;
        Node();
        Node(const ValueType& value);
    };

public:
    class Iterator : public std::iterator<std::bidirectional_iterator_tag, ValueType>
    {
    public:
        Iterator& operator++();
        Iterator& operator--();
        ValueType& operator*() const;
        ValueType& operator->() const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        Iterator();
    private:
        friend class RedBlackTree<Key, T>;
        Iterator(Node* const node);
        Node* node_;
    };

    RedBlackTree();
    ~RedBlackTree();
    Iterator Insert(const ValueType& value);
    void Delete(Iterator pos);

#ifdef RBT_TESTING
protected:
#else
private:
#endif
    void LeftRotate(Node* subtree_root_node);
    void RightRotate(Node* subtree_root_node);
    void InsertFixup(Node* node);
    void Transplant(Node* old_node, Node* new_node);
    Node* TreeMinimum(Node* sub_tree_root);
    void DeleteFixup(Node* node);
    
    Node* root_;
    Node* nil_;

};

// ---------- definition ----------

template <class Key, class T>
RedBlackTree<Key, T>::Node::Node() {}

template <class Key, class T>
RedBlackTree<Key, T>::Node::Node(const ValueType& value) : value(value) {}

template <class Key, class T>
RedBlackTree<Key, T>::Iterator::Iterator() : node_(nullptr) {}

template <class Key, class T>
RedBlackTree<Key, T>::Iterator::Iterator(Node* const node) : node_(node) {}

template <class Key, class T>
RedBlackTree<Key, T>::RedBlackTree()
{
    nil_ = new Node();
    nil_->color = Node::BLACK;
    //nil_的p, l, r需要设置为nil_吗？
    root_ = nil_;
}

template <class Key, class T>
RedBlackTree<Key, T>::~RedBlackTree()
{
    //TODO: 释放内存
    delete nil_;
}

template <class Key, class T>
void RedBlackTree<Key, T>::LeftRotate(Node* subtree_root_node) 
{
    Node* new_root;
    new_root = subtree_root_node->right;
    subtree_root_node->right = new_root->left;
    if (subtree_root_node->right != nil_)
        subtree_root_node->right->parent = subtree_root_node;
    new_root->parent = subtree_root_node->parent;
    if (subtree_root_node->parent == nil_)
        root_ = new_root;
    else if (subtree_root_node->parent->left == subtree_root_node)
        subtree_root_node->parent->left = new_root;
    else
        subtree_root_node->parent->right = new_root;
    new_root->left = subtree_root_node;
    subtree_root_node->parent = new_root;
}

//13.2-1
template <class Key, class T>
void RedBlackTree<Key, T>::RightRotate(Node* subtree_root_node) 
{
    Node* new_root;
    new_root = subtree_root_node->left;
    subtree_root_node->left = new_root->right;
    if (subtree_root_node->left != nil_)
        subtree_root_node->left->parent = subtree_root_node;
    new_root->parent = subtree_root_node->parent;
    if (subtree_root_node->parent == nil_)
        root_ = new_root;
    else if (subtree_root_node->parent->left == subtree_root_node)
        subtree_root_node->parent->left = new_root;
    else
        subtree_root_node->parent->right = new_root;
    new_root->right = subtree_root_node;
    subtree_root_node->parent = new_root;
}

template <class Key, class T>
typename RedBlackTree<Key, T>::Iterator RedBlackTree<Key, T>::Insert(const ValueType& value)
{
    Node *node, **now_ptr;
    node = new Node(value);
    Iterator it(node);

    node->parent = nil_;
    now_ptr = &root_;
    while (*now_ptr != nil_)
    {
        node->parent = *now_ptr;
        if (node->value.first < (*now_ptr)->value.first)
            now_ptr = &((*now_ptr)->left);
        else
            now_ptr = &((*now_ptr)->right);
    }
    *now_ptr = node;
    node->right = node->left = nil_;
    node->color = Node::RED;
    InsertFixup(node);
    return it;
}

template <class Key, class T>
void RedBlackTree<Key, T>::InsertFixup(Node* node)
{
    Node *uncle, *grandparent;
    void(RedBlackTree<Key, T>::*grandparent_rotate)(Node*);
    while (node->parent->color == Node::RED)
    {
        grandparent = node->parent->parent;
        if (node->parent == grandparent->left)
        {
            uncle = grandparent->right;
            grandparent_rotate = &RedBlackTree<Key, T>::RightRotate;
        }
        else
        {
            uncle = grandparent->left;
            grandparent_rotate = &RedBlackTree<Key, T>::LeftRotate;
        }
        if (uncle->color == Node::RED)
        {
            uncle->color = node->parent->color = Node::BLACK;
            grandparent->color = Node::RED;
            node = grandparent;
        }
        else
        {
            if (node == node->parent->right)
            {
                node = node->parent;
                LeftRotate(node);
                // notice that varible grandparent do not need to update here,
                // since it is still the grandparent of varible node
            }
            node->parent->color = Node::BLACK;
            grandparent->color = Node::RED;
            (this->*grandparent_rotate)(grandparent);
        }
    }
    root_->color = Node::BLACK;
}

template <class Key, class T>
void RedBlackTree<Key, T>::Transplant(Node* old_node, Node* new_node)
{
    if (old_node->parent == nil_)
        root_ = new_node;
    else if (old_node == old_node->parent->left)
        old_node->parent->left = new_node;
    else
        old_node->parent->right = new_node;
    new_node->parent = old_node->parent;
}

template <class Key, class T>
typename RedBlackTree<Key, T>::Node* RedBlackTree<Key, T>::TreeMinimum(Node* sub_tree_root)
{
    while (sub_tree_root->left != nil_)
        sub_tree_root = sub_tree_root->left;
    return sub_tree_root;
}

template <class Key, class T>
void RedBlackTree<Key, T>::Delete(Iterator pos)
{
    Node *old, *replaced, *replaced_replaced;
    bool is_black_deleted;
    old = pos.node_;
    replaced = old;
    is_black_deleted = replaced->color == Node::BLACK;
    if (replaced->left == nil_)
    {
        // do NOT need two "replaced" to store moved node
        replaced_replaced = replaced->right;
        Transplant(replaced, replaced_replaced);
    }
    else if (replaced->right == nil_)
    {
        // do NOT need two "replaced" to store moved node
        replaced_replaced = replaced->left;
        Transplant(replaced, replaced_replaced);
    }
    else
    {
        // DO need two "replaced" to store moved node
        // re-assign varible "replaced" and "is_black_deleted"
        replaced = TreeMinimum(old->right);
        is_black_deleted = replaced->color == Node::BLACK;
        replaced_replaced = replaced->right;
        if (replaced->parent == old)
        {
            // neccessary when "replaced_replaced" is nil_
            replaced_replaced->parent = replaced;
        }
        else
        {
            Transplant(replaced, replaced_replaced);
            replaced->right = old->right;
            replaced->right->parent = replaced;
        }
        Transplant(old, replaced);
        replaced->left = old->left;
        replaced->left->parent = replaced;
        replaced->color = old->color;// this is why "is_black_deleted" need to re-assign in this case
    }
    if (is_black_deleted)
        // In order to maintain property 5,
        // "replaced_replaced" node has extra black (either "doubly black" or "red-and-black", contributes either 2 or 1)
        DeleteFixup(replaced_replaced);
}

template <class Key, class T>
void RedBlackTree<Key, T>::DeleteFixup(Node* node)
{
    Node* sibling;
    while (node != root_ && node->color == Node::BLACK)
    {
        if (node == node->parent->left)
        {
            sibling = node->parent->right;
            if (sibling->color == Node::RED)
            {
                sibling->color = Node::BLACK;
                node->parent->color = Node::RED;
                LeftRotate(node->parent);
                sibling = node->parent->right;
            }
            if (sibling->left->color == Node::BLACK && sibling->right->color == Node::BLACK)
            {
                sibling->color = Node::RED;
                node = node->parent;
            }
            else
            {
                if (sibling->right->color == Node::BLACK)
                {
                    sibling->left->color = Node::BLACK;
                    sibling->color = Node::RED;
                    RightRotate(sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = Node::BLACK;
                sibling->right->color = Node::BLACK;
                LeftRotate(node->parent);
                node = root_;
            }
        }
        else
        {
            sibling = node->parent->left;
            if (sibling->color == Node::RED)
            {
                sibling->color = Node::BLACK;
                node->parent->color = Node::RED;
                RightRotate(node->parent);
                sibling = node->parent->left;
            }
            if (sibling->left->color == Node::BLACK && sibling->right->color == Node::BLACK)
            {
                sibling->color = Node::RED;
                node = node->parent;
            }
            else
            {
                if (sibling->left->color == Node::BLACK)
                {
                    sibling->right->color = Node::BLACK;
                    sibling->color = Node::RED;
                    LeftRotate(sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = Node::BLACK;
                sibling->left->color = Node::BLACK;
                RightRotate(node->parent);
                node = root_;
            }
        }
    }
    node->color = Node::BLACK;
}

#endif
