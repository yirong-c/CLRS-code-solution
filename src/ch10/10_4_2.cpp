#include "binary_tree.h"

/*
10.4.2
*/
void PrintBinaryTreeRecursive(BinaryTreeNode* binary_tree_root)
{
    if (binary_tree_root == NULL)
    {
        return;
    }
    printf("%i\n", binary_tree_root->key_);
    PrintBinaryTreeRecursive(binary_tree_root->left_);
    PrintBinaryTreeRecursive(binary_tree_root->right_);  
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
    b1.left_ = &b2;
    b1.right_ = &b3;
    b2.left_ = &b4;
    b2.right_ = &b5;
    b3.left_ = &b6;
    b3.right_ = &b7;
    b5.left_ = &b8;
    PrintBinaryTreeRecursive(&b1);
    return 0;
}
