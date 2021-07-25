#include "10_p_2__mergeable_min_heap.h"

int main()
{
    MergeableMinHeap<void*>::HeapBinaryTreeNode n1(1);
    MergeableMinHeap<void*>::HeapBinaryTreeNode n2(2);
    MergeableMinHeap<void*>::HeapBinaryTreeNode n3(3);
    MergeableMinHeap<void*>::HeapBinaryTreeNode n4(4);
    MergeableMinHeap<void*>::HeapBinaryTreeNode n5(5);
    MergeableMinHeap<void*>::HeapBinaryTreeNode n6(6);

    MergeableMinHeap<void*> mergeable_min_heap;
    mergeable_min_heap.MinHeapInsert(&n4);
    mergeable_min_heap.MinHeapInsert(&n6);
    mergeable_min_heap.MinHeapInsert(&n5);
    mergeable_min_heap.MinHeapInsert(&n3);
    mergeable_min_heap.MinHeapInsert(&n1);
    mergeable_min_heap.MinHeapInsert(&n2);
 
    MergeableMinHeap<void*>::HeapBinaryTreeNode* extract;
    extract = mergeable_min_heap.ExtractMin();
    extract = mergeable_min_heap.ExtractMin();
    extract = mergeable_min_heap.ExtractMin();
    extract = mergeable_min_heap.ExtractMin();
    extract = mergeable_min_heap.ExtractMin();
    extract = mergeable_min_heap.ExtractMin();
    extract = mergeable_min_heap.ExtractMin();

    return 0;
}


