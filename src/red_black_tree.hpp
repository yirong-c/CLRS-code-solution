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

#ifndef RBT_TESTING
private:
#endif
    struct Node
    {
        Node* parent;
        Node* left;
        Node* right;
        ValueType value;
        enum { BLACK, RED } color;

        Node() {}

        Node(const ValueType& value);
    };

public:
    RedBlackTree();
    ~RedBlackTree();

#ifndef RBT_TESTING
private:
#endif
    void LeftRotate(Node* subtree_root_node);
    void RightRotate(Node* subtree_root_node);

    Node* root_;
    Node* nil_;

public:
    class Iterator : public std::iterator<std::bidirectional_iterator_tag, ValueType>
    {
    public:
        Iterator(ValueType* iter_init);
        Iterator& operator++();
        ValueType& operator*() const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    private:
        ValueType* iter_;
    };
};

// ---------- definition ----------

template <class Key, class T>
RedBlackTree<Key, T>::Node::Node(const ValueType& value) : value(value) {}

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

// template <class Key, class T>
// RedBlackTree<Key, T>::Iterator::Iterator(ValueType* iter_init) : iter_(iter_init) {}

// template <class Key, class T>
// RedBlackTree<Key, T>::Iterator& RedBlackTree<Key, T>::Iterator::operator++() {}

// template <class Key, class T>
// typename RedBlackTree<Key, T>::ValueType& RedBlackTree<Key, T>::Iterator::operator*() const {}

// template <class Key, class T>
// bool RedBlackTree<Key, T>::Iterator::operator==(const Iterator& other) const {}

// template <class Key, class T>
// bool RedBlackTree<Key, T>::Iterator::operator!=(const Iterator& other) const {}

#endif
