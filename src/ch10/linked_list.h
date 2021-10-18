#pragma once

#include "../stdafx.h"

/*
doubly linked list
*/
template <class T>
class DoublyLinkedListElement
{
public:
	T data_;
	DoublyLinkedListElement* prev_;
	DoublyLinkedListElement* next_;

	DoublyLinkedListElement(T data, DoublyLinkedListElement* prev, 
		DoublyLinkedListElement* next)
	{
		data_ = data;
		prev_ = prev;
		next_ = next;
	}

	DoublyLinkedListElement(T data, DoublyLinkedListElement* next)
	{
		data_ = data;
		prev_ = NULL;
		next_ = next;
	}

	DoublyLinkedListElement()
	{
		data_ = NULL;
		prev_ = NULL;
		next_ = NULL;
	}

	//TODO: Have not test
	void Swap(DoublyLinkedListElement* another_list)
	{
		SwapTemplate(this->prev_, another_list->prev_);
		SwapTemplate(this->next_, another_list->next_);
		this->prev_->next_ = this;
		this->next_->prev_ = this;
		another_list->prev_->next_ = another_list;
		another_list->next_->prev_ = another_list;
	}
};

/*
unsorted doubly linked list
*/
template <class T>
class DoublyLinkedList
{
public:
	DoublyLinkedListElement<T>* head_ = NULL;

	/*
	O(n)
	if element_data is not found, the function will return NULL
	*/
	DoublyLinkedListElement<T>* Search(T element_data)
	{
		DoublyLinkedListElement<T>* x;
		x = head_;
		while (x != NULL && x->data_ != element_data)
		{
			x = x->next_;
		}
		return x;
	}

	/*
	O(1)
	*/
	void Insert(T element_data)
	{
		DoublyLinkedListElement<T>* x;
		x = new DoublyLinkedListElement<T>(element_data, head_);
		if (head_ != NULL)
			head_->prev_ = x;
		head_ = x;
	}

	/*
	O(1)
	element will be deleted from memory
	element must be a member of the list
	(the pointer must be a memeber in the list)
	*/
	void Delete(DoublyLinkedListElement<T>* element)
	{
		if (element->prev_ != NULL)
			element->prev_->next_ = element->next_;
		else
			/*
			if element is not a member of the list, 
			memory leak will happened at original head_
			*/
			head_ = element->next_;
		if (element->next_ != NULL)
			element->next_->prev_ = element->prev_;
		delete element;
	}

	~DoublyLinkedList()
	{
		DoublyLinkedListElement<T>* x;
		x = head_;
		while (x != NULL)
		{
			delete x;
			x = x->next_;
		}
	}
};

/*
unsorted doubly linked list
use sentinels
*/
template <class T>
class DoublyLinkedListSentinel
{
public:
	DoublyLinkedListElement<T> nil_;//data might not be NULL

	/*
	O(n)
	if element_data is not found, the function will return nil_
	*/
	DoublyLinkedListElement<T>* Search(T element_data)
	{
		DoublyLinkedListElement<T>* x;
		x = nil_.next_;
		while (x != &nil_ && x->data_ != element_data)
		{
			x = x->next_;
		}
		return x;
	}

	/*
	O(n)
	if element_data is not found, the function will return NULL
	10.2-4
	*/
	DoublyLinkedListElement<T>* SearchOpt(T element_data)
	{
		DoublyLinkedListElement<T>* x;
		x = nil_.next_;
		nil_.data_ = element_data;
		while (x->data_ != element_data)
		{
			x = x->next_;
		}
		if (x == &nil_)
			return NULL;
		else
			return x;
	}

	/*
	O(1)
	*/
	DoublyLinkedListElement<T>* Insert(T element_data)
	{
		DoublyLinkedListElement<T>* x;
		x = new DoublyLinkedListElement<T>(element_data, &nil_, nil_.next_);
		nil_.next_->prev_ = x;
		nil_.next_ = x;
		return x;
	}

	/*
	O(1)
	*/
	DoublyLinkedListElement<T>* InsertAtEnd(T element_data)
	{
		DoublyLinkedListElement<T>* x;
		x = new DoublyLinkedListElement<T>(element_data, nil_.prev_, &nil_);
		nil_.prev_->next_ = x;
		nil_.prev_ = x;
		return x;
	}

	/*
	O(1)
	*/
	static DoublyLinkedListElement<T>* InsertAfter(T element_data, DoublyLinkedListElement<T>* after_this_element)
	{
		DoublyLinkedListElement<T>* x;
		x = new DoublyLinkedListElement<T>(element_data, 
			after_this_element, after_this_element->next_);
		x->next_->prev_ = x;
		x->prev_->next_ = x;
		return x;
	}

	/*
	O(1)
	element will be deleted from memory
	element must be a member of the list
	(the pointer must be a memeber in the list)
	*/
	static void Delete(DoublyLinkedListElement<T>* element)
	{
		element->prev_->next_ = element->next_;
		element->next_->prev_ = element->prev_;
		delete element;
	}

	DoublyLinkedListSentinel()
	{
		nil_.next_ = nil_.prev_ = &nil_;
	}

	~DoublyLinkedListSentinel()
	{
		DoublyLinkedListElement<T>* x;
		x = nil_.next_;
		while (x != &nil_)
		{
			delete x;
			x = x->next_;
		}
	}
};

/*
singly linked list
*/
template <class T>
class SinglyLinkedListElement
{
public:
	T data_;
	SinglyLinkedListElement* next_;

	SinglyLinkedListElement(T data, SinglyLinkedListElement* next)
	{
		data_ = data;
		next_ = next;
	}

	SinglyLinkedListElement(T data)
	{
		data_ = data;
		next_ = NULL;
	}
};

/*
unsorted singly linked list
10.2-5
*/
template <class T>
class SinglyLinkedList
{
public:
	SinglyLinkedListElement<T>* head_ = NULL;

	/*
	O(n)
	if element_data is not found, the function will return NULL
	*/
	SinglyLinkedListElement<T>* Search(T element_data)
	{
		SinglyLinkedListElement<T>* x;
		x = head_;
		while (x != NULL && x->data_ != element_data)
		{
			x = x->next_;
		}
		return x;
	}

	/*
	O(1)
	10.2-1
	*/
	void Insert(T element_data)
	{
		/*
		SinglyLinkedListElement<T>* x;
		x = new SinglyLinkedListElement<T>(element_data, head_);
		head_ = x;
		*/
		head_ = new SinglyLinkedListElement<T>(element_data, head_);
	}

	/*
	O(1)
	element will be deleted from memory
	element must be a member of the list
	(the pointer must be a memeber in the list)
	order MIGHT be broken (happen when the last element is delete)
	Data of pointers will be changed
	10.2-1
	*/
	void Delete(SinglyLinkedListElement<T>* element)
	{
		SinglyLinkedListElement<T>* next;
		if (element->next_ != NULL)
		{
			next = element->next_;
			memcpy(&(element->data_), &(next->data_), sizeof(T));
			element->next_ = next->next_;
		}
		else
		{
			//order will be broken
			next = head_;
			memcpy(&(element->data_), &(next->data_), sizeof(T));
			head_ = next->next_;
		}
		delete next;
	}

	/*
	O(n)
	element will be deleted from memory
	element must be a member of the list
	(the pointer must be a memeber in the list)
	order will NOT be broken
	Data of pointers will NOT be changed
	*/
	void DeleteLinear(SinglyLinkedListElement<T>* element)
	{
		SinglyLinkedListElement<T>* x, *before;
		x = head_;
		before = NULL;
		while (x != element)
		{
			before = x;
			x = x->next_;
		}
		if (before)
			before->next_ = x->next_;
		else
			head_ = x->next_;
		delete x;
	}

	/*
	O(n)
	10.2-7
	*/
	void reverse()
	{
		SinglyLinkedListElement<T> *last, *next;
		next = head_;
		last = NULL;
		while (next != NULL)
		{
			head_ = next;
			next = head_->next_;
			head_->next_ = last;
			last = head_;
		}
	}

	~SinglyLinkedList()
	{
		SinglyLinkedListElement<T>* x;
		x = head_;
		while (x != NULL)
		{
			delete x;
			x = x->next_;
		}
	}
};

/*
unsorted singly linked list
use sentinels
10.2-5
*/
template <class T>
class SinglyLinkedListSentinel
{
public:
	SinglyLinkedListElement<T> nil_ = NULL;//data might not be NULL

	/*
	O(n)
	if element_data is not found, the function will return nil_
	*/
	SinglyLinkedListElement<T>* Search(T element_data)
	{
		SinglyLinkedListElement<T>* x;
		x = nil_.next_;
		while (x != &nil_ && x->data_ != element_data)
		{
			x = x->next_;
		}
		return x;
	}

	/*
	O(n)
	if element_data is not found, the function will return NULL
	*/
	SinglyLinkedListElement<T>* SearchOpt(T element_data)
	{
		SinglyLinkedListElement<T>* x;
		x = nil_.next_;
		nil_.data_ = element_data;
		while (x->data_ != element_data)
		{
			x = x->next_;
		}
		if (x == &nil_)
			return NULL;
		else
			return x;
	}

	/*
	O(1)
	*/
	void Insert(T element_data)
	{
		nil_.next_ = 
			new SinglyLinkedListElement<T>(element_data, nil_.next_);
	}

	/*
	O(1)
	element will be deleted from memory
	element must be a member of the list
	(the pointer must be a memeber in the list)
	order MIGHT be broken (happen when the last element is delete)
	Data of pointers will be changed
	10.2-1
	*/
	void Delete(SinglyLinkedListElement<T>* element)
	{
		SinglyLinkedListElement<T>* next;
		if (element->next_ != &nil_)
		{
			next = element->next_;
			memcpy(&(element->data_), &(next->data_), sizeof(T));
			element->next_ = next->next_;
		}
		else
		{
			//order will be broken
			next = nil_.next_;
			memcpy(&(element->data_), &(next->data_), sizeof(T));
			nil_.next_ = next->next_;
		}
		delete next;
	}

	/*
	O(n)
	element will be deleted from memory
	element must be a member of the list
	(the pointer must be a memeber in the list)
	order will NOT be broken
	Data of pointers will NOT be changed
	*/
	void DeleteLinear(SinglyLinkedListElement<T>* element)
	{
		SinglyLinkedListElement<T>* x, *before;
		x = nil_.next_;
		before = NULL;
		while (x != element)
		{
			before = x;
			x = x->next_;
		}
		if (before)
			before->next_ = x->next_;
		else
			nil_.next_ = x->next_;
		delete x;
	}

	SinglyLinkedListSentinel()
	{
		nil_.next_ = &nil_;
	}

	~SinglyLinkedListSentinel()
	{
		SinglyLinkedListElement<T>* x;
		x = nil_.next_;
		while (x != &nil_)
		{
			delete x;
			x = x->next_;
		}
	}
};

/*
O(1)
sets S1 and S2 might be destroyed
10.2-6
*/
template <typename T>
void DoublyLinkedListSentinelUnion
	(DoublyLinkedListElement<T>* s1_first,
	DoublyLinkedListElement<T>* s1_last,
	DoublyLinkedListElement<T>* s2_first,
	DoublyLinkedListElement<T>* s2_last,
	DoublyLinkedListSentinel<T>& set_return)
{
	s1_first->prev_->next_ = s1_last->next_;
	s1_last->next_->prev_ = s1_first->prev_;
	s2_first->prev_->next_ = s2_last->next_;
	s2_last->next_->prev_ = s2_first->prev_;
	
	s1_last->next_ = s2_first;
	s2_first->prev_ = s1_last;

	s2_last->next_ = (&set_return.nil_)->next_;
	s1_first->prev_ = &set_return.nil_;

	(&set_return.nil_)->next_->prev_ = s2_last;
	(&set_return.nil_)->next_ = s1_first;
}
