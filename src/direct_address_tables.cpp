#include "stdafx.h"

struct ElementInSet 
{
    int key;
    void* satellite_data;
};

ElementInSet* DirectAddressSearch(vector<ElementInSet*>& table, int key)
{
    return table[key];
}

void DirectAddressInsert(vector<ElementInSet*>& table, ElementInSet* element)
{
    table[element->key] = element;
}

void DirectAddressDelete(vector<ElementInSet*>& table, ElementInSet* element)
{
    table[element->key] = NULL;
}

/*
11.1-1
O(n)
*/
ElementInSet* FindMaxElement(vector<ElementInSet*> table)
{
    int i;
    ElementInSet* max;
    for (i = 0; i < table.size(); ++i)
    {
        if (table[i] != NULL)
            max = table[i];
    }
    return max;
}

int main()
{
    ElementInSet e0;
    e0.key = 0;
    e0.satellite_data = (void*)1111;
    ElementInSet e1;
    e1.key = 1;
    e1.satellite_data = (void*)1;
    ElementInSet e2;
    e2.key = 2;
    e2.satellite_data = (void*)2;
    ElementInSet e3;
    e3.key = 3;
    e3.satellite_data = (void*)3;

    ElementInSet* result;

    vector<ElementInSet*> table;
    table.resize(4);
    DirectAddressInsert(table, &e1);
    result = FindMaxElement(table);
    DirectAddressInsert(table, &e0);
    result = FindMaxElement(table);
    DirectAddressInsert(table, &e3);
    result = FindMaxElement(table);
    DirectAddressInsert(table, &e2);
    result = FindMaxElement(table);

    result = DirectAddressSearch(table, 0);
    result = DirectAddressSearch(table, 1);
    result = DirectAddressSearch(table, 2);
    result = DirectAddressSearch(table, 3);

    DirectAddressDelete(table, &e0);
    DirectAddressDelete(table, &e1);
    DirectAddressDelete(table, &e2);
    DirectAddressDelete(table, &e3);

    result = DirectAddressSearch(table, 0);
    result = DirectAddressSearch(table, 1);
    result = DirectAddressSearch(table, 2);
    result = DirectAddressSearch(table, 3);

    return 0;
}
