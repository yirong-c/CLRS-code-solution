#include "red_black_tree_test.hpp"

#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

typedef RedBlackTreeTest<int, char> Tree;

TEST_CASE("Insert", "[insert]")
{
    Tree tree;
    Tree::Iterator it;
    it = tree.Insert({10, 'a'});
    tree.Insert({20, 'a'});
    tree.Insert({30, 'a'});
    tree.Insert({40, 'a'});
    REQUIRE(tree.CheckTreeValid());
    tree.Delete(it);
    REQUIRE(tree.CheckTreeValid());
    tree.Insert({50, 'a'});
    it = tree.Insert({80, 'a'});
    REQUIRE(tree.CheckTreeValid());
    tree.Delete(it);
    REQUIRE(tree.CheckTreeValid());
    it = tree.Insert({60, 'a'});
    tree.Insert({70, 'a'});
    REQUIRE(tree.CheckTreeValid());
    tree.Delete(it);
    REQUIRE(tree.CheckTreeValid());
    it = tree.Insert({90, 'a'});
    tree.Insert({100, 'a'});
    REQUIRE(tree.CheckTreeValid());
    tree.Delete(it);
    REQUIRE(tree.CheckTreeValid());

}


