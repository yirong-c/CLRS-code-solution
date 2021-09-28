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
    private:
        friend class RedBlackTree<Key, T>;
        Iterator(Node* const node);
        Node* const node_;
    };

    RedBlackTree();
    ~RedBlackTree();
    Iterator Insert(const ValueType& value);
    
#ifdef RBT_TESTING
protected:
#else
private:
#endif
    void LeftRotate(Node* subtree_root_node);
    void RightRotate(Node* subtree_root_node);
    void InsertFixup(Node* node);
    void Transplant(Node* old_node, Node* new_node);
    
    Node* root_;
    Node* nil_;

};

// ---------- definition ----------

template <class Key, class T>
RedBlackTree<Key, T>::Node::Node() {}

template <class Key, class T>
RedBlackTree<Key, T>::Node::Node(const ValueType& value) : value(value) {}

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



#endif
