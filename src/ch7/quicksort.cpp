#include "../stdafx.h"
#include "../ch2/insertion_sort.h"
#include "../ch9/selection.h"
#include "partition.h"
#include "quicketsort.h"

/*
Best case: ��(nlgn)
Worst case: ��(n^2)
*/
void Quicksort(vector<int>& A, int p, int r)
{
	int q;
	if (p < r)
	{
		q = Partition(A, p, r);
		Quicksort(A, p, q - 1);
		Quicksort(A, q + 1, r);
	}
}

/*
Best case: ��(nlgn)
Worst case: ��(n^2)
*/
void RandomizedQuicksort(vector<int>& A, int p, int r)
{
	int q;
	if (p < r)
	{
		q = RandomizedPartition(A, p, r);
		RandomizedQuicksort(A, p, q - 1);
		RandomizedQuicksort(A, q + 1, r);
	}
}

/*
Expected: O(nlg(n/k))
7-4-5
*/
void QuicksortOptByInsertionSortDoQuicksort(const int& k, vector<int>& A, int p, int r)
{
	int q;
	if (p < r && r - p + 1 >= k)
	{
		q = RandomizedPartition(A, p, r);
		QuicksortOptByInsertionSortDoQuicksort(k, A, p, q - 1);
		QuicksortOptByInsertionSortDoQuicksort(k, A, q + 1, r);
	}
}

/*
Expected: O(nk + nlg(n/k))
7-4-5
*/
void QuicksortOptByInsertionSort(const int& k, vector<int>& A, int p, int r)
{
	QuicksortOptByInsertionSortDoQuicksort(k, A, p, r);
	InsertionSort(A);
}

/*
Best case: ��(nlgn)
Worst case: ��(n^2)
7-p-1-e
*/
void HoareQuicksort(vector<int>& A, int p, int r)
{
	int q;
	if (p < r)
	{
		q = HoarePartition(A, p, r);
		HoareQuicksort(A, p, q);
		HoareQuicksort(A, q + 1, r);
	}
}

/*
Best case: ��(nlgn)
Worst case: ��(n^2)
7-p-2-c
*/
void RandomizedQuicksortReturnQAndT(vector<int>& A, int p, int r)
{
	int pivot_index, q, t;
	if (p < r)
	{
		srand((unsigned)time(NULL));
		pivot_index = GetRangedRandomNum(p, r);
		PartitionSpecificPivotIndex(A, p, r,
			pivot_index, q, t);
		RandomizedQuicksortReturnQAndT(A, p, q - 1);
		RandomizedQuicksortReturnQAndT(A, t + 1, r);
	}
}

void TailRecursiveQuicksort(vector<int>& A, int p, int r)
{
	int q;
	while (p < r)
	{
		q = Partition(A, p, r);
		TailRecursiveQuicksort(A, p, q - 1);
		p = q + 1;
	}
}

/*
expexted running time: ��(nlgn)
stack depth: worse-case: ��(lgn)
7-p-4-c
*/
void TailRecursiveQuicksortModify(vector<int>& A, int p, int r)
{
	int q, half;
	while (p < r)
	{
		half = (r - p + 1) / 2;
		q = Partition(A, p, r);
		if (q <= half)
		{
			TailRecursiveQuicksortModify(A, p, q - 1);
			p = q + 1;
		}
		else
		{
			TailRecursiveQuicksortModify(A, q + 1, r);
			r = q - 1;
		}

	}
}


/*
��(n)
7-p-6
*/
void FindOverlapInterval(vector<FuzzySortData>& A,
	int p, int r, int pivot_index, FuzzySortData& overlap_interval)
{
	FuzzySortData j_val;
	int j;
	overlap_interval = A[pivot_index];
	for (j = p; j <= r; ++j)
	{
		j_val = A[j];
		if (j_val.a <= overlap_interval.b && j_val.b >= overlap_interval.a)
		{
			if (j_val.a < overlap_interval.a)
				overlap_interval.a = j_val.a;
			if (j_val.b > overlap_interval.b)
				overlap_interval.b = j_val.b;
		}
	}
}


/*
7-p-6
*/
void FuzzySort(vector<FuzzySortData>& A, int p, int r)
{
	FuzzySortData overlap_interval;
	int pivot_index, q, t;
	if (p < r)
	{
		pivot_index = GetRangedRandomNum(p, r);
		FindOverlapInterval(A, p, r, pivot_index, overlap_interval);
		FuzzySortPartition(A, p, r, overlap_interval, q, t);
		FuzzySort(A, p, q - 1);
		FuzzySort(A, t + 1, r);
	}

}

/*
��(nlgn)
9.3-3
*/
void QuicksortMedianPivot(vector<int>& A, int begin_index, int end_index)
{
	int pivot_left_index, pivot_right_index;
	if (begin_index < end_index)
	{
		LinearSelectMedian(A, begin_index, end_index,
			pivot_left_index, pivot_right_index);
		RandomizedQuicksortReturnQAndT(A, begin_index, pivot_left_index - 1);
		RandomizedQuicksortReturnQAndT(A, pivot_right_index + 1, end_index);
	}
}

int main_quicksort()
{
	vector<FuzzySortData> A;
	A = { 
		FuzzySortData(3, 5),
		FuzzySortData(1, 2),
		FuzzySortData(6, 7),
		FuzzySortData(16, 20),
		FuzzySortData(6, 8),
		FuzzySortData(9, 15),
	};
	FuzzySort(A, 0, 5);

	vector<int> B, container_input;
	B = { 2,4,8,7,1,4,3,5,6,4 };
//	B = { 1,2,3,4,5,6,7,8,9,10 };
	container_input = { 5,4,8,7,5,5,7,9,10,5,6,10,20,
	5,4,8,7,5,5,7,9,10,5,6,10,20,
	5,4,8,7,5,5,7,9,10,5,6,10,20 };

	QuicksortMedianPivot(container_input, 0, container_input.size() - 1);

	RandomizedQuicksort(B, 0, 9);
	
	return 0;
}


