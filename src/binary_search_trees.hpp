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
