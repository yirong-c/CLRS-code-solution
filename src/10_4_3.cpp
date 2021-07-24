#include "binary_tree.h"
#include "stack_queue.h"

/*
10.4.3
(DO use temp_ of BinaryTreeNode object)
*/
void PrintBinaryTreeNonrecursive(BinaryTreeNode* binary_tree)
{
    Stack<BinaryTreeNode*> stack(30);
    int traversing_left_flag;
    int traversing_right_flag;
    while (true)
    {
        if (binary_tree->temp_ == NULL)
        {
            printf("%i\n", binary_tree->key_);
            binary_tree->temp_ = &traversing_left_flag;
            if(binary_tree->left_ != NULL)
            {
                stack.PushCheck(binary_tree);
                binary_tree = binary_tree->left_;
            }
        }
        else if (binary_tree->temp_ == &traversing_left_flag)
        {
            binary_tree->temp_ = &traversing_right_flag;
            if(binary_tree->right_ != NULL)
            {
                stack.PushCheck(binary_tree);
                binary_tree = binary_tree->right_;
            }
        }
        else if (binary_tree->temp_ == &traversing_right_flag)
        {
            if (stack.StackEmpty())
                break;
            binary_tree = stack.PopCheck();
        }
    }
}

/*
10.4.3
better one
(do NOT use temp_ of BinaryTreeNode object)
*/
void PrintBinaryTreeNonrecursiveAnother(BinaryTreeNode* binary_tree)
{
    Stack<BinaryTreeNode*> stack(30);
    stack.Push(binary_tree);
    while (true)
    {
        while (binary_tree->left_ != NULL)
        {
            binary_tree = binary_tree->left_;
            stack.PushCheck(binary_tree);
        }
        binary_tree = stack.Pop();
        printf("%i\n", binary_tree->key_);
        while (binary_tree->right_ == NULL)
        {
            if (stack.StackEmpty())
                return;
            binary_tree = stack.Pop();
            printf("%i\n", binary_tree->key_);

        }
        binary_tree = binary_tree->right_;
        stack.PushCheck(binary_tree);
    }
}

int main()
{
    BinaryTreeNode b1(18);
    BinaryTreeNode b2(12);
    BinaryTreeNode b3(16);
    BinaryTreeNode b4(7);
    BinaryTreeNode b5(4);
    BinaryTreeNode b6(2);
    BinaryTreeNode b7(21);
    BinaryTreeNode b8(5);
    //b1.left_ = &b2;
    b1.right_ = &b3;
    b2.left_ = &b4;
    b2.right_ = &b5;
    b3.left_ = &b6;
    b3.right_ = &b7;
    b5.left_ = &b8;
    b7.right_ = &b2;//test
    PrintBinaryTreeNonrecursiveAnother(&b1);
    return 0;
}
