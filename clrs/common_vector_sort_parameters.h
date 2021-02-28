#pragma once

#include "stdafx.h"

struct CommonVectorSortParameters
{
	//int GetKeyFromVectorDemo(void* vector_A, int index_A, void* key, void* data)
	typedef void (*GetKeyFromVector)(void* vector_A, int index_A, 
		void* key, void* data);
	//void CpyElementBetweenVectorsDemo(void* vector_A, int index_A, void* vector_B, int index_B, void* data)
	typedef void (*CpyElementBetweenVectors)(void* vector_A, int index_A, 
		void* vector_B, int index_B, void* data);
	//void SwapElementBetweenVectorsDemo(void* vector_A, int index_A, void* vector_B, int index_B, void* data)
	typedef void (*SwapElementBetweenVectors)(void* vector_A, int index_A, 
		void* vector_B, int index_B, void* data);
	//void* GetElementAddressFromVectorDemo(void* vector_A, int index_A, void* data)
	typedef void* (*GetElementAddressFromVector)(void* vector_A, int index_A, 
		void* data);

	//only suit for vector A or B
	GetKeyFromVector get_key_from_vector;//get key (to sort) from vector A
	CpyElementBetweenVectors cpy_element_between_vectors;//copy the element from vector A to vector B
	SwapElementBetweenVectors swap_element_between_vectors;//swap the elements
	GetElementAddressFromVector get_element_address_from_vector;//get the address of the element from vector A

	void* data;//custom data
	int k;//range of key [0, k]

	void* vector_A;//input
	void* vector_B;//output: should be resize before Sort Function is called
	size_t vector_elements_size;//size of vector A and B
	size_t element_size;//size of struct of element in vector A and B
	void* temp_element_1;/*temporary data for the sort function; 
					init with the space with size of element in the vector A and B*/
};

struct CommonSortParameters
{
	struct IteratorGroup2Member
	{
		void* begin;
		void* end;
	};
	typedef void* (*Type1GetElementAddressFromContainer)
		(void* container, int index, void* data);
	typedef void (*Type1GetKeyFromContainer)
		(void* container, int index, void* key, void* data);
	typedef void (*Type1CopyElementBetweenContainers)
		(void* container_A, int index_A, void* container_B, int index_B, void* data);
	typedef void (*Type1SwapElementBetweenContainers)
		(void* container_A, int index_A, void* container_B, int index_B, void* data);
	typedef void* (*Type1GetContainerIterators)
		(void* container, bool reverse,
			void* iterator_begin, void* iterator_end, void* data);
	typedef void (*Type2GetKeyFromContainer)
		(void* iterator, void* key, void* data);
	typedef void (*Type2CopyElementBetweenContainers)
		(void* iterator_A, void* container_B, int index_B, void* data);

	//func-type 1: get address of element from container
	Type1GetElementAddressFromContainer t1_get_element_address_from_container;
	//func-type 1: get key from container
	Type1GetKeyFromContainer t1_get_key_from_container;
	//func-type 1: copy the element from container A to container B
	Type1CopyElementBetweenContainers t1_copy_element_between_containers;
	//func-type 1: swap the elements between containers
	Type1SwapElementBetweenContainers t1_swap_element_between_containers;
	//func-type 1: get iterators of container
	Type1GetContainerIterators t1_get_container_iterators;
	//func-type 2: get key from container by using iterator
	Type2GetKeyFromContainer t2_get_key_from_container;
	//func-type 2: copy the element from container A to container B
	Type2CopyElementBetweenContainers t2_copy_element_between_containers;

	//custom data
	void* data;
	//return value struct
	void* return_value_struct;

	//var-type 1: size of container
	size_t t1_container_elements_size;
	//var-type 1: size of struct of element in container
	size_t t1_element_size;
	//var-type 1: size of iterator of container
	size_t t1_iterator_size;
	//var-type 1: range of key [0, t1_key_range]
	int t1_key_range;
	//var-type 1: temporary data for the sort function
	void* t1_temp;
	//var-type 1: iterator group
	IteratorGroup2Member t1_iterator_group;

	//container 1
	void* container_1;
	//container 2
	void* container_2;
};
