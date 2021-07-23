#include "insertion_sort.h"

/*
O(n^2)
*/
void InsertionSort(vector< ElementWithKey* >& A, int begin_index, int end_index)
{
	int j, i;
	ElementWithKey* temp;
	for (j = begin_index + 1; j <= end_index; ++j)
	{
		temp = A[j];
		i = j - 1;
		while (i >= 0 && A[i]->key_ > temp->key_)
		{
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = temp;
	}
}
