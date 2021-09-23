#include <utility>
#include <iterator>

template <class Key, class T>
class RedBlackTree
{
public:
    typedef std::pair<const Key, T> ValueType;

//private:
    struct Node
    {
        Node* parent;
        Node* left;
        Node* right;
        ValueType value;
        enum { BLACK, RED } color;

        Node() {}

        Node(const ValueType& value) : value(value) {}

        void SetRelation(Node* parent, Node* left, Node* right)
        {
            this->parent = parent;
            this->left = left;
            this->right = right;
        }
    };

public:
    RedBlackTree();
    ~RedBlackTree();

//private:
    void LeftRotate(Node* subtree_root_node);

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

// ---------- Iterator ----------
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
