#include "partition.h"

/*
成(n)
n = r - p + 1
return: q
*/
int Partition(vector<int>& A, int p, int r)
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
成(n)
n = r - p + 1
return: q
*/
int RandomizedPartition(vector<int>& A, int p, int r)
{
	int i;
	srand((unsigned)time(NULL));
	i = GetRangedRandomNum(p, r);
	SwapInt(A[r], A[i]);
	return Partition(A, p, r);
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
partition of FuzzySort
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
成(r - p)
7-p-2-b
parameters:
	pivot_left_index: out-para
	pivot_right_index: out-para
*/
void PartitionSpecificPivotIndex(vector<int>& A, int p, int r,
	int pivot_index, int& pivot_left_index, int& pivot_right_index)
{
	int j, x, j_val;
	x = A[pivot_index];
	pivot_right_index = pivot_left_index = p - 1;
	for (j = p; j <= r; ++j)
	{
		j_val = A[j];
		if (j_val == x)
		{
			SwapInt(A[++pivot_right_index], A[j]);
		}
		else if (j_val < x)
		{
			A[j] = A[++pivot_right_index];
			A[pivot_right_index] = A[++pivot_left_index];
			A[pivot_left_index] = j_val;
		}
	}
	++pivot_left_index;
}

/*
成(n)
parameters:
	pivot_left_index: out-para
	pivot_right_index: out-para
*/
void PartitionSpecificPivotValue(vector<int>& A, int begin_index, int end_index,
	int pivot_val, int& pivot_left_index, int& pivot_right_index)
{
	int j, j_val;
	pivot_right_index = pivot_left_index = begin_index - 1;
	for (j = begin_index; j <= end_index; ++j)
	{
		j_val = A[j];
		if (j_val == pivot_val)
		{
			SwapInt(A[++pivot_right_index], A[j]);
		}
		else if (j_val < pivot_val)
		{
			A[j] = A[++pivot_right_index];
			A[pivot_right_index] = A[++pivot_left_index];
			A[pivot_left_index] = j_val;
		}
	}
	++pivot_left_index;
}

/*
成(r - p)
7-p-2-b
parameters:
	pivot_left_index: out-para
	pivot_right_index: out-para
*/
void PartitionSpecificPivotIndex(vector< ElementWithKey* >& A, int p, int r,
	int pivot_index, int& pivot_left_index, int& pivot_right_index)
{
	int j, x;
	ElementWithKey* j_val;
	x = A[pivot_index]->key_;
	pivot_right_index = pivot_left_index = p - 1;
	for (j = p; j <= r; ++j)
	{
		j_val = A[j];
		if (j_val->key_ == x)
		{
			SwapTemplate(A[++pivot_right_index], A[j]);
		}
		else if (j_val->key_ < x)
		{
			A[j] = A[++pivot_right_index];
			A[pivot_right_index] = A[++pivot_left_index];
			A[pivot_left_index] = j_val;
		}
	}
	++pivot_left_index;
}

/*
成(n)
parameters:
	pivot_left_index: out-para
	pivot_right_index: out-para
*/
void PartitionSpecificPivotValue(vector< ElementWithKey* >& A, int begin_index, 
	int end_index, int pivot_key_val, int& pivot_left_index, int& pivot_right_index)
{
	int j;
	ElementWithKey* j_val;
	pivot_right_index = pivot_left_index = begin_index - 1;
	for (j = begin_index; j <= end_index; ++j)
	{
		j_val = A[j];
		if (j_val->key_ == pivot_key_val)
		{
			SwapTemplate(A[++pivot_right_index], A[j]);
		}
		else if (j_val->key_ < pivot_key_val)
		{
			A[j] = A[++pivot_right_index];
			A[pivot_right_index] = A[++pivot_left_index];
			A[pivot_left_index] = j_val;
		}
	}
	++pivot_left_index;
}
