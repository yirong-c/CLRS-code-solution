#include "../stdafx.h"
#include "../ch2/merge_sort.h"
#include "selection.h"
#include "../ch7/partition.h"
#include "../ch2/insertion_sort.h"

class WeightedElement : public ElementWithKey
{
public:
	int value_;
	float weight_;

	WeightedElement(int value, float weight) : ElementWithKey(weight * 100)
	{
		value_ = value;
		weight_ = weight;
	}
};

/*
return index of array
O(nlgn)
(b)
*/
int FindWeightedMedianSort(vector< WeightedElement* >& elements)
{
	int size, i;
	float weight_sum;
	size = elements.size();
	MergeSort((vector< ElementWithKey* >&)elements, 0, size - 1);
	weight_sum = 0;
	for (i = 0; i < size; ++i)
	{
		weight_sum += elements[i]->weight_;
		if (weight_sum >= 0.5)
			break;
	}
	return i;
}

/*
return index of array
O(n)
(c)
*/
int FindWeightedMedianSelectRecursive(vector< ElementWithKey* >& A,
	int begin_index, int end_index, int target_weight_sum, 
	int& pivot_left_index, int& pivot_right_index)
{
	int size, full_group_num, group_num, full_groups_size,
		last_nonfull_group_size, j, weight_sum;
	ElementWithKey* median_of_medians;
	vector< ElementWithKey* > medians;
	size = end_index - begin_index + 1;
	full_group_num = size / 5;
	full_groups_size = full_group_num * 5;
	last_nonfull_group_size = size - full_groups_size;
	group_num = full_group_num + (last_nonfull_group_size != 0);
	//find medians and insertion sort
	medians.reserve(group_num);
	for (j = begin_index; j < begin_index + full_groups_size; j += 5)
	{
		InsertionSort(A, j, j + 4);
		medians.push_back(A[j + 2]);
	}
	if (last_nonfull_group_size)
		medians.push_back(A[j + (last_nonfull_group_size - 1) / 2]);
	//find median of medians
	if (group_num == 1)
		median_of_medians = medians[0];
	else
		median_of_medians = medians[LinearSelect(medians,
			0, group_num - 1, (group_num - 1) / 2)];
	//partition
	PartitionSpecificPivotValue(A, begin_index, end_index, median_of_medians->key_,
		pivot_left_index, pivot_right_index);
	//calculate sum of weight
	weight_sum = 0;
	for (j = begin_index; j < pivot_left_index; ++j)
	{
		weight_sum += A[j]->key_;
	}
	if (weight_sum >= target_weight_sum)
		return FindWeightedMedianSelectRecursive(A, 
			begin_index, pivot_left_index - 1, target_weight_sum, 
			pivot_left_index, pivot_right_index);
	for (j = pivot_left_index; j <= pivot_right_index; ++j)
	{
		weight_sum += A[j]->key_;
		if (weight_sum >= target_weight_sum)
			return j;
	}
	return FindWeightedMedianSelectRecursive(A, 
		pivot_right_index + 1, end_index, target_weight_sum - weight_sum,
		pivot_left_index, pivot_right_index);
}

/*
return index of array
O(n)
(c)
*/
int FindWeightedMedianSelect(vector< WeightedElement* >& elements)
{
	int size, pivot_left_index, pivot_right_index;
	size = elements.size();
	return FindWeightedMedianSelectRecursive((vector< ElementWithKey* >&)elements,
		0, size - 1, 50, pivot_left_index, pivot_right_index);
}

int main_9_p_2()
{
	int ret, size, pivot_left_index, pivot_right_index;
	WeightedElement e1(1, 0.1);
	WeightedElement e2(2, 0.35);
	WeightedElement e3(3, 0.05);
	WeightedElement e4(4, 0.1);
	WeightedElement e5(5, 0.15);
	WeightedElement e6(6, 0.05);
	WeightedElement e7(7, 0.2);
	vector< WeightedElement* > elements;
	elements = { &e1,&e2,&e3,&e4,&e5,&e6,&e7 };
	size = elements.size();

	ret = FindWeightedMedianSelect(elements);

	ret = FindWeightedMedianSort(elements);

	return 0;
}
