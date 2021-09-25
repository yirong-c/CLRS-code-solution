#include "red_black_tree_test.hpp"

#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

typedef RedBlackTreeTest<int, char> Tree;

TEST_CASE("Insert", "[insert]")
{
    Tree tree;
    tree.Insert({10, 'a'});
}


