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

#endif