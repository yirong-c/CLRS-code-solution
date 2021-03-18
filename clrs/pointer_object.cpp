#include "stdafx.h"
#include "stack_by_list__10_2_2.h"
#include "pointer_object.h"

Allocater::Allocater(int single_element_size, int element_num)
{
	void *it, *last;
	int total_size;

	single_element_size_ = single_element_size;
	if (single_element_size < sizeof(FreeElement))
		throw "single_element_size too small";
	total_size = single_element_size * element_num;
	memory_addr_ = malloc(total_size);
	if (!memory_addr_)
		throw "malloc failed";

	last = NULL;
	for (it = memory_addr_ + total_size - single_element_size;
		it >= memory_addr_; it = it - single_element_size)
	{
		((FreeElement*)it)->next = (FreeElement*)last;
		last = it;
	}

	free_list_head_ = (FreeElement*)memory_addr_;
}

Allocater::~Allocater()
{
	free(memory_addr_);
}

void* Allocater::AllocateObject()
{
	void* pointer;
	if (!free_list_head_)
		throw "out of space";
	pointer = free_list_head_;
	free_list_head_ = free_list_head_->next;
	return pointer;
}

void Allocater::FreeObject(void* pointer)
{
	((FreeElement*)pointer)->next = free_list_head_;
	free_list_head_ = (FreeElement*)pointer;
}
