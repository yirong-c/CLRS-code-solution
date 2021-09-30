#include "red_black_tree_test.hpp"

#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

typedef RedBlackTreeTest<int, char> Tree;

TEST_CASE("rbt", "[rbt]")
{
    Tree tree;
    std::pair<Tree::Iterator, bool> insert_result, insert_result2;
    insert_result = tree.Insert({10, 'a'});
    REQUIRE(insert_result.second);
    tree.Insert({20, 'a'});
    tree.Insert({30, 'a'});
    tree.Insert({40, 'a'});
    REQUIRE(tree.CheckTreeValid());
    tree.Delete(insert_result.first);
    REQUIRE(tree.CheckTreeValid());
    tree.Insert({50, 'c'});
    insert_result = tree.Insert({80, 'a'});
    REQUIRE(insert_result.second);
    REQUIRE(tree.CheckTreeValid());
    tree.Delete(insert_result.first);
    REQUIRE(tree.CheckTreeValid());
    insert_result = tree.Insert({60, 'a'});
    REQUIRE(insert_result.second);
    insert_result2 = tree.Insert({40, 'd'});
    REQUIRE_FALSE(insert_result2.second);
    REQUIRE(insert_result2.first->first == 40);
    REQUIRE(insert_result2.first->second == 'a');
    insert_result2 = tree.Insert({10, 'd'});
    REQUIRE(insert_result2.second);
    REQUIRE(insert_result2.first->first == 10);
    REQUIRE(insert_result2.first->second == 'd');
    tree.Insert({70, 'a'});
    REQUIRE(tree.CheckTreeValid());
    tree.Delete(insert_result.first);
    REQUIRE(tree.CheckTreeValid());
    insert_result = tree.Insert({90, 'a'});
    REQUIRE(insert_result.second);
    tree.Insert({100, 'a'});
    REQUIRE(tree.CheckTreeValid());
    tree.Delete(insert_result.first);
    REQUIRE(tree.CheckTreeValid());
    
    REQUIRE(tree.At(50) == 'c');
    REQUIRE(tree.Find(10) == insert_result2.first);
    REQUIRE(tree[50] == 'c');

    ++insert_result2.first;
    REQUIRE(tree.Find(20) == insert_result2.first);

    --insert_result2.first;
    REQUIRE(tree.Find(10) == insert_result2.first);

    REQUIRE(tree.Find(200) == tree.End());
    REQUIRE(tree[200] == 0);
    REQUIRE(tree.Find(200) != tree.End());
    REQUIRE(tree.Find(200)->first == 200);
    REQUIRE(tree.Find(200)->second == 0);
    tree[200] = 'e';
    REQUIRE(tree[200] == 'e');
    REQUIRE(tree.Find(200) != tree.End());
    REQUIRE(tree.Find(200)->first == 200);
    REQUIRE(tree.Find(200)->second == 'e');

    REQUIRE(tree.Begin()->first == 10);
    REQUIRE(tree.Begin()->second == 'd');

}


