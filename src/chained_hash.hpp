#ifndef _CHAINED_HASH_HPP
#define _CHAINED_HASH_HPP

#include "linked_list.h"

template <class T>
class ChainedHash
{
public:
    typedef int (*HashFunction)(int);
    class Element
    {
    public:
        int key_;
        T data_;
        DoublyLinkedListElement< Element* >* list_element_;

        Element(int key)
        {
            key_ = key;
            data_ = NULL;
            list_element_ = NULL;
        }

        Element(int key, T data)
        {
            key_ = key;
            data_ = data;
            list_element_ = NULL;
        }
    };
private:
    typedef DoublyLinkedListElement< Element* > ListElement;
    typedef DoublyLinkedListSentinel< Element* > List;
    vector<List> table_;
    HashFunction hash_function_;
public:
    ChainedHash(const int slot_num, const HashFunction hash_function)
        : table_(slot_num) 
    {
        hash_function_ = hash_function;
    }

    void ChainedHashInsert(Element* const element)
    {
        int hash;
        hash = hash_function_(element->key_);
        element->list_element_ = 
            table_[hash].Insert(element);
    }

    Element* ChainedHashSearch(const int key)
    {
        int hash;
        ListElement* x;
        hash = hash_function_(key);
        List& list = table_[hash];
		x = list.nil_.next_;
        while (true)
		{
            if (x == &list.nil_)
                return NULL;
            if (x->data_->key_ == key)
                return x->data_;
			x = x->next_;
		}
    }

    void ChainedHashDelete(Element* const element)
    {
        List::Delete(element->list_element_);
        element->list_element_ = NULL;
    }
};

#endif