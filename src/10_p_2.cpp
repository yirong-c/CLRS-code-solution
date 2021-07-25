#include "10_p_2__mergeable_min_heap.h"

int main()
{
    MergeableMinHeapSortedList<void*>::ListElementData n1(1);
    MergeableMinHeapSortedList<void*>::ListElementData n2(2);
    MergeableMinHeapSortedList<void*>::ListElementData n3(3);
    MergeableMinHeapSortedList<void*>::ListElementData n4(4);
    MergeableMinHeapSortedList<void*>::ListElementData n5(5);
    MergeableMinHeapSortedList<void*>::ListElementData n6(6);

    MergeableMinHeapSortedList<void*> mergeable_min_heap, 
                                    mergeable_min_heap_another;
    mergeable_min_heap.Insert(&n4);
    mergeable_min_heap.Insert(&n6);
    mergeable_min_heap.Insert(&n3);
    mergeable_min_heap_another.Insert(&n2);
    mergeable_min_heap_another.Insert(&n5);
    mergeable_min_heap_another.Insert(&n1);

    mergeable_min_heap_another.Union(mergeable_min_heap);

    return 0;
}
