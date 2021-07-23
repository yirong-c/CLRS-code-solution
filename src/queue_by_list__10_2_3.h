#pragma once

#include "stdafx.h"
#include "linked_list.h"

/*
10.2-3
*/
template <class T>
class QueueImpleBySinglyLinkedList
{
	SinglyLinkedList<T> list_;
	SinglyLinkedListElement<T>* tail_ = NULL;

public:
	//do NOT check overflow
	void Enqueue(T element_data)
	{
		SinglyLinkedListElement<T>* new_element;
		new_element = new SinglyLinkedListElement<T>(element_data);
		if (tail_)
			tail_->next_ = new_element;
		else
			list_.head_ = new_element;
		tail_ = new_element;
	}

	//do NOT check underflow
	T Dequeue()
	{
		T data;
		SinglyLinkedListElement<T>* element;
		element = list_.head_;
		data = element->data_;
		list_.head_ = element->next_;
		delete element;
		return data;
	}

	bool QueueEmpty()
	{
		if (list_.head_ == NULL)
			return true;
		else
			return false;
	}

	bool QueueFull()
	{
		//never overflow
		return false;
	}

	/*
	check overflow
	10.1-4
	*/
	void EnqueueCheck(T element)
	{
		//never overflow
		Enqueue(element);
		/*
		if (QueueFull())
			throw "overflow";
		else
			Enqueue(element);
		*/
	}

	/*
	check underflow
	10.1-4
	*/
	T DequeueCheck()
	{
		if (QueueEmpty())
			throw "underflow";
		return Dequeue();
	}
};
