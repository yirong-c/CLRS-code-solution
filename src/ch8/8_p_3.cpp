#include "../stdafx.h"
#include "../common_sort_parameters.h"
#include "counting_sort.h"
#include "bucket_sort.h"

/*
HAVE NOT TEST
��(k + n)
stable
Parameters:
	container_1: input containers (list) of elements
	container_2: output containers (vector) of elements;
			should be resize before the function is called
	t1_key_range: range of key of element in container_1
	t1_container_elements_size: size of elements in container_1 and container_2
	t1_iterator_size: size of iterator of container_1
	t1_iterator_group: iterator group of container_1
	t2_get_key_from_container: get key from container_1
	t2_copy_element_between_containers: copy the elements from container_1 to container2
	t1_get_container_iterators: get iterators of container_1
*/
/*
void CountingSortStableListToVector(CommonSortParameters& para)
{
	vector<int> C(para.t1_key_range + 1, 0);
	size_t i, j;
	int A_j_key;
	para.t1_get_container_iterators(para.container_1, false,
		para.t1_iterator_group.begin, para.t1_iterator_group.end,
		para.data);
	while (!memcmp(para.t1_iterator_group.begin,
		para.t1_iterator_group.end, para.t1_iterator_size))
	{
		para.t2_get_key_from_container(para.t1_iterator_group.begin,
			&A_j_key, para.data);
		++C[A_j_key];
	}
	for (i = 1; i <= para.t1_key_range; ++i)
	{
		C[i] += C[i - 1];
	}
	para.t1_get_container_iterators(para.container_1, true,
		para.t1_iterator_group.begin, para.t1_iterator_group.end,
		para.data);
	while (!memcmp(para.t1_iterator_group.begin,
		para.t1_iterator_group.end, para.t1_iterator_size))
	{
		para.t2_get_key_from_container(para.t1_iterator_group.begin,
			&A_j_key, para.data);
		para.t2_copy_element_between_containers(para.t1_iterator_group.begin,
			para.container_2, C[A_j_key] - 1, para.data);
		--C[A_j_key];
	}
}
*/

//8-p-3-a--------------------------------------------------------------------

struct IntWithDigitsNum
{
	int element;
	int digits_num;
};

int VectorIntWithDigitsNumInit(vector<int>& A,
	vector<IntWithDigitsNum>& element_with_size)
{
	int i, size, n, total_length;
	total_length = 0;
	size = element_with_size.size();
	for (i = 0; i < size; ++i)
	{
		element_with_size[i].element = A[i];
		while (A[i] != 0)
		{
			A[i] /= 10;
			++element_with_size[i].digits_num;
		}
		total_length += element_with_size[i].digits_num;
	}
	return total_length;
}

void ParaFuncGetDigitsNumFromVectorIntWithDigitsNum
(void* container, int index, void* key, void* data)
{
	*(int*)key =
		((*(vector<IntWithDigitsNum>*)container)[index]).digits_num;
}

void ParaFuncAddElementFromVectorIntWithDigitsNumToBucket
(void* container_A, int index_A, void* container_B, int index_B, void* data)
{
	(*(vector< list<int> >*)container_B)[index_B].push_back(
		((*(vector<IntWithDigitsNum>*)container_A)[index_A]).element
	);
}

struct SortingVariableLengthItemsIntCountingSortParametersData
{
	//digit of int; 0 is the most right digit
	int get_key_from_container_digit;
	int vector_base_index;
};

void ParaFuncGetSpecficDigitFromVectorInt
(void* container, int index, void* key, void* data)
{
	int i;
	SortingVariableLengthItemsIntCountingSortParametersData& data_ref =
		*(SortingVariableLengthItemsIntCountingSortParametersData*)data;
	int& key_ref = *(int*)key;
	index += data_ref.vector_base_index;
	key_ref = ((vector<int>*)container)->at(index);
	for (i = 0; i < data_ref.get_key_from_container_digit; ++i)
	{
		key_ref /= 10;
	}
	key_ref %= 10;
}

void ParaFuncCopyElementBetweenVectorsInt(void* vector_A, int index_A,
	void* vector_B, int index_B, void* data)
{
	index_A += 
		(*(SortingVariableLengthItemsIntCountingSortParametersData*)data).
		vector_base_index;
	index_B +=
		(*(SortingVariableLengthItemsIntCountingSortParametersData*)data).
		vector_base_index;
	((vector<int>*)vector_B)->at(index_B) = ((vector<int>*)vector_A)->at(index_A);
}

/*
��(n)
n (total_length) = total number of digits over all the integers in the array
stable
*/
void SortingVariableLengthItemsInt(vector<int>& A)
{
	int total_length, buckets_index, A_index, A_size;
	CommonSortParameters para;
	A_size = A.size();
	//classify element into buckets
	para.t1_container_elements_size = A_size;
	vector<IntWithDigitsNum> element_with_size(para.t1_container_elements_size);
	total_length = VectorIntWithDigitsNumInit(A, element_with_size);
	vector< list<int> > buckets(total_length + 1);
	para.container_1 = &element_with_size;
	para.container_2 = &buckets;
	para.t1_key_range = total_length;
	para.t1_get_key_from_container = ParaFuncGetDigitsNumFromVectorIntWithDigitsNum;
	para.t1_copy_element_between_containers = 
		ParaFuncAddElementFromVectorIntWithDigitsNumToBucket;
	BucketSortClassify(para);
	//concentrate buckets (list) into vector
	list<int>::iterator iterator_begin;
	list<int>::iterator iterator_end;
	vector<int> bucket_base_index_in_vector(total_length + 2);
	A_index = 0;
	for (buckets_index = 0; buckets_index <= total_length; ++buckets_index)
	{
		bucket_base_index_in_vector[buckets_index] = A_index;
		iterator_begin = buckets[buckets_index].begin();
		iterator_end = buckets[buckets_index].end();
		while (iterator_begin != iterator_end)
		{
			A[A_index] = *iterator_begin;
			++iterator_begin;
			++A_index;
		}
	}
	bucket_base_index_in_vector[total_length + 1] = A_size;
	//radix sort
	SortingVariableLengthItemsIntCountingSortParametersData counting_sort_para_data;
	para.data = &counting_sort_para_data;
	para.t1_get_key_from_container = ParaFuncGetSpecficDigitFromVectorInt;
	para.t1_copy_element_between_containers = ParaFuncCopyElementBetweenVectorsInt;
	vector<int> B(A_size);
	B = A;
	para.t1_key_range = 10;
	para.t1_iterator_size = sizeof(list<int>::iterator);
	para.container_1 = &A;
	para.container_2 = &B;
	for (buckets_index = 1; buckets_index <= total_length; ++buckets_index)
	{
		//counting sort
		para.t1_container_elements_size =
			bucket_base_index_in_vector[buckets_index + 1] -
			bucket_base_index_in_vector[buckets_index];
		if (para.t1_container_elements_size > 1)
		{
			counting_sort_para_data.vector_base_index =
				bucket_base_index_in_vector[buckets_index];
			for (counting_sort_para_data.get_key_from_container_digit = 0;
				counting_sort_para_data.get_key_from_container_digit < buckets_index;
				++counting_sort_para_data.get_key_from_container_digit)
			{
				CountingSortStable(para);
				SwapTemplate(para.container_1, para.container_2);
			}
			
		}
	}
	A = *(vector<int>*)para.container_1;
	return;
}

//8-p-3-b--------------------------------------------------------------------

struct SortingVariableLengthItemsCStrCountingSortParametersData
{
	//position of character; 0 is the most left character
	int get_key_from_container_char_pos;
	int vector_base_index;
};

void ParaFuncGetSpecficCharFromVectorCStr
(void* container, int index, void* key, void* data)
{
	int i;
	SortingVariableLengthItemsCStrCountingSortParametersData& data_ref =
		*(SortingVariableLengthItemsCStrCountingSortParametersData*)data;
	int& key_ref = *(int*)key;
	index += data_ref.vector_base_index;
	key_ref = *(((vector<const char*>*)container)->at(index) + 
		data_ref.get_key_from_container_char_pos);
	if (key_ref >= 97 && key_ref <= 122)
		key_ref -= 96;
	else
		key_ref = 0;
}

void ParaFuncCopyElementBetweenVectorsCStr(void* vector_A, int index_A,
	void* vector_B, int index_B, void* data)
{
	index_A +=
		(*(SortingVariableLengthItemsCStrCountingSortParametersData*)data).
		vector_base_index;
	index_B +=
		(*(SortingVariableLengthItemsCStrCountingSortParametersData*)data).
		vector_base_index;
	((vector<const char*>*)vector_B)->at(index_B) = 
		((vector<const char*>*)vector_A)->at(index_A);
}

void SortingVariableLengthItemsCStrRecursiveCallCountingSort(CommonSortParameters& para)
{
	int key_index, get_key_from_container_char_pos, vector_base_index;
	SortingVariableLengthItemsCStrCountingSortParametersData& counting_sort_para_data =
		*(SortingVariableLengthItemsCStrCountingSortParametersData*)para.data;
	CountingSortStableReturnCounterReturnValueStruct& counting_sort_return_struct = 
		*(CountingSortStableReturnCounterReturnValueStruct*)para.return_value_struct;
	vector<int> counting_sort_counter(para.t1_key_range + 2);
	counting_sort_return_struct.counter = &counting_sort_counter;
	CountingSortStableReturnCountingIndex(para);
	counting_sort_counter[para.t1_key_range + 1] = para.t1_container_elements_size;
	*(vector<const char*>*)para.container_1 = *(vector<const char*>*)para.container_2;
	++counting_sort_para_data.get_key_from_container_char_pos;
	get_key_from_container_char_pos = counting_sort_para_data.get_key_from_container_char_pos;
	vector_base_index = counting_sort_para_data.vector_base_index;
	for (key_index = 1; key_index <= para.t1_key_range; ++key_index)
	{
		counting_sort_para_data.vector_base_index = counting_sort_counter[key_index];
		para.t1_container_elements_size = counting_sort_counter[key_index + 1] - 
			counting_sort_para_data.vector_base_index;
		if (para.t1_container_elements_size > 1)
		{
			counting_sort_para_data.vector_base_index += vector_base_index;
			counting_sort_para_data.get_key_from_container_char_pos = 
				get_key_from_container_char_pos;
			SortingVariableLengthItemsCStrRecursiveCallCountingSort(para);
		}
	}
}

/*
��(n)
n (total_length) = total number of digits over all the integers in the array
stable
*/
void SortingVariableLengthItemsCStr(vector<const char*>& A)
{
	CommonSortParameters para;
	int A_size;
	A_size = A.size();
	vector<const char*> B(A_size);
	B = A;
	para.container_1 = &A;
	para.container_2 = &B;
	para.t1_key_range = 26;
	SortingVariableLengthItemsCStrCountingSortParametersData counting_sort_para_data;
	para.data = &counting_sort_para_data;
	para.t1_get_key_from_container = ParaFuncGetSpecficCharFromVectorCStr;
	para.t1_copy_element_between_containers = ParaFuncCopyElementBetweenVectorsCStr;
	CountingSortStableReturnCounterReturnValueStruct counting_sort_return_struct;
	para.return_value_struct = &counting_sort_return_struct;
	para.t1_container_elements_size = A_size;
	counting_sort_para_data.get_key_from_container_char_pos = 0;
	counting_sort_para_data.vector_base_index = 0;
	SortingVariableLengthItemsCStrRecursiveCallCountingSort(para);
}

//---------------------------------------------------------------------------

int main_8_p_3()
{
	vector<const char*> B;
	B = { "dzog", "dog", "cat","dsafa","trfssdjrtg","gdsfrhytkuw","a","ab","b","a" };
	SortingVariableLengthItemsCStr(B);

	vector<int> A;
	A = { 1,22,333,4444,55555,6666,777,88,9,123456 };
	SortingVariableLengthItemsInt(A);

	return 0;
}
