#pragma once

class Allocater
{
	typedef struct FreeElement
	{
		FreeElement* next;
	} FreeElement;

	void* memory_addr_;
	int single_element_size_;
	FreeElement* free_list_head_;

public:
	Allocater(int single_element_size, int element_num);
	~Allocater();
	void* AllocateObject();
	void FreeObject(void* pointer);
};
