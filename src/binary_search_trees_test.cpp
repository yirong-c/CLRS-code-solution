#include "binary_search_trees.hpp"

int main()
{
    //build test tree
    typedef BinaryTreeNode<int, int> TestNode;
    typedef TestNode* TestNodePtr;
    TestNode n1(1), n2(2), n3(3), n4(4), n5(5), n6(6), n7(7), 
        n8(8), n9(9), n10(10), n11(11), n12(12), n13(13), 
        n14(14), n15(15), n16(16);
    n1.SetRelation(&n5, nullptr, &n3);
    n2.SetRelation(&n3, nullptr, nullptr);
    n3.SetRelation(&n1, &n2, &n4);
    n4.SetRelation(&n3, nullptr, nullptr);
    n5.SetRelation(&n10, &n1, &n6);
    n6.SetRelation(&n5, nullptr, &n9);
    n7.SetRelation(&n8, nullptr, nullptr);
    n8.SetRelation(&n9, &n7, nullptr);
    n9.SetRelation(&n6, &n8, nullptr);
    n10.SetRelation(nullptr, &n5, &n14);
    n11.SetRelation(&n13, nullptr, &n12);
    n12.SetRelation(&n11, nullptr, nullptr);
    n13.SetRelation(&n14, &n11, nullptr);
    n14.SetRelation(&n10, &n13, &n15);
    n15.SetRelation(&n14, nullptr, &n16);
    n16.SetRelation(&n15, nullptr, nullptr);

    //test functions
    InorderTreeWalkNonRecursive(&n10);
    std::cout << "---" << std::endl;
    InorderTreeWalkNonRecursiveNonStack(&n10);

    std::cout << "---" << std::endl;

    PreorderTreeWalk(&n10);
    std::cout << "---" << std::endl;
    PostorderTreeWalk(&n10);

    return 0;
}
