#include "selection.h"
#include "partition.h"
#include "insertion_sort.h"

//9.1----------------------------------------------------------------

/*
成(n)
(n - 1) comparsions
*/
int Minimum(vector<int> A)
{
	int min, size, i;
	size = A.size();
	min = A[0];
	for (i = 1; i < size; ++i)
	{
		if (min > A[i])
			min = A[i];
	}
	return min;
}

/*
成(n)
at most 3(n/2) comparsions
size must greater than (>) 0 
*/
void SimultaneousMinMax(vector<int> A, int& min_val, int& max_val)
{
	size_t size;
	int i;
	size = A.size();
	if (size % 2)
	{
		min_val = max_val = A[0];
		i = 1;
	}
	else
	{
		if (A[0] <= A[1])
		{
			min_val = A[0];
			max_val = A[1];
		}
		else
		{
			min_val = A[1];
			max_val = A[0];
		}
		i = 2;
	}
	for (; i < size; i+=2)
	{
		if (A[i] <= A[i + 1])
		{
			if (min_val > A[i])
				min_val = A[i];
			if (max_val < A[i + 1])
				max_val = A[i + 1];			
		}
		else
		{
			if (min_val > A[i + 1])
				min_val = A[i + 1];
			if (max_val < A[i])
				max_val = A[i];
		}
	}
}

struct FindSecondSmallestElementResultTreeNode
{
	int left;
	int right;
	int is_left_small = -1;
};

//Init result_tree nodes and return index of element with smallest value
int FindSecondSmallestElementInitNodesGetSmallIndex(vector<int>& A, 
	vector<FindSecondSmallestElementResultTreeNode>& result_tree, int node)
{
	if (result_tree[node].is_left_small == -1)
	{
		result_tree[node].left = FindSecondSmallestElementInitNodesGetSmallIndex
			(A, result_tree, BinaryTreeLeft(node));
		result_tree[node].right = FindSecondSmallestElementInitNodesGetSmallIndex
			(A, result_tree, BinaryTreeRight(node));
		result_tree[node].is_left_small = 
			A[result_tree[node].left] <= A[result_tree[node].right];//comparison
	}
	return result_tree[node].is_left_small ?
		result_tree[node].left : result_tree[node].right;
}

/*
成(n)
(n + lgn - 2) comparsions
9.1-1
*/
int FindSecondSmallestElement(vector<int> A)
{
	int size, i, is_odd, result_tree_index, smallest_value_index, 
		second_smallest_value;
	list<int> second_smallest_value_index_candidates;
	list<int>::iterator it_p, it_end;
	size = A.size();
	is_odd = size % 2;
	size -= is_odd;
	vector<FindSecondSmallestElementResultTreeNode> result_tree(size - 1);
	result_tree_index = (size - 1) / 2;
	//init leaves of result tree
	for (i = 0; i < size; i += 2)
	{
		result_tree[result_tree_index].is_left_small = A[i] <= A[i + 1];
		result_tree[result_tree_index].left = i;
		result_tree[result_tree_index].right = i + 1;
		++result_tree_index;
	}
	//init nodes of result tree
	smallest_value_index = FindSecondSmallestElementInitNodesGetSmallIndex
		(A, result_tree, 0);
	//add the left "odd" into second_smallest_value_index_candidates 
	if (is_odd)
	{
		if (A[smallest_value_index] > A[size])//comparison
			return A[smallest_value_index];
		else
			second_smallest_value_index_candidates.push_back(size);
	}
	//add index into second_smallest_value_index_candidates 
	result_tree_index = 0;
	while (result_tree_index < size - 1)
	{
		if (result_tree[result_tree_index].is_left_small)
		{
			second_smallest_value_index_candidates.push_back
				(result_tree[result_tree_index].right);
			result_tree_index = BinaryTreeLeft(result_tree_index);
		}
		else
		{
			second_smallest_value_index_candidates.push_back
			(result_tree[result_tree_index].left);
			result_tree_index = BinaryTreeRight(result_tree_index);
		}
	}
	//find second_smallest_value from second_smallest_value_index_candidates
	it_p = second_smallest_value_index_candidates.begin();
	it_end = second_smallest_value_index_candidates.end();
	second_smallest_value = INT_MAX;
	while (it_p != it_end)
	{
		if (second_smallest_value > A[*it_p])//comparison
			second_smallest_value = A[*it_p];
		++it_p;
	}
	return second_smallest_value;
}

//9.2----------------------------------------------------------------

/*
expexted running time: 成(n)
worst-case time: 成(n^2)
parameter: 
	i: ith (start by 1) smallest element of the array A
*/
int RandomizedSelect(vector<int> A, int begin_index, int end_index,
	int i)
{
	int middle_index, relative_middle_index;
	if (begin_index == end_index)
		return A[begin_index];
	middle_index = RandomizedPartition(A, begin_index, end_index);
	relative_middle_index = middle_index - begin_index + 1;
	if (i == relative_middle_index)
		return A[middle_index];
	else if (i < relative_middle_index)
		return RandomizedSelect(A, begin_index, middle_index - 1, i);
	else
		return RandomizedSelect(A, middle_index + 1, end_index, 
			i - relative_middle_index);
}

/*
expexted running time: 成(n)
worst-case time: 成(n^2)
parameter:
	i: ith (start by 1) smallest element of the array A
9.2-3
*/
int RandomizedSelectIterativeVersion(vector<int> A,
	int begin_index, int end_index,
	int i)
{
	int middle_index, relative_middle_index;
	while (1)
	{
		if (begin_index == end_index)
			return A[begin_index];
		middle_index = RandomizedPartition(A, begin_index, end_index);
		relative_middle_index = middle_index - begin_index + 1;
		if (i == relative_middle_index)
			return A[middle_index];
		else if (i < relative_middle_index)
			end_index = middle_index - 1;
		else
		{
			begin_index = middle_index + 1;
			i -= relative_middle_index;
		}
	}
}

//9.3----------------------------------------------------------------

/*
with the function of Partition
worst-case time: 成(n)
parameter:
	i_index: index (start by 0, base is begin_index) of 
			ith smallest element of the array A
	i_index = i + begin_index - 1;
*/
int LinearSelect(vector<int>& A, int begin_index, int end_index, int i_index)
{
	int size, full_group_num, group_num, full_groups_size, 
		last_nonfull_group_size, j, median_of_medians, 
		pivot_left_index, pivot_right_index;
	vector<int> medians;
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
		median_of_medians = LinearSelect(medians,
			0, group_num - 1, (group_num - 1) / 2);
	//partition
	PartitionSpecificPivotValue(A, begin_index, end_index, median_of_medians,
		pivot_left_index, pivot_right_index);
	if (i_index >= pivot_left_index && i_index <= pivot_right_index)
		return median_of_medians;
	else if (i_index < pivot_left_index)
		return LinearSelect(A, begin_index, pivot_left_index - 1, i_index);
	else
		return LinearSelect(A, pivot_right_index + 1, end_index, i_index);
}

/*
with the function of Partition
worst-case time: 成(n)
parameter:
	i: ith (start by 1) smallest element of the array A
*/
int LinearSelectEntrance(vector<int>& A, int i)
{
	//i_index = i + begin_index - 1;
	return LinearSelect(A, 0, A.size() - 1, i - 1);
}

/*
with the function of Partition
worst-case time: 成(n)
parameter:
	i_index: index (start by 0, base is begin_index) of
			ith smallest element of the array A
	i_index = i + begin_index - 1;
*/
int LinearSelectReturnPivotIndex(vector<int>& A, int begin_index, int end_index, 
	int i_index, int& pivot_left_index, int& pivot_right_index)
{
	int size, full_group_num, group_num, full_groups_size,
		last_nonfull_group_size, j, median_of_medians;
	vector<int> medians;
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
		median_of_medians = LinearSelect(medians,
			0, group_num - 1, (group_num - 1) / 2);
	//partition
	PartitionSpecificPivotValue(A, begin_index, end_index, median_of_medians,
		pivot_left_index, pivot_right_index);
	if (i_index >= pivot_left_index && i_index <= pivot_right_index)
		return median_of_medians;
	else if (i_index < pivot_left_index)
		return LinearSelectReturnPivotIndex(A, begin_index, pivot_left_index - 1, 
			i_index, pivot_left_index, pivot_right_index);
	else
		return LinearSelectReturnPivotIndex(A, pivot_right_index + 1, end_index, 
			i_index, pivot_left_index, pivot_right_index);
}

/*
with the function of Partition
worst-case time: 成(n)
*/
int LinearSelectMedianReturnPivotIndex(vector<int>& A, int begin_index, 
	int end_index, int& pivot_left_index, int& pivot_right_index)
{
	LinearSelectReturnPivotIndex(A, begin_index, end_index,
		(begin_index + end_index) / 2, pivot_left_index, pivot_right_index);
}

/*
QuicksortMedianPivot is in quicksort.cpp
成(nlgn)
9.3 - 3
*/

/*
select ith (start by 1) smallest element of the array A
		by using worst-case linear-time median subroutine
parameters:
	i_index: index (start by 0, base is begin_index) of
			ith smallest element of the array A
	i_index = i + begin_index - 1; 
9.3-5
*/
int SelectByBlackBox(vector<int>& A, int begin_index, int end_index,
	int i_index)
{
	int pivot_left_index, pivot_right_index, median;
	median = LinearSelectMedianReturnPivotIndex(A, begin_index, end_index,
		pivot_left_index, pivot_right_index);//black box + partition function
	if (i_index >= pivot_left_index && i_index <= pivot_right_index)
		return median;
	else if (i_index < pivot_left_index)
		return SelectByBlackBox(A, begin_index, pivot_left_index - 1,
			i_index);
	else
		return SelectByBlackBox(A, pivot_left_index + 1, end_index,
			i_index);
}

/*
Find kth quantiles
with the function of Partition
O(nlgk)
parameters:
	element_num_of_group: element numbers of each group
	quantiles: do NOT resize before the function is called; 
			reserve should be done before the function is called 
			(should be done in FindKthQuantilesEntrance)
9.3-6
*/
void FindKthQuantiles(vector<int>& A, int begin_index, int end_index, 
	int element_num_of_group, vector<int>& quantiles)
{
	int size, group_num, pivot_index, quantily_value;
	size = end_index - begin_index + 1;
	group_num = size / element_num_of_group +
		(size % element_num_of_group != 0);
	if (group_num <= 1)
		return;
	pivot_index = begin_index + int(group_num / 2) * element_num_of_group - 1;
	quantily_value = LinearSelect(A, begin_index, end_index, pivot_index);
	FindKthQuantiles(A, begin_index, pivot_index - 1, element_num_of_group, 
		quantiles);
	quantiles.push_back(quantily_value);
	FindKthQuantiles(A, pivot_index + 1, end_index, element_num_of_group,
		quantiles);
}

/*
Find kth quantiles
with the function of Partition
O(nlgk)
parameters:
	quantiles: do NOT resize and reserve before the function is called
9.3-6
*/
void FindKthQuantilesEntrance(vector<int>& A, int k, vector<int>& quantiles)
{
	int element_num_of_group, size;
	size = A.size();
	element_num_of_group = size / k +
		(A.size() % k != 0);
	quantiles.reserve(element_num_of_group - 1);
	FindKthQuantiles(A, 0, size - 1, element_num_of_group, quantiles);
}

//-------------------------------------------------------------------

int main_selection()
{
	int min_val, max_val, i_smallest_value, size, 
		pivot_left_index, pivot_right_index;
	vector<int> container_input, quantiles;
	container_input = { 5,4,8,7,5,5,7,9,10,5,6,10,20,
		5,4,8,7,5,5,7,9,10,5,6,10,20,
		5,4,8,7,5,5,7,9,10,5,6,10,20 };
	size = container_input.size();

	FindKthQuantilesEntrance(container_input, 5, quantiles);

	i_smallest_value = SelectByBlackBox(container_input, 0, size - 1, 20);
	
	i_smallest_value = LinearSelectReturnPivotIndex
		(container_input, 0, size - 1, (size - 1) / 2, 
		pivot_left_index, pivot_right_index);

	i_smallest_value = LinearSelectEntrance
	(container_input, 24);

	i_smallest_value = RandomizedSelectIterativeVersion
		(container_input, 0, size - 1, 2);

	i_smallest_value = RandomizedSelect(container_input, 0, size - 1, 2);

	i_smallest_value = FindSecondSmallestElement(container_input);
	
	SimultaneousMinMax(container_input, min_val, max_val);

	min_val = Minimum(container_input);

	return 0;
}
