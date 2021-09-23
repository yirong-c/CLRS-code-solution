#include "red_black_tree_test.hpp"

#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

TEST_CASE("Rotate", "[rotate]")
{
    typedef RedBlackTreeTest<int, char> Tree;
    Tree tree;
    bool result;

    // temp build test tree for rotate

    RedBlackTree<int, char>::Node n1({1, 'a'}), n2({2, 'a'}), n3({3, 'a'}), n4({4, 'a'}), n5({5, 'a'}), 
        n6({6, 'a'}), n7({7, 'a'});
    
    tree.root_ = &n4;
    tree.SetNodeRelation(&n1, &n2, tree.nil_, tree.nil_);
    tree.SetNodeRelation(&n2, &n4, &n1, &n3);
    tree.SetNodeRelation(&n3, &n2, tree.nil_, tree.nil_);
    tree.SetNodeRelation(&n4, tree.nil_, &n2, &n6);
    tree.SetNodeRelation(&n5, &n6, tree.nil_, tree.nil_);
    tree.SetNodeRelation(&n6, &n4, &n5, &n7);
    tree.SetNodeRelation(&n7, &n6, tree.nil_, tree.nil_);

    result = tree.CheckTreeValid();
    std::cout << "BuildTree-CheckTreeValid: " << (result ? "tree" : "false") << std::endl;
    REQUIRE(result);
    REQUIRE(tree.root_ == &n4);

    // 1
    tree.LeftRotate(&n4);

    result = tree.CheckTreeValid();
    std::cout << "LeftRotate-CheckTreeValid: " << (result ? "tree" : "false") << std::endl;
    REQUIRE(result);
    REQUIRE(tree.root_ == &n6);

    // 2
    tree.RightRotate(&n6);

    result = tree.CheckTreeValid();
    std::cout << "RightRotate-CheckTreeValid: " << (result ? "tree" : "false") << std::endl;
    REQUIRE(result);
    REQUIRE(tree.root_ == &n4);

    // 3
    tree.LeftRotate(&n2);

    result = tree.CheckTreeValid();
    std::cout << "LeftRotate-CheckTreeValid: " << (result ? "tree" : "false") << std::endl;
    REQUIRE(result);
    REQUIRE(tree.root_ == &n4);
    
    // 4
    tree.RightRotate(&n6);

    result = tree.CheckTreeValid();
    std::cout << "RightRotate-CheckTreeValid: " << (result ? "tree" : "false") << std::endl;
    REQUIRE(result);
    REQUIRE(tree.root_ == &n4);

}
