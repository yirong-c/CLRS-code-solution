#include "stdafx.h"
#include "merge_sort.h"
#include "k_way_merge__6_5_9.h"

struct AverageSortingMergeSortParaData
{
	int container_index_base;
	int step_length;
};

//callback func of AverageSorting, AverageSortingOutputSubsets
void AverageSortingGetKey
(void* container, int index, void* key, void* data)
{
	AverageSortingMergeSortParaData& data_ref =
		*(AverageSortingMergeSortParaData*)data;
	index = data_ref.container_index_base + data_ref.step_length * index;
	*(int*)key = ((vector<int>*)container)->at(index);
}

//callback func of AverageSorting
void AverageSortingCopyElementBetweenContainer(void* container_A, int index_A, 
	void* container_B, int index_B, void* data)
{
	AverageSortingMergeSortParaData& data_ref =
		*(AverageSortingMergeSortParaData*)data;
	index_A = data_ref.container_index_base + data_ref.step_length * index_A;
	index_B = data_ref.container_index_base + data_ref.step_length * index_B;
	((vector<int>*)container_B)->at(index_B) = 
		((vector<int>*)container_A)->at(index_A);
}

//callback func of AverageSortingOutputSubsets
void AverageSortingCopyElementBetweenContainerOutputSubsets
	(void* container_A, int index_A, void* container_B, int index_B, void* data)
{
	AverageSortingMergeSortParaData& data_ref =
		*(AverageSortingMergeSortParaData*)data;
	index_A = data_ref.container_index_base + data_ref.step_length * index_A;
	((vector<int>*)container_B)->at(index_B) =
		((vector<int>*)container_A)->at(index_A);
}

/*
O(nlg(n/k))
sort the elements in container_input into k-sorted ayyay
Parameter:
	container_input: input container of elements
	container_output: output container of elements; resize before the function is called
8_p_5_d
*/
void AverageSorting(int k, vector<int>& container_input, vector<int>& container_output)
{
	int container_size, subset_element_size_least, subset_element_size_reminder;
	container_size = container_input.size();
	AverageSortingMergeSortParaData para_data;
	CommonSortParameters para;
	para.data = &para_data;
	para.container_1 = &container_input;
	para.container_2 = &container_output;
	para.t1_get_key_from_container = AverageSortingGetKey;
	para.t1_copy_element_between_containers =
		AverageSortingCopyElementBetweenContainer;
	para_data.container_index_base = 0;
	para_data.step_length = k;
	subset_element_size_least = container_size / para_data.step_length;
	subset_element_size_reminder = container_size % para_data.step_length;
	for (para_data.container_index_base = 0; 
		para_data.container_index_base < para_data.step_length; 
		++para_data.container_index_base)
	{
		para.t1_container_elements_size = subset_element_size_least + 
			(subset_element_size_reminder > para_data.container_index_base);
		MergeSort(para);
	}
}

/*
O(nlg(n/k))
sort the elements in container_input into k-sorted ayyay
Parameter:
	container_input: input container of elements
	container_output_subsets: output container of subset container of elements; 
			do NOT need to resize anything in this container
8_p_5_e
*/
void AverageSortingOutputSubsets(int k, vector<int>& container_input, 
	vector< vector<int> >& container_output_subsets)
{
	int container_size, subset_element_size_least, subset_element_size_reminder;
	container_size = container_input.size();
	AverageSortingMergeSortParaData para_data;
	CommonSortParameters para;
	para.data = &para_data;
	para.container_1 = &container_input;
	para.t1_get_key_from_container = AverageSortingGetKey;
	para.t1_copy_element_between_containers =
		AverageSortingCopyElementBetweenContainerOutputSubsets;
	para_data.container_index_base = 0;
	para_data.step_length = k;
	subset_element_size_least = container_size / para_data.step_length;
	subset_element_size_reminder = container_size % para_data.step_length;
	container_output_subsets.clear();
	for (para_data.container_index_base = 0;
		para_data.container_index_base < para_data.step_length;
		++para_data.container_index_base)
	{
		para.t1_container_elements_size = subset_element_size_least +
			(subset_element_size_reminder > para_data.container_index_base);
		container_output_subsets.push_back(vector<int>(para.t1_container_elements_size));
		para.container_2 = &(container_output_subsets[para_data.container_index_base]);
		MergeSort(para);
	}
}

/*
O(nlg(k))
sort the k-sorted array (in the struct of container of subset container of elements) 
		in container_input_subsets into ordinary sorted array in container_output
8_p_5_e
*/
void KSortedArraySort(vector< vector<int> >& container_input_subsets, 
	vector<int>& container_output)
{
	KWayMergeArraysSort(container_input_subsets, container_output);
}

int main_8_p_5()
{
	vector<int> container_input, container_output;
	vector< vector<int> > container_output_subsets;
	container_input = { 5,4,8,3,7,1,5,5,7,9,10,5,6,8 };

	//8_p_5_e test
	AverageSortingOutputSubsets(4, container_input, container_output_subsets);
	KSortedArraySort(container_output_subsets, container_output);

	//8_p_5_d test
	container_output.clear();
	container_output.resize(container_input.size());
	AverageSorting(4, container_input, container_output);

	return 0;
}