#include "stdafx.h"

/*
жи(n)
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
жи(n)
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
жи(n)
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

int main_min_and_max()
{
	int min_val, max_val, second_smallest_value;
	vector<int> container_input;
	container_input = { 5,4,8,7,5,5,7,9,10,5,6,10,20 };
	second_smallest_value = FindSecondSmallestElement(container_input);
	
	SimultaneousMinMax(container_input, min_val, max_val);

	min_val = Minimum(container_input);

	return 0;
}
