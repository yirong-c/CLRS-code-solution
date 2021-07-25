#ifndef _10_P_2__MERGEABLE_MIN_HEAP_H
#define _10_P_2__MERGEABLE_MIN_HEAP_H

#include "linked_list.h"

template <class T>
class MergeableMinHeap
{
public:
    class HeapBinaryTreeNode
    {
    public:
        int key_;
        T data_;

        HeapBinaryTreeNode(int key)
        {
            key_ = key;
            data_ = NULL;
        }

        HeapBinaryTreeNode(int key, T data)
        {
            key_ = key;
            data_ = data;
        }
    };

    typedef HeapBinaryTreeNode* ListElementDataPointer;
    typedef DoublyLinkedListSentinel< ListElementDataPointer > List;
    typedef DoublyLinkedListElement< ListElementDataPointer > ListElement;

    List* list_;

    MergeableMinHeap()
    {
        list_ = new List();
    }

    ~MergeableMinHeap()
    {
        delete list_;
    }

    /*
    O(n)
    */
    void MinHeapify(const int index, ListElement * const element_at_index)
    {
        int i, smallest_element_index;
        ListElement *element_at_left_child, *element_at_right_child, 
        *smallest_element;
        //init smallest_element_index and smallest_element
        smallest_element_index = index;
        smallest_element = element_at_index;
        //find pointer of element of left child
        element_at_left_child = element_at_index;
        for (i = index; i < BinaryTreeLeft(index); ++i)
        {
            element_at_left_child = element_at_left_child->next_;
            if (element_at_left_child == &list_->nil_)
            {
                //pointer of element of list has reached nil_
                return;
            }
        }
        //test left child
        if (element_at_left_child->data_ != NULL && 
        element_at_left_child->data_->key_ < smallest_element->data_->key_)
        {
            smallest_element_index = BinaryTreeLeft(index);
            smallest_element = element_at_left_child;
        }
        //find pointer of element of right child
        element_at_right_child = element_at_left_child->next_;
        if (element_at_right_child == &list_->nil_)
        {
            //pointer of element of list has reached nil_
            if (smallest_element_index != index)
            {
                //swap smallest_element and element_at_index in list
                SwapTemplate(smallest_element->data_, element_at_index->data_);
            }
            return;//TODO
        }
        //test right child
        if (element_at_right_child->data_ != NULL && 
        element_at_right_child->data_->key_ < smallest_element->data_->key_)
        {
            smallest_element_index = BinaryTreeLeft(index);
            smallest_element = element_at_right_child;
        }
        if (smallest_element_index != index)
        {
            //swap smallest_element and element_at_index in list
            SwapTemplate(smallest_element->data_, element_at_index->data_);
            MinHeapify(smallest_element_index, smallest_element);
        }
    }

    /*
    O(n)
    */
    void MinHeapCheckParents(const int index, 
        ListElement * const element_at_index)
    {
        int i, parent_element_index, child_element_index;
        ListElement *parent_element, *child_element;
        //init parent_element_index and parent_element
        parent_element_index = index;
        parent_element = element_at_index;
        //compare to key of parents
        while (parent_element_index > 0)
        {
            child_element = parent_element;
            child_element_index = parent_element_index;
            parent_element_index = BinaryTreeParent(parent_element_index);
            for (i = child_element_index; i > parent_element_index; --i)
            {
                parent_element = parent_element->prev_;
            }
            if (parent_element->data_->key_ > child_element->data_->key_)
            {
                SwapTemplate(parent_element->data_, child_element->data_);   
            }
            else
            {
                break;
            }
        }
    }

    void HeapDecreaseKey(const int index, 
        ListElement * const element_at_index, const int key)
    {
        if (key > element_at_index->data_->key_)
		    throw "new key is greater than current key";
        element_at_index->data_->key_ = key;
        this->MinHeapCheckParents(index, element_at_index);
    }

    void MinHeapInsert(ListElementDataPointer list_element_data)
    {
        list_->InsertAtEnd(list_element_data);
        this->MinHeapCheckParents(list_->length - 1, list_->nil_.prev_);
    }

    ListElementDataPointer Minimum()
    {
        return list_->nil_.next_->data_;
    }

    ListElementDataPointer ExtractMin()
    {
        ListElementDataPointer min;
        min = this->Minimum();
        list_->nil_.next_->data_ = list_->nil_.prev_->data_;
        list_->Delete(list_->nil_.prev_);
        MinHeapify(0, list_->nil_.next_);
        return min;
    }

};

#endif