#include "k_way_merge__6_5_9.h"

/*
O(lgn)
return the index (larger one) of last exchange element
*/
int MinHeapifyReturnLastIndex(vector<int>& A, int heap_size, int i)
{
    int l, r, smallest;
    l = BinaryTreeLeft(i);
    r = BinaryTreeRight(i);
    if (l < heap_size && A.at(l) < A.at(i))
        smallest = l;
    else
        smallest = i;
    if (r < heap_size && A.at(r) < A.at(smallest))
        smallest = r;
    if (smallest != i)
    {
        SwapInt(A.at(i), A.at(smallest));
        return MinHeapifyReturnLastIndex(A, heap_size, smallest);
    }
    else
    {
        return smallest;
    }
}

/*
O(lgn)
return: extracted min value
parameter:
 	A: min heap
 	fill_value: value which is going to be filled at the space (in para)
 	filled_value_index: space index (out para)
*/
int HeapExtractMinAndFillSpaceBySpecificValueGetIndex(vector<int>& A,
    int fill_value, int& filled_value_index)
{
    int min_val;
    if (A.size() < 1)
        throw "heap underflow";
    int& min = A.at(0);
    min_val = min;
    min = fill_value;
    filled_value_index = MinHeapifyReturnLastIndex(A, A.size(), 0);
    return min_val;
}

struct VectorIntIterator
{
    vector<int>::iterator iterator;
    vector<int>::iterator iterator_end;
};

/*
O(nlgk) 6.5-9
k-way merge: merge k sorted arrays (vector) into one sorted array (vector)
n is the total number of elements in all the input containers
*/
void KWayMergeArraysSort(vector< vector<int> >& sorted_arrays_input, 
    vector<int>& merged_array_output)
{
    int lists_size, i, heap_nodes_num, filled_value_index, extracted_min_value, 
        list_num;
    VectorIntIterator iterator;
    vector<VectorIntIterator> list_iterators;
    lists_size = sorted_arrays_input.size();//k
    heap_nodes_num = lists_size - 1;
    vector<int> min_heap(heap_nodes_num, INT_MIN);
    for (i = 0; i < lists_size; ++i)
    {
        iterator.iterator = sorted_arrays_input.at(i).begin();
        iterator.iterator_end = sorted_arrays_input.at(i).end();
        min_heap.push_back(*iterator.iterator);
        list_iterators.push_back(iterator);
    }
    while (1)
    {
        extracted_min_value = HeapExtractMinAndFillSpaceBySpecificValueGetIndex
        (min_heap, INT_MAX, filled_value_index);
        list_num = filled_value_index - heap_nodes_num;
        if (list_num >= 0)
        {
            if (++list_iterators[list_num].iterator !=
                list_iterators[list_num].iterator_end)
            {
                min_heap[filled_value_index] = *(list_iterators[list_num].iterator);
            }
        }
        if (extracted_min_value == INT_MAX)
        {
            break;
        }
        if (extracted_min_value != INT_MIN)
        {
            merged_array_output.push_back(extracted_min_value);
        }
    }
}

int main_6_5_9()
{
    vector<vector<int>> sorted_arrays_input;
    vector<int> arr;
    arr = { 1,3,5,7,9 };
    sorted_arrays_input.push_back(arr);
    arr = { 2,4,6,8,10 };
    sorted_arrays_input.push_back(arr);
    arr = { 1,2,5,6,8,9 };
    sorted_arrays_input.push_back(arr);
    arr = { 5,6,7,8,8,9,11 };
    sorted_arrays_input.push_back(arr);
    arr = { 1,2,4,6,7,8,10 };
    sorted_arrays_input.push_back(arr);
    arr.clear();
    KWayMergeArraysSort(sorted_arrays_input, arr);

    return 0;
}
