#ifndef _10_P_2__MERGEABLE_MIN_HEAP_H
#define _10_P_2__MERGEABLE_MIN_HEAP_H

#include "linked_list.h"

template <class T>
class MergeableMinHeapUnsortedList
{
public:
    class ListElementData
    {
    public:
        int key_;
        T data_;

        ListElementData(int key)
        {
            key_ = key;
            data_ = NULL;
        }

        ListElementData(int key, T data)
        {
            key_ = key;
            data_ = data;
        }
    };

    typedef DoublyLinkedListSentinel< ListElementData* > List;
    typedef DoublyLinkedListElement< ListElementData* > ListElement;

    List* list_;

    /*
    MakeHeap
    O(1)
    */
    MergeableMinHeapUnsortedList()
    {
        list_ = new List();
    }

    ~MergeableMinHeapUnsortedList()
    {
        delete list_;
    }

    /*
    O(1)
    */
    void Insert(ListElementData* const list_element_data)
    {
        list_->Insert(list_element_data);
    }

    /*
    O(n)
    */
    ListElement* Minimum()
    {
        ListElement *traversing_element, *smallest_element;
        int smallest_key;
        traversing_element = list_->nil_.next_;
        smallest_element = NULL;
        smallest_key = INT_MAX;
        while (traversing_element != &list_->nil_)
        {
            if (traversing_element->data_->key_ < smallest_key)
            {
                smallest_key = traversing_element->data_->key_;
                smallest_element = traversing_element;
            }
            traversing_element = traversing_element->next_;
        }
        return smallest_element;
    }

    /*
    O(n)
    */
    ListElementData* ExtractMin()
    {
        ListElement* smallest_element;
        ListElementData* smallest_element_data;
        smallest_element = this->Minimum();
        smallest_element_data = smallest_element->data_;
        list_->Delete(smallest_element);
        return smallest_element_data;
    }

    /*
    O(n)
    */
    void Union(MergeableMinHeapUnsortedList& another_heap)
    {
        this->list_->nil_.prev_->next_ = another_heap.list_->nil_.next_;
        this->list_->nil_.prev_->next_->prev_ = this->list_->nil_.prev_;
        this->list_->nil_.prev_ = another_heap.list_->nil_.prev_;
        this->list_->nil_.prev_->next_ = &this->list_->nil_;
        another_heap.list_->nil_.next_ = NULL;
        another_heap.list_->nil_.prev_ = NULL;
    }
};

template <class T>
class MergeableMinHeapSortedList
{
public:
    class ListElementData
    {
    public:
        int key_;
        T data_;

        ListElementData(int key)
        {
            key_ = key;
            data_ = NULL;
        }

        ListElementData(int key, T data)
        {
            key_ = key;
            data_ = data;
        }
    };

    typedef DoublyLinkedListSentinel< ListElementData* > List;
    typedef DoublyLinkedListElement< ListElementData* > ListElement;

    List* list_;

    /*
    MakeHeap
    O(1)
    */
    MergeableMinHeapSortedList()
    {
        list_ = new List();
    }

    ~MergeableMinHeapSortedList()
    {
        delete list_;
    }

    /*
    O(n)
    */
    void Insert(ListElementData* const list_element_data)
    {
        ListElement *last_traversing_element;
        last_traversing_element = &list_->nil_;
        while (last_traversing_element->next_ != &list_->nil_ &&
                last_traversing_element->next_->data_->key_ 
                < list_element_data->key_)
        {
            last_traversing_element = last_traversing_element->next_;
        }
        list_->InsertAfter(list_element_data, last_traversing_element);
    }

    /*
    O(1)
    */
    ListElement* Minimum()
    {
        return list_->nil_.next_;
    }

    /*
    O(1)
    */
    ListElementData* ExtractMin()
    {
        ListElement* smallest_element;
        ListElementData* smallest_element_data;
        smallest_element = this->Minimum();
        smallest_element_data = smallest_element->data_;
        list_->Delete(smallest_element);
        return smallest_element_data;
    }

    /*
    O(n)
    */
    void Union(MergeableMinHeapSortedList& another_heap)
    {
        ListElement *last_traversing_element_a, *last_traversing_element_b;
        last_traversing_element_a = &this->list_->nil_;
        last_traversing_element_b = &another_heap.list_->nil_;
        while (last_traversing_element_b->next_ != &another_heap.list_->nil_)
        {
            if (last_traversing_element_a->next_ == &list_->nil_ ||
                last_traversing_element_a->next_->data_->key_ > 
                last_traversing_element_b->next_->data_->key_)
            {
                last_traversing_element_b = last_traversing_element_b->next_;
                this->list_->InsertAfter(last_traversing_element_b->data_, 
                        last_traversing_element_a);
            }
            else
            {
                last_traversing_element_a = last_traversing_element_a->next_;
            }
        }
    }
};


#endif