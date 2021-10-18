#include "../stdafx.h"
#include "../ch2/insertion_sort.h"
#include "bucket_sort.h"

/*
average-case running time: O(n)
worst-case running time: O(n^2)
interval of elements of A: [0, 1)
*/
void BucketSort(vector<float>& A)
{
	vector< list<float> > B;
	size_t size;
	int i, j;
	list<float>::iterator iterator_list, iterator_list_end;
	size = A.size();
	B.resize(size);
	for (i = 0; i < size; ++i)
		B[size * A[i]].push_back(A[i]);
	for (i = 0, j = 0; i < size; ++i)
	{
		InsertionSortList(B[i]);
		for (iterator_list = B[i].begin(), iterator_list_end = B[i].end();
			iterator_list != iterator_list_end; ++iterator_list)
		{
			A[j] = *iterator_list;
			++j;
		}
	}
}

/*
O(n)
element will full into bucket according to key of element
Parameters:
	t1_container_elements_size: size of container 1
	container_1: store elements; vector< "type of element" >
			it is a good idea to use: vector< "struct of the type of element with size" >
	container_2: bucket to store elements in container_1;
			vector< list< "type of element" > >;
			should be resize before the function is called
	t1_get_key_from_container: get bucket (container_2) index of element
	t1_copy_element_between_containers: add element from container_1
			into a bucket in container_2
*/
void BucketSortClassify(CommonSortParameters& para)
{
	int i, bucket_index;
	for (i = 0; i < para.t1_container_elements_size; ++i)
	{
		para.t1_get_key_from_container(para.container_1, i, &bucket_index, para.data);
		para.t1_copy_element_between_containers(para.container_1, i,
			para.container_2, bucket_index, para.data);
	}
}

int main_bucket_sort()
{
	vector<float> A;
	A = { .78,.17,.39,.26,.72,.94,.21,.12,.23,.68 };
	BucketSort(A);

	return 0;
}
