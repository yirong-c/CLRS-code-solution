#include <iostream>
#include <stack>

template <typename T1, typename T2>
struct BinaryTreeNode
{
    BinaryTreeNode<T1, T2>* parent;
    BinaryTreeNode<T1, T2>* left;
    BinaryTreeNode<T1, T2>* right;
    T1 data;
    T2 key;

    BinaryTreeNode(T2 key)
    {
        this->key = key;
    }

    void SetRelation(BinaryTreeNode<T1, T2>* parent,
        BinaryTreeNode<T1, T2>* left, 
        BinaryTreeNode<T1, T2>* right)
    {
        this->parent = parent;
        this->left = left;
        this->right = right;
    }
};

//O(n)
template <typename T1, typename T2>
void InorderTreeWalk(BinaryTreeNode<T1, T2>* x)
{
    if (x != nullptr)
    {
        InorderTreeWalk(x->left);
        std::cout << x->key << std::endl;
        InorderTreeWalk(x->right);
    }
}

//12.1-3
//O(n)
//space complexity: O(n)
template <typename T1, typename T2>
void InorderTreeWalkNonRecursive(BinaryTreeNode<T1, T2>* x)
{
    std::stack<BinaryTreeNode<T1, T2>*> stack;
    while (true)
    {
        while (x != nullptr)
        {
            stack.push(x);
            x = x->left;
        }
        if (stack.empty())
        {
            break;
        }
        x = stack.top();
        std::cout << x->key << std::endl;
        stack.pop();
        x = x->right;
    }
}

//12.1-3
//O(n)
//space complexity: O(1)
template <typename T1, typename T2>
void InorderTreeWalkNonRecursiveNonStack(BinaryTreeNode<T1, T2>* x)
{
    BinaryTreeNode<T1, T2>* last;
    goto Start;
    while (x->parent)
    {
        last = x;
        x = x->parent;
        if (last == x->left)
        {
            std::cout << x->key << std::endl;
            while (x->right)
            {
                x = x->right;
                Start:
                while (x->left)
                {
                    x = x->left;
                }
                std::cout << x->key << std::endl;
            }
        }
    }
}

//12.1-4
//O(n)
template <typename T1, typename T2>
void PreorderTreeWalk(BinaryTreeNode<T1, T2>* x)
{
    if (x != nullptr)
    {
        std::cout << x->key << std::endl;
        PreorderTreeWalk(x->left);
        PreorderTreeWalk(x->right);
    }
}

//12.1-4
//O(n)
template <typename T1, typename T2>
void PostorderTreeWalk(BinaryTreeNode<T1, T2>* x)
{
    if (x != nullptr)
    {
        PostorderTreeWalk(x->left);
        PostorderTreeWalk(x->right);
        std::cout << x->key << std::endl;
    }
}

//O(h)
//h: height (h >= lgn)
//space complexity: O(h)
template <typename T1, typename T2>
BinaryTreeNode<T1, T2>* TreeSearch(BinaryTreeNode<T1, T2>* root_node, T2 key)
{
    if (root_node == nullptr || root_node->key == key)
        return root_node;
    if (key < root_node->key)
        return TreeSearch(root_node->left, key);
    else
        return TreeSearch(root_node->right, key);
}

//O(h)
//h: height (h >= lgn)
//space complexity: O(1)
template <typename T1, typename T2>
BinaryTreeNode<T1, T2>* IterativeTreeSearch(BinaryTreeNode<T1, T2>* root_node, T2 key)
{
    while (root_node != nullptr && root_node->key != key)
    {
        if (key < root_node->key)
            root_node = root_node->left;
        else
            root_node = root_node->right;
    }    
    return root_node;
}

//O(h)
//root_node cannot be nullptr
template <typename T1, typename T2>
BinaryTreeNode<T1, T2>* TreeMinimum(BinaryTreeNode<T1, T2>* root_node)
{
    while (root_node->left)
        root_node = root_node->left;
    return root_node;
}

//O(h)
//root_node cannot be nullptr
template <typename T1, typename T2>
BinaryTreeNode<T1, T2>* TreeMaximum(BinaryTreeNode<T1, T2>* root_node)
{
    while (root_node->right)
        root_node = root_node->right;
    return root_node;
}

//O(h)
//node cannot be nullptr
template <typename T1, typename T2>
BinaryTreeNode<T1, T2>* TreeSuccessor(BinaryTreeNode<T1, T2>* node)
{
    BinaryTreeNode<T1, T2>* parent;
    if (node->right != nullptr)
        return TreeMinimum(node->right);
    parent = node->parent;
    while (parent != nullptr && parent->right == node)
    {
        node = parent;
        parent = node->parent;
    }
    return parent;
}

//12.2-2
//O(h)
//root_node cannot be nullptr
template <typename T1, typename T2>
BinaryTreeNode<T1, T2>* TreeMinimumRecursive(BinaryTreeNode<T1, T2>* root_node)
{
    if (root_node->left)
        return TreeMinimumRecursive(root_node->left);
    else
        return root_node;
}

//12.2-2
//O(h)
//root_node cannot be nullptr
template <typename T1, typename T2>
BinaryTreeNode<T1, T2>* TreeMaximumRecursive(BinaryTreeNode<T1, T2>* root_node)
{
    if (root_node->right)
        return TreeMaximumRecursive(root_node->right);
    else
        return root_node;
}
