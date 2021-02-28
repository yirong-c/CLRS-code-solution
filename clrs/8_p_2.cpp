#include "stdafx.h"
#include "common_vector_sort_parameters.h"

/*
O(n)
stable
*/
void SortingBitKey12(CommonVectorSortParameters& para)
{
	int index_0, index_1;
	size_t j;
	bool A_j_key;
	index_0 = index_1 = -1;
	for (j = 0; j < para.vector_elements_size; ++j)
	{
		para.get_key_from_vector(para.vector_A, j, &A_j_key, para.data);
		index_1+=!A_j_key;
	}
	for (j = 0; j < para.vector_elements_size; ++j)
	{
		para.get_key_from_vector(para.vector_A, j, &A_j_key, para.data);
		A_j_key ?
			para.cpy_element_between_vectors(para.vector_A, j,
				para.vector_B, ++index_1, para.data) :
			para.cpy_element_between_vectors(para.vector_A, j,
				para.vector_B, ++index_0, para.data);
	}
}

/*
O(n)
in place: using no more than a constant amount of storage space
	in addition to the original array
*/
void SortingBitKey13(CommonVectorSortParameters& para)
{
	int size_0, index_1;
	size_t j;
	bool A_j_key;
	size_0 = 0;
	for (j = 0; j < para.vector_elements_size; ++j)
	{
		para.get_key_from_vector(para.vector_A, j, &A_j_key, para.data);
		size_0 += !A_j_key;
	}
	index_1 = para.vector_elements_size;
	j = 0;
	while (j < size_0 && index_1 > size_0)
	{
		para.get_key_from_vector(para.vector_A, j, &A_j_key, para.data);
		if (A_j_key)
			para.swap_element_between_vectors(para.vector_A, j, 
				para.vector_A, --index_1, para.data);
		else
			++j;
	}
}

/*
stable
in place: using no more than a constant amount of storage space
	in addition to the original array
*/
void SortingBitKey23(CommonVectorSortParameters& para)
{
	int i, j;
	size_t size;
	bool A_j_key, A_i_key;
	size = para.vector_elements_size;
	for (j = 1; j < size; ++j)
	{
		memcpy(para.temp_element_1,
			para.get_element_address_from_vector(para.vector_A, j, para.data),
			para.element_size);
		para.get_key_from_vector(para.vector_A, j, &A_j_key, para.data);
		i = j - 1;
		while (i >= 0)
		{
			para.get_key_from_vector(para.vector_A, i, &A_i_key, para.data);
			if (A_i_key <= A_j_key)
				break;
			para.cpy_element_between_vectors(para.vector_A, i,
					para.vector_A, i + 1, para.data);
			i--;
		}
		memcpy(para.get_element_address_from_vector(para.vector_A, i + 1, para.data),
			para.temp_element_1,
			para.element_size);
	}
}

struct SortingBitParametersData
{
	int and_factor_get_key;
};

void SortingBitGetKeyFromVector(void* vector_A, int index_A, void* key, void* data)
{
	*(bool*)key = (((vector<int>*)vector_A)->at(index_A) & 
		((SortingBitParametersData*)data)->and_factor_get_key);
}

void SortingBitCpyElementBetweenVectors(void* vector_A, int index_A,
	void* vector_B, int index_B, void* data)
{
	((vector<int>*)vector_B)->at(index_B) = ((vector<int>*)vector_A)->at(index_A);
}

void SortingBitSwapElementBetweenVectors(void* vector_A, int index_A,
	void* vector_B, int index_B, void* data)
{
	SwapInt(((vector<int>*)vector_A)->at(index_A), 
		((vector<int>*)vector_B)->at(index_B));
}

void* SortingBitGetElementAddressFromVector(void* vector_A, int index_A, void* data)
{
	return &((vector<int>*)vector_A)->at(index_A);
}

//8-p-2-e in "counting_sort.cpp"

int main_8_p_2()
{
	int temp_element_1;
	vector<int> A, B;
	SortingBitParametersData data;
	CommonVectorSortParameters para;
	para.data = &data;
	para.get_key_from_vector = SortingBitGetKeyFromVector;
	para.cpy_element_between_vectors = SortingBitCpyElementBetweenVectors;
	para.swap_element_between_vectors = SortingBitSwapElementBetweenVectors;
	para.get_element_address_from_vector = SortingBitGetElementAddressFromVector;
	para.temp_element_1 = &temp_element_1;
	para.k = 1;
	para.vector_A = &A;
	para.vector_B = &B;
	data.and_factor_get_key = 1;
	A = { 5,4,8,3,7,1,5,5,7,9,10,5,6,8 };
	para.vector_elements_size = A.size();
	para.element_size = sizeof(int);
	//23
	SortingBitKey23(para);
	//13
	SortingBitKey13(para);
	//12
	B.resize(para.vector_elements_size);
	for (data.and_factor_get_key = 1; data.and_factor_get_key < 30; data.and_factor_get_key <<= 1)
	{
		SortingBitKey12(para);
		A = B;
	}

	return 0;
}
