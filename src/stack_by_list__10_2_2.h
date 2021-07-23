#pragma once

#include "stdafx.h"
#include "linked_list.h"

/*
10.2-2
*/
template <class T>
class StackImpleBySinglyLinkedList
{
	SinglyLinkedList<T> list_;

public:
	bool StackEmpty()
	{
		if (list_.head_ == NULL)
			return true;
		else
			return false;
	}

	bool StackFull()
	{
		//never overflow
		return false;
	}

	//do NOT check overflow
	void Push(T element)
	{
		/*
		list_.Insert(element);
		*/
		list_.head_ =
			new SinglyLinkedListElement<T>(element, list_.head_);
	}

	//do NOT check underflow
	T Pop()
	{
		/*
		T data;
		data = list_.head_->data_;
		list_.Delete(list_.head_);
		return data;
		*/
		SinglyLinkedListElement<T>* first;
		T data;
		first = list_.head_;
		data = first->data_;
		list_.head_ = first->next_;
		delete first;
		return data;
	}

	//check overflow
	void PushCheck(T element)
	{
		//never overflow
		Push(element);
		/*
		if (StackFull())
			throw "overflow";
		else
			Push(element);
		*/
	}

	//check underflow
	T PopCheck()
	{
		if (StackEmpty())
			throw "underflow";
		else
			return Pop();
	}
};
