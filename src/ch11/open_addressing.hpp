#ifndef _OPEN_ADDRESSING_HPP
#define _OPEN_ADDRESSING_HPP

#include "../stdafx.h"

template <class T>
class OpenAddressing
{
public:
    typedef int (*HashFunction)(int key, int i);
private:
    class Element
    {
    public:
        int key_;
        T data_;
        enum {NIL, DELETED, OCCUPIED} flag_;

        Element()
        {
            flag_ = NIL;
        }
    };
    vector< Element > table_;
    HashFunction hash_function_;
    int slot_num_;
public:
    OpenAddressing(const int slot_num, const HashFunction hash_function)
    : table_(slot_num)
    {
        hash_function_ = hash_function;
        slot_num_ = slot_num;
    }

    int HashInsert(int key, T data)
    {
        int i, hash;
        for (i = 0; i < slot_num_; ++i)
        {
            hash = hash_function_(key, i);
            if (table_[hash].flag_ != Element::OCCUPIED)
            {
                table_[hash].flag_ = Element::OCCUPIED;
                table_[hash].key_ = key;
                table_[hash].data_ = data;
                return hash;
            }
        }
        return -1;
        //throw "hash table overflow";
    }

    int HashSearch(const int key)
    {
        int i, hash;
        for (i = 0; i < slot_num_; ++i)
        {
            hash = hash_function_(key, i);
            if (table_[hash].flag_ == Element::NIL)
            {
                return -1;
            }
            if (table_[hash].flag_ == Element::OCCUPIED &&
                table_[hash].key_ == key)
            {
                return hash;
            }
        }
        return -1;
    }

    T HashGet(const int hash)
    {
        return table_[hash].data_;
    }

    /*
    11.4-2
    */
    void HashDelete(const int hash)
    {
        table_[hash].flag_ = Element::DELETED;
    }

};

#endif