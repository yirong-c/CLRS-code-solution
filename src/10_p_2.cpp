#include "10_p_2__mergeable_min_heap.h"

int main()
{
    MergeableMinHeapUnsortedList<void*>::ListElementData n1(1);
    MergeableMinHeapUnsortedList<void*>::ListElementData n2(2);
    MergeableMinHeapUnsortedList<void*>::ListElementData n3(3);
    MergeableMinHeapUnsortedList<void*>::ListElementData n4(4);
    MergeableMinHeapUnsortedList<void*>::ListElementData n5(5);
    MergeableMinHeapUnsortedList<void*>::ListElementData n6(6);

    MergeableMinHeapUnsortedList<void*> mergeable_min_heap, 
                                    mergeable_min_heap_another;
    mergeable_min_heap.Insert(&n4);
    mergeable_min_heap.Insert(&n6);
    mergeable_min_heap.Insert(&n3);
    mergeable_min_heap.Insert(&n2);
    mergeable_min_heap_another.Insert(&n5);
    mergeable_min_heap_another.Insert(&n1);

    mergeable_min_heap.Union(mergeable_min_heap_another);

    


    return 0;
}
