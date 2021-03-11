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
	(the pointer must be a memeber in the list)
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

};

/*
unsorted singly linked list
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

int main_linked_list()
{
	SinglyLinkedListElement<int>* singly_element;
	SinglyLinkedList<int> singly_list;
	singly_element = singly_list.Search(5);
	singly_list.Insert(1);
	singly_list.Insert(2);
	singly_list.Insert(3);
	singly_list.Insert(4);
	singly_list.Insert(5);
	singly_element = singly_list.Search(5);
	singly_list.Insert(6);
	singly_list.Insert(7);
	singly_list.Insert(8);
	singly_list.Delete(singly_element);
	singly_element = singly_list.Search(1);
	singly_list.Delete(singly_element);
	singly_list.Insert(6);
	singly_element = singly_list.Search(6);
	singly_list.Delete(singly_element);

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
