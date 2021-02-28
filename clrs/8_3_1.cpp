//radix_sort

#include "stdafx.h"
#include "counting_sort.h"

struct StableCountingSortParametersData
{
	int digit;
};

void GetKeyFromVectorConstCharP(void* vector_A, int index, void* key, void* data)
{
	*(int*)key = ((vector<const char*>*)vector_A)->at(index)
		[((StableCountingSortParametersData*)data)->digit] - 0x41;
}

void CpyElementBetweenVectorsConstCharP(void* vector_A, int index_A,
	void* vector_B, int index_B, void* data)
{
	((vector<const char*>*)vector_B)->at(index_B) = ((vector<const char*>*)vector_A)->at(index_A);
}

int main_8_3_1()
{
	StableCountingSortParametersData data;
	vector<const char*> A, B;
	A = { "COW","DOG","SEA","RUG","ROW","MOB","BOX","TAB","BAR","EAR","TAR",
		"DIG","BIG","TEA","NOW","FOX" };
	CommonVectorSortParameters para;
	para.get_key_from_vector = GetKeyFromVectorConstCharP;
	para.cpy_element_between_vectors = CpyElementBetweenVectorsConstCharP;
	para.k = 25;
	para.data = &data;
	para.vector_A = &A;
	para.vector_B = &B;
	para.vector_elements_size = A.size();
	B.resize(para.vector_elements_size);
	//radix_sort
	for (data.digit = 2; data.digit >= 0; --data.digit)
	{
		CountingSortStableOld(para);
		A = B;
	}
	return 0;
}


