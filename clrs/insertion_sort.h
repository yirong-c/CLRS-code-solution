#pragma once

#include "stdafx.h"

/*
O(n^2)
T should have overload operator >
*/
template <typename T>
void InsertionSort(vector<T>& A)
{
	size_t j, size, i;
	T key;
	for (j = 1, size = A.size(); j < size; ++j)
	{
		key = A[j];
		i = j - 1;
		while (i >= 0 && A[i] > key)
		{
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
}

/*
O(n^2)
T should have overload operator >
*/
template <typename T>
void InsertionSortList(list<T>& A)
{
	typename list<T>::iterator iterator_begin, iterator_end,
		iterator_j, iterator_i_low, iterator_i_high;
	T key;
	iterator_begin = A.begin();
	iterator_end = A.end();
	for (iterator_j = iterator_begin, ++iterator_j;
		iterator_j != iterator_end; ++iterator_j)
	{
		key = *iterator_j;
		iterator_i_high = iterator_i_low = iterator_j;
		--iterator_i_low;
		while (iterator_i_high != iterator_begin && *iterator_i_low > key)
		{
			*iterator_i_high = *iterator_i_low;
			--iterator_i_high;
			--iterator_i_low;
		}
		*iterator_i_high = key;
	}
}

/*
O(n^2)
T should have overload operator >
*/
template <typename T>
void InsertionSort(vector<T>& A, int begin_index, int end_index)
{
	size_t j, i;
	T key;
	for (j = begin_index + 1; j <= end_index; ++j)
	{
		key = A[j];
		i = j - 1;
		while (i >= 0 && A[i] > key)
		{
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
}