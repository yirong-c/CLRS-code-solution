#include "stdafx.h"

struct ElementInSet 
{
    int key;
    void* satellite_data;
};

typedef ElementInSet** DirectAddressTable;

ElementInSet* DirectAddressSearch(DirectAddressTable table, int key)
{
    return table[key];
}

void DirectAddressInsert(DirectAddressTable table, ElementInSet* element)
{
    table[element->key] = element;
}

void DirectAddressDelete(DirectAddressTable table, ElementInSet* element)
{
    table[element->key] = NULL;
}

int main()
{
    ElementInSet e1;
    e1.key = 1;
    e1.satellite_data = (void*)1;
    ElementInSet e2;
    e2.key = 2;
    e2.satellite_data = (void*)2;
    ElementInSet e3;
    e3.key = 3;
    e3.satellite_data = (void*)3;
    ElementInSet e4;
    e4.key = 4;
    e4.satellite_data = (void*)4;

    ElementInSet* table[5];
    DirectAddressInsert(table, &e3);
    DirectAddressInsert(table, &e2);
    DirectAddressInsert(table, &e1);
    DirectAddressInsert(table, &e4);

    ElementInSet* result;
    result = DirectAddressSearch(table, 1);
    result = DirectAddressSearch(table, 2);
    result = DirectAddressSearch(table, 3);
    result = DirectAddressSearch(table, 4);

    DirectAddressDelete(table, &e1);
    DirectAddressDelete(table, &e2);
    DirectAddressDelete(table, &e3);
    DirectAddressDelete(table, &e4);

    result = DirectAddressSearch(table, 1);
    result = DirectAddressSearch(table, 2);
    result = DirectAddressSearch(table, 3);
    result = DirectAddressSearch(table, 4);

    return 0;
}
