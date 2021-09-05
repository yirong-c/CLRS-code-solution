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
    n7.SetRelation(nullptr, nullptr, nullptr);
    n8.SetRelation(&n9, /*&n7*/nullptr, nullptr);
    n9.SetRelation(&n6, &n8, nullptr);
    n10.SetRelation(nullptr, &n5, &n12);
    n11.SetRelation(&n12, nullptr, nullptr);
    n12.SetRelation(&n10, &n11, &n15);
    n13.SetRelation(&n15, nullptr, &n14);
    n14.SetRelation(&n13, nullptr, nullptr);
    n15.SetRelation(&n12, &n13, &n16);
    n16.SetRelation(&n15, nullptr, nullptr);

    //test functions
    InorderTreeWalkNonRecursive(&n10);
    std::cout << "---" << std::endl;
    InorderTreeWalkNonRecursiveNonStack(&n10);

    std::cout << "---" << std::endl;

    PreorderTreeWalk(&n10);
    std::cout << "---" << std::endl;
    PostorderTreeWalk(&n10);

    std::cout << "---" << std::endl;

    std::cout << "TreeMinimum(&n10)->key: " << TreeMinimum(&n10)->key << std::endl;
    std::cout << "TreeMaximum(&n10)->key: " << TreeMaximum(&n10)->key << std::endl;

    std::cout << "TreeSuccessor(&n4)->key: " << TreeSuccessor(&n4)->key << std::endl;
    std::cout << "TreeSuccessor(&n10)->key: " << TreeSuccessor(&n10)->key << std::endl;
    std::cout << "TreeSuccessor(&n11)->key: " << TreeSuccessor(&n11)->key << std::endl;
    std::cout << "TreeSuccessor(&n16) == nullptr: " << (TreeSuccessor(&n16) == nullptr) << std::endl;

    std::cout << "TreeMinimumRecursive(&n10)->key: " << TreeMinimumRecursive(&n10)->key << std::endl;
    std::cout << "TreeMaximumRecursive(&n10)->key: " << TreeMaximumRecursive(&n10)->key << std::endl;

    std::cout << "TreePredecessor(&n1) == nullptr: " << (TreePredecessor(&n1) == nullptr) << std::endl;
    std::cout << "TreePredecessor(&n2)->key: " << TreePredecessor(&n2)->key << std::endl;
    std::cout << "TreePredecessor(&n4)->key: " << TreePredecessor(&n4)->key << std::endl;
    //std::cout << "TreePredecessor(&n7)->key: " << TreePredecessor(&n7)->key << std::endl;
    std::cout << "TreePredecessor(&n10)->key: " << TreePredecessor(&n10)->key << std::endl;
    std::cout << "TreePredecessor(&n11)->key: " << TreePredecessor(&n11)->key << std::endl;
    std::cout << "TreePredecessor(&n16)->key: " << TreePredecessor(&n16)->key << std::endl;

    TreeInsert(&n10, &n7);

    TreeDelete(&n12);
    TreeDelete(&n3);
    //TreeDelete(&n10);
    InorderTreeWalkNonRecursiveNonStack(&n10);
    return 0;
}
