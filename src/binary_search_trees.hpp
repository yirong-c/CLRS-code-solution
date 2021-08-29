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
