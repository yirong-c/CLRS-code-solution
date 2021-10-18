#include "../stdafx.h"

inline int DAryHeapParent(int d, int i)
{
	return (i - 1) / d;
}

//child_id start by 1
inline int DAryHeapChild(int d, int i, int child_id)
{
	return d * i + child_id;
}

/*
O(d * log_d(n)) = O(dlgn/lgd)
T(n) = T(n/d) + O(d)
*/
void DAryMaxHeapify(int d, vector<int>& A, int heap_size, int i)
{
	int largest, child_id, child_key;
	child_key = DAryHeapChild(d, i, 1);
	largest = i;
	for (child_id = 1; child_id <= d; ++child_id)
	{
		child_key = DAryHeapChild(d, i, child_id);
		if (child_key < heap_size)
			if (A.at(child_key) > A.at(largest))
				largest = child_key;
		else
			break;
	}
	if (largest != i)
	{
		SwapInt(A.at(i), A.at(largest));
		DAryMaxHeapify(d, A, heap_size, largest);
	}
}

//O(dlgn/lgd)
int DAryHeapExtractMax(int d, vector<int>& A)
{
	int max_val;
	if (A.size() < 1)
		throw "heap underflow";
	int& max = A.at(0);
	max_val = max;
	max = A.at(A.size() - 1);
	A.pop_back();
	DAryMaxHeapify(d, A, A.size(), 0);
	return max_val;
}

//O(lgn/lgd)
void DAryHeapIncreaseKey(int d, vector<int>& A, int i, int key)
{
	if (key < A.at(i))
		throw "new key is smaller than current key";
	while (i > 0 && A.at(DAryHeapParent(d, i)) < key)
	{
		A.at(i) = A.at(DAryHeapParent(d, i));
		i = DAryHeapParent(d, i);
	}
	A.at(i) = key;
}

//O(lgn/lgd)
void DAryMaxHeapInsert(int d, vector<int>& A, int key)
{
	A.push_back(INT_MIN);
	DAryHeapIncreaseKey(d, A, A.size() - 1, key);
}

int main_6_p_2()
{
	int ret;
	vector<int> list;
	DAryMaxHeapInsert(3, list, 10);
	DAryMaxHeapInsert(3, list, 8);
	DAryMaxHeapInsert(3, list, 5);
	DAryMaxHeapInsert(3, list, 6);
	DAryMaxHeapInsert(3, list, 2);
	DAryMaxHeapInsert(3, list, 3);
	DAryMaxHeapInsert(3, list, 7);
	DAryMaxHeapInsert(3, list, 1);
	DAryMaxHeapInsert(3, list, 13);
	ret = DAryHeapExtractMax(3, list);

	return 0;
}

