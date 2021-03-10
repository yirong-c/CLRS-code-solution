#pragma once

#include "stdafx.h"

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
	DoublyLinkedListElement<T> nil_;

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
	O(1)
	*/
	void Insert(T element_data)
	{
		DoublyLinkedListElement<T>* x;
		x = new DoublyLinkedListElement<T>(element_data, &nil_, nil_.next_);
		nil_.next_->prev_ = x;
		nil_.next_ = x;
	}

	/*
	O(1)
	element will be deleted from memory
	element must be a member of the list
	*/
	void Delete(DoublyLinkedListElement<T>* element)
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

int main_linked_list()
{
	DoublyLinkedListElement<int>* element;
	DoublyLinkedListSentinel<int> list;
//	DoublyLinkedList<int> list;
	element = list.Search(5);
	list.Insert(1);
	list.Insert(2);
	list.Insert(3);
	list.Insert(4);
	list.Insert(5);
	list.Insert(6);
	list.Insert(7);
	list.Insert(8);
	element = list.Search(5);
	list.Delete(element);
	list.Insert(6);

	return 0;
}
