#include "stdafx.h"

//max heap-----------------------------------------------
//O(lgn)
void MaxHeapify(vector<int>& A, int heap_size, int i)
{
	int l, r, largest;
	l = BinaryTreeLeft(i);
	r = BinaryTreeRight(i);
	if (l < heap_size && A.at(l) > A.at(i))
		largest = l;
	else
		largest = i;
	if (r < heap_size && A.at(r) > A.at(largest))
		largest = r;
	if (largest != i)
	{
		SwapInt(A.at(i), A.at(largest));
		MaxHeapify(A, heap_size, largest);
	}
}

//O(lgn) 6.2-5
void MaxHeapifyIterativeControlConstruct(vector<int>& A, int heap_size, int i)
{
	int l, r, largest;
	while (1)
	{
		l = BinaryTreeLeft(i);
		r = BinaryTreeRight(i);
		if (l < heap_size && A.at(l) > A.at(i))
			largest = l;
		else
			largest = i;
		if (r < heap_size && A.at(r) > A.at(largest))
			largest = r;
		if (largest == i)
			break;
		SwapInt(A.at(i), A.at(largest));
		i = largest;
	}
}

//O(n)
int BuildMaxHeap(vector<int>& A)
{
	int i, heap_size;
	heap_size = A.size();
	for (i = heap_size / 2 - 1; i >= 0; --i)
	{
		MaxHeapify(A, heap_size, i);
	}
	return heap_size;
}

//O(nlgn)
void Heapsort(vector<int>& A)
{
	int i, heap_size;
	heap_size = BuildMaxHeap(A);
	for (i = heap_size - 1; i > 0; --i)
	{
		SwapInt(A.at(0), A.at(i));
		MaxHeapify(A, --heap_size, 0);
	}
}

//O(1)
int HeapMaximum(vector<int>& A)
{
	return A.at(0);
}

//O(lgn)
int HeapExtractMax(vector<int>& A)
{
	int max_val;
	if (A.size() < 1)
		throw "heap underflow";
	int &max = A.at(0);
	max_val = max;
	max = A.at(A.size() - 1);
	A.pop_back();
	MaxHeapify(A, A.size(), 0);
	return max_val;
}

//O(lgn)
void HeapIncreaseKey(vector<int>& A, int i, int key)
{
	if (key < A.at(i))
		throw "new key is smaller than current key";
	A.at(i) = key;
	while (i > 0 && A.at(BinaryTreeParent(i)) < A.at(i))
	{
		SwapInt(A.at(i), A.at(BinaryTreeParent(i)));
		i = BinaryTreeParent(i);
	}
}

//O(lgn) 6.5-6
void HeapIncreaseKeyOneAssignment(vector<int>& A, int i, int key)
{
	if (key < A.at(i))
		throw "new key is smaller than current key";
	while (i > 0 && A.at(BinaryTreeParent(i)) < key)
	{
		A.at(i) = A.at(BinaryTreeParent(i));
		i = BinaryTreeParent(i);
	}
	A.at(i) = key;
}

//O(lgn)
void MaxHeapInsert(vector<int>& A, int key)
{
	A.push_back(INT_MIN);
	HeapIncreaseKeyOneAssignment(A, A.size() - 1, key);
}

//O(lgn) 6.5-8
void MaxHeapDelete(vector<int>& A, int i)
{
	int last_member_val;
	last_member_val = A.at(A.size() - 1);
	int& i_ref = A.at(i);
	A.pop_back();
	if (last_member_val > i_ref)
	{
		HeapIncreaseKeyOneAssignment(A, i, last_member_val);
	}
	else if (last_member_val < i_ref)
	{
		i_ref = last_member_val;
		MaxHeapify(A, A.size(), i);
	}
}

//min heap-----------------------------------------------
//O(lgn) 6.2-2
void MinHeapify(vector<int>& A, int heap_size, int i)
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
		MinHeapify(A, heap_size, smallest);
	}
}

//O(n)
int BuildMinHeap(vector<int>& A)
{
	int i, heap_size;
	heap_size = A.size();
	for (i = heap_size / 2 - 1; i >= 0; --i)
	{
		MinHeapify(A, heap_size, i);
	}
	return heap_size;
}

//O(1) 6.5-3
int HeapMinimum(vector<int>& A)
{
	return A.at(0);
}

//O(lgn) 6.5-3
int HeapExtractMin(vector<int>& A)
{
	int min_val;
	if (A.size() < 1)
		throw "heap underflow";
	int& min = A.at(0);
	min_val = min;
	min = A.at(A.size() - 1);
	A.pop_back();
	MinHeapify(A, A.size(), 0);
	return min_val;
}

//O(lgn) 6.5-3
void HeapDecreaseKey(vector<int>& A, int i, int key)
{
	if (key > A.at(i))
		throw "new key is greater than current key";
	A.at(i) = key;
	while (i > 0 && A.at(BinaryTreeParent(i)) > A.at(i))
	{
		SwapInt(A.at(i), A.at(BinaryTreeParent(i)));
		i = BinaryTreeParent(i);
	}
}

//O(lgn)
void HeapDecreaseKeyOneAssignment(vector<int>& A, int i, int key)
{
	if (key > A.at(i))
		throw "new key is greater than current key";
	while (i > 0 && A.at(BinaryTreeParent(i)) > key)
	{
		A.at(i) = A.at(BinaryTreeParent(i));
		i = BinaryTreeParent(i);
	}
	A.at(i) = key;
}

//O(lgn) 6.5-3
void MinHeapInsert(vector<int>& A, int key)
{
	A.push_back(INT_MAX);
	HeapDecreaseKeyOneAssignment(A, A.size() - 1, key);
}

//main---------------------------------------------------
int main_heapsort()
{
	int ret, filled_value_index;
	vector<int> A;
	vector<int>::iterator it;
	/*
	A.push_back(16);
	A.push_back(4);
	A.push_back(10);
	A.push_back(14);
	A.push_back(7);
	A.push_back(9);
	A.push_back(3);
	A.push_back(2);
	A.push_back(8);
	A.push_back(1);
	*/
	A.push_back(5);
	A.push_back(13);
	A.push_back(2);
	A.push_back(25);
	A.push_back(7);
	A.push_back(17);
	A.push_back(20);
	A.push_back(8);
	A.push_back(4);
	BuildMinHeap(A);
	for (it = A.begin(); it != A.end(); it++)
	{
		printf("%i ", *it);
	}
	printf("\n");
	//ret = HeapExtractMinAndFillSpaceBySpecificValueGetIndex(A, INT_MAX, 
	//	filled_value_index);
	for (it = A.begin(); it != A.end(); it++)
	{
		printf("%i ", *it);
	}
	printf("\n");
	return 0;
}

