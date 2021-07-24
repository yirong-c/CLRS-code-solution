#include "binary_tree.h"

void PrintBinaryTreeRecursive(BinaryTree* binary_tree)
{
    if (binary_tree == NULL)
    {
        return;
    }
    printf("%i\n", binary_tree->key_);
    PrintBinaryTreeRecursive(binary_tree->left_);
    PrintBinaryTreeRecursive(binary_tree->right_);  
}

int main()
{
    BinaryTree b1(18);
    BinaryTree b2(12);
    BinaryTree b3(16);
    BinaryTree b4(7);
    BinaryTree b5(4);
    BinaryTree b6(2);
    BinaryTree b7(21);
    BinaryTree b8(5);
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
