#include "stdafx.h"
#include "counting_sort.h"

/*
成(k + n)
stable
Parameter:
	A: input
	B: output
	k: range of array [0, k]
*/
void CountingSort(vector<int>& A, vector<int>& B, int k)
{
	vector<int> C(k + 1, 0);
	size_t i, j, size;
	size = A.size();
	B.resize(size);
	for (j = 0; j < size; ++j)
	{
		++C[A[j]];
	}
	for (i = 1; i <= k; ++i)
	{
		C[i] += C[i - 1];
	}
	for (j = size - 1; j >= 0 && j < size; --j)
	{
		B[C[A[j]] - 1] = A[j];
		--C[A[j]];
	}
}

/*
成(k + n)
anti-stable
Parameter:
	A: input
	B: output
	k: range of array [0, k]
*/
void ModifiedCountingSort(vector<int>& A, vector<int>& B, int k)
{
	vector<int> C(k + 1, 0);
	size_t i, j, size;
	size = A.size();
	B.resize(size);
	for (j = 0; j < size; ++j)
	{
		++C[A[j]];
	}
	for (i = 1; i <= k; ++i)
	{
		C[i] += C[i - 1];
	}
	for (j = 0; j < size; ++j)
	{
		B[C[A[j]] - 1] = A[j];
		--C[A[j]];
	}
}

/*
成(k + n)
stable
*/
void CountingSortStableOld(CommonVectorSortParameters& para)
{
	vector<int> C(para.k + 1, 0);
	size_t i, j;
	int A_j_key;
	for (j = 0; j < para.vector_elements_size; ++j)
	{
		para.get_key_from_vector(para.vector_A, j, &A_j_key, para.data);
		++C[A_j_key];
	}
	for (i = 1; i <= para.k; ++i)
	{
		C[i] += C[i - 1];
	}
	for (j = para.vector_elements_size - 1;
		j >= 0 && j < para.vector_elements_size; --j)
	{
		para.get_key_from_vector(para.vector_A, j, &A_j_key, para.data);
		para.cpy_element_between_vectors(para.vector_A, j,
			para.vector_B, C[A_j_key] - 1, para.data);
		--C[A_j_key];
	}
}

/*
成(k + n)
stable
Parameters:
	container_1: input containers (vector) of elements
	container_2: output containers (vector) of elements;
			should be resize before the function is called
	t1_key_range: range of key of element in container_1
	t1_container_elements_size: size of elements in container_1 and container_2
	t1_get_key_from_container: get key from container_1
	t1_copy_element_between_containers: copy the elements from container_1 to container2
*/
void CountingSortStable(CommonSortParameters& para)
{
	vector<int> C(para.t1_key_range + 1, 0);
	size_t i, j;
	int A_j_key;
	for (j = 0; j < para.t1_container_elements_size; ++j)
	{
		para.t1_get_key_from_container(para.container_1, j, &A_j_key, para.data);
		++C[A_j_key];
	}
	for (i = 1; i <= para.t1_key_range; ++i)
	{
		C[i] += C[i - 1];
	}
	for (j = para.t1_container_elements_size - 1;
		j >= 0 && j < para.t1_container_elements_size; --j)
	{
		para.t1_get_key_from_container(para.container_1, j, &A_j_key, para.data);
		para.t1_copy_element_between_containers(para.container_1, j,
			para.container_2, C[A_j_key] - 1, para.data);
		--C[A_j_key];
	}
}

/*
成(k + n)
stable
Parameters:
	container_1: input containers (vector) of elements
	container_2: output containers (vector) of elements;
			should be resize before the function is called
	t1_key_range: range of key of element in container_1
	t1_container_elements_size: size of elements in container_1 and container_2
	t1_get_key_from_container: get key from container_1
	t1_copy_element_between_containers: copy the elements from container_1 to container2
	return_value_struct should be init with the pointer of 
			CountingSortStableReturnCounterReturnValueStruct object
*/
void CountingSortStableReturnCountingIndex(CommonSortParameters& para)
{
	vector<int>& C = *(*(CountingSortStableReturnCounterReturnValueStruct*)
		para.return_value_struct).counter;
	size_t i, j;
	int A_j_key;
	for (j = 0; j < para.t1_container_elements_size; ++j)
	{
		para.t1_get_key_from_container(para.container_1, j, &A_j_key, para.data);
		++C[A_j_key];
	}
	for (i = 1; i <= para.t1_key_range; ++i)
	{
		C[i] += C[i - 1];
	}
	for (j = para.t1_container_elements_size - 1;
		j >= 0 && j < para.t1_container_elements_size; --j)
	{
		para.t1_get_key_from_container(para.container_1, j, &A_j_key, para.data);
		para.t1_copy_element_between_containers(para.container_1, j,
			para.container_2, C[A_j_key] - 1, para.data);
		--C[A_j_key];
	}
}

struct CountingSortCounter
{
	int index_p;
	int index_start;
};

/*
成(k + n)
anti-stable
in place: using no more than a constant amount of storage space 
	in addition to the original array
Parameters:
	container_1: containers of elements
	t1_key_range: range of key of element in container_1
	t1_container_elements_size: size of elements in container_1
	t1_get_key_from_container: get key from container_1
	t1_swap_element_between_containers: swap elements in container_1
8-p-2-e
*/
void CountingSortInPlace(CommonSortParameters& para)
{
	vector<CountingSortCounter> C(para.t1_key_range + 1);
	size_t i, j;
	int A_j_key;
	for (j = 0; j < para.t1_container_elements_size; ++j)
	{
		para.t1_get_key_from_container(para.container_1, j, &A_j_key, para.data);
		++C[A_j_key].index_p;
	}
	for (i = 1; i <= para.t1_key_range; ++i)
	{
		C[i].index_p += C[i - 1].index_p;
		C[i].index_start = C[i - 1].index_p;
	}
	j = 0;
	while (1)
	{
		para.t1_get_key_from_container(para.container_1, j, &A_j_key, para.data);
		if (j < C[A_j_key].index_p)
			para.t1_swap_element_between_containers(para.container_1, j,
				para.container_1, --C[A_j_key].index_p, para.data);
		else if (A_j_key >= para.t1_key_range)
			break;
		else
			j = C[A_j_key + 1].index_start;
	}
}

void GetKeyFromVectorDemo(void* vector_A, int index, void* key, void* data)
{
	*(int*)key = ((vector<int>*)vector_A)->at(index);
}

void CpyElementBetweenVectorsDemo(void* vector_A, int index_A,
	void* vector_B, int index_B, void* data)
{
	((vector<int>*)vector_B)->at(index_B) = ((vector<int>*)vector_A)->at(index_A);
}

void SwapElementBetweenVectorsDemo(void* vector_A, int index_A,
	void* vector_B, int index_B, void* data)
{
	SwapInt(((vector<int>*)vector_A)->at(index_A),
		((vector<int>*)vector_B)->at(index_B));
}

int main_counting_sort()
{

	vector<int> A, B;
	A = { 5,4,8,3,7,1,5,5,7,9,10,5,6,8 };
	CommonSortParameters para;
	para.t1_get_key_from_container = GetKeyFromVectorDemo;
	para.t1_copy_element_between_containers = CpyElementBetweenVectorsDemo;
	para.t1_swap_element_between_containers = SwapElementBetweenVectorsDemo;
	para.t1_key_range = 10;
	para.container_1 = &A;
	para.container_2 = &B;
	para.t1_container_elements_size = A.size();
	B.resize(para.t1_container_elements_size);
	CountingSortStable(para);
	CountingSortInPlace(para);
	/*
	vector<int> A, B;
	A = { 5,4,8,3,7,1,5,5,7,9,10,5,6,8 };
	CommonVectorSortParameters para;
	para.get_key_from_vector = GetKeyFromVectorDemo;
	para.cpy_element_between_vectors = CpyElementBetweenVectorsDemo;
	para.swap_element_between_vectors = SwapElementBetweenVectorsDemo;
	para.k = 10;
	para.vector_A = &A;
	para.vector_B = &B;
	para.vector_elements_size = A.size();
	B.resize(para.vector_elements_size);
	StableCountingSort(para);
		*/
	return 0;
}


