#include "stdafx.h"
#include "insertion_sort.h"

/*
成(n)
n = r - p + 1
return: q
*/
int QuicksortPartition(vector<int>& A, int p, int r)
{
	int i, j;
	i = p - 1;
	for (j = p; j < r; ++j)
		if (A[j] <= A[r])
			SwapInt(A[++i], A[j]);
	SwapInt(A[++i], A[r]);
	return i;
}

/*
Best case: 成(nlgn)
Worst case: 成(n^2)
*/
void Quicksort(vector<int>& A, int p, int r)
{
	int q;
	if (p < r)
	{
		q = QuicksortPartition(A, p, r);
		Quicksort(A, p, q - 1);
		Quicksort(A, q + 1, r);
	}
}

/*
成(n)
n = r - p + 1
return: q
*/
int QuicksortRandomizedPartition(vector<int>& A, int p, int r)
{
	int i;
	srand((unsigned)time(NULL));
	i = GetRangedRandomNum(p, r);
	SwapInt(A[r], A[i]);
	return QuicksortPartition(A, p, r);
}

/*
Best case: 成(nlgn)
Worst case: 成(n^2)
*/
void RandomizedQuicksort(vector<int>& A, int p, int r)
{
	int q;
	if (p < r)
	{
		q = QuicksortRandomizedPartition(A, p, r);
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
		q = QuicksortRandomizedPartition(A, p, r);
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
成(n)
*/
int HoarePartition(vector<int>& A, int p, int r)
{
	int x, i, j;
	x = A[p];
	i = p - 1;
	j = r + 1;
	while (1)
	{
		do
			j--;
		while (A[j] > x);
		do
			i++;
		while (A[i] < x);
		if (i < j)
			SwapInt(A[i], A[j]);
		else
			return j;
	}
}

/*
Best case: 成(nlgn)
Worst case: 成(n^2)
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
成(r - p)
7-p-2-b
*/
void QuicksortPartitionSpecificPivotIndexReturnQAndT(vector<int>& A, int p, int r,
	int pivot_index, int& q, int& t)
{
	int j, x, j_val;
	x = A[pivot_index];
	t = q = p - 1;
	for (j = p; j <= r; ++j)
	{
		j_val = A[j];
		if (j_val == x)
		{
			SwapInt(A[++t], A[j]);
		}
		else if (j_val < x)
		{
			A[j] = A[++t];
			A[t] = A[++q];
			A[q] = j_val;
		}
	}
	q++;
}

/*
Best case: 成(nlgn)
Worst case: 成(n^2)
7-p-2-c
*/
void RandomizedQuicksortReturnQAndT(vector<int>& A, int p, int r)
{
	int pivot_index, q, t;
	if (p < r)
	{
		srand((unsigned)time(NULL));
		pivot_index = GetRangedRandomNum(p, r);
		QuicksortPartitionSpecificPivotIndexReturnQAndT(A, p, r, 
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
		q = QuicksortPartition(A, p, r);
		TailRecursiveQuicksort(A, p, q - 1);
		p = q + 1;
	}
}

/*
expexted running time: 成(nlgn)
stack depth: worse-case: 成(lgn)
7-p-4-c
*/
void TailRecursiveQuicksortModify(vector<int>& A, int p, int r)
{
	int q, half;
	while (p < r)
	{
		half = (r - p + 1) / 2;
		q = QuicksortPartition(A, p, r);
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
7-p-6
*/
class FuzzySortData
{
public:
	int a;//left endpoint
	int b;//right endpoint
	FuzzySortData(){}
	FuzzySortData(int a, int b)
	{
		this->a = a;
		this->b = b;
	}
};

/*
成(n)
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
成(n)
7-p-6
*/
void FuzzySortPartition(vector<FuzzySortData>& A,
	int p, int r, FuzzySortData& overlap_interval, int& q, int& t)
{
	FuzzySortData j_val;
	int j;
	t = q = p - 1;
	for (j = p; j <= r; ++j)
	{
		j_val = A[j];
		if (j_val.b < overlap_interval.a)
		{
			A[j] = A[++t];
			A[t] = A[++q];
			A[q] = j_val;
		}
		else if (!(j_val.a > overlap_interval.b))
		{
			SwapTemplate(A[++t], A[j]);
		}
	}
	q++;
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

	vector<int> B;
	B = { 2,4,8,7,1,4,3,5,6,4 };
//	B = { 1,2,3,4,5,6,7,8,9,10 };
	RandomizedQuicksort(B, 0, 9);
	
	return 0;
}


