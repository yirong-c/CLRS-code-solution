#include "stdafx.h"
#include "merge_sort.h"
#include "heapsort.h"
#include "selection.h"

//(a)----------------------------------------------------------

/*
O(nlgn)
list i largest numbers
use merge sort
parameters:
	container_input: will be changed
	container_output: do NOT resize before function is called
	i: start by 1
*/
void FindLargestIA(vector<int>& container_input, vector<int>& container_output, 
	int i)
{
	int size, j;
	size = container_input.size();
	//merge sort
	MergeSort(container_input, 0, size - 1);
	//list numbers
	container_output.resize(i);
	for (j = 0; j < i; ++j)
		container_output[j] = container_input[size - j - 1];
}

//(b)----------------------------------------------------------

/*
O(n + ilgn)
list i largest numbers
use max-priority queue
parameters:
	container_input: will be changed
	container_output: do NOT resize before function is called
	i: start by 1
*/
void FindLargestIB(vector<int>& container_input, vector<int>& container_output, 
	int i)
{
	int j;
	//build max heap
	BuildMaxHeap(container_input);
	//extract i largest number
	container_output.resize(i);
	for (j = 0; j < i; ++j)
		container_output[j] = HeapExtractMax(container_input);
}

//(c)----------------------------------------------------------

/*
list i largest numbers
O(n + ilgi)
use LinearSelect partition and find ith largest number 
		and merge sort the i largest numbers
parameters:
	container_input: will be changed
	container_output: do NOT resize before function is called
	i: start by 1
*/
void FindLargestIC(vector<int>& container_input, vector<int>& container_output,
	int i)
{
	int size, j;
	size = container_input.size();
	//partition and find ith largest number
	LinearSelect(container_input, 0, size - 1, size - i);
	//transfer elements
	container_output.resize(i);
	for (j = 0; j < i; ++j)
		container_output[j] = container_input[size - j - 1];
	//merge sort
	MergeSortReverse(container_output, 0, i - 1);
}

//-------------------------------------------------------------

int main_9_p_1()
{
	vector<int> container_input, container_output;
	container_input = { 5,4,8,7,5,5,7,9,10,5,6,10,20,
	5,4,8,7,5,5,7,9,10,5,6,10,20,
	5,4,8,7,5,5,7,9,10,5,6,10,20 };

	FindLargestIC(container_input, container_output, 5);

	FindLargestIB(container_input, container_output, 5);

	FindLargestIA(container_input, container_output, 5);

	return 0;
}
