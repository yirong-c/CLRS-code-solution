#include "rooted_tree.h"

/*
10.4.4
*/
void PrintRootedTree(RootedTreeNode* rooted_tree)
{
    printf("%i\n", rooted_tree->key_);
    if (rooted_tree->left_child_ != NULL)
    {
        rooted_tree = rooted_tree->left_child_;
        PrintRootedTree(rooted_tree);
        while (rooted_tree->right_sibling_ != NULL)
        {
            rooted_tree = rooted_tree->right_sibling_;
            PrintRootedTree(rooted_tree);
        }
    }
}

int main()
{
    RootedTreeNode n1(1);
    RootedTreeNode n2(2);
    RootedTreeNode n3(3);
    RootedTreeNode n4(4);
    RootedTreeNode n5(5);
    RootedTreeNode n6(6);
    RootedTreeNode n7(7);
    RootedTreeNode n8(8);
    RootedTreeNode n9(9);
    RootedTreeNode n10(10);
    RootedTreeNode n11(11);
    RootedTreeNode n12(12);
    RootedTreeNode n13(13);
    RootedTreeNode n14(14);
    n1.left_child_ = &n2;
    n2.left_child_ = &n5;
    n2.right_sibling_ = &n3;
    n3.left_child_ = &n7;
    n3.right_sibling_ = &n4;
    n4.left_child_ = &n11;
    n5.right_sibling_ = &n6;
    n6.left_child_ = &n12;
    n7.right_sibling_ = &n8;
    n8.right_sibling_ = &n9;
    n9.left_child_ = &n13;
    n9.right_sibling_ = &n10;
    n13.right_sibling_ = &n14;
    PrintRootedTree(&n1);
    return 0;
}
