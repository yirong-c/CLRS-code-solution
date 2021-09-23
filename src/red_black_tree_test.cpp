#include "red_black_tree.hpp"

template <class Key, class T>
bool CheckRedBlackTree(const RedBlackTree<Key, T>& tree)
{
    
}

int main()
{
    RedBlackTree<int, char> tree;

    // temp build test tree for rotate

    RedBlackTree<int, char>::Node n1({1, 'a'}), n2({2, 'a'}), n3({3, 'a'}), n4({4, 'a'}), n5({5, 'a'}), 
        n6({6, 'a'}), n7({7, 'a'});
    
    tree.root_ = &n4;

    n1.SetRelation(&n2, tree.nil_, tree.nil_);
    n2.SetRelation(&n4, &n1, &n3);
    n3.SetRelation(&n2, tree.nil_, tree.nil_);
    n4.SetRelation(tree.nil_, &n2, &n6);
    n5.SetRelation(&n6, tree.nil_, tree.nil_);
    n6.SetRelation(&n4, &n5, &n7);
    n7.SetRelation(&n6, tree.nil_, tree.nil_);

    tree.LeftRotate(&n4);


    return 0;
}
