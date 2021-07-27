#include "linked_list.h"

struct ElementInSet 
{
    int key;
    void* satellite_data;
};

DoublyLinkedListElement<ElementInSet*>* DirectAddressSearch
    (vector<DoublyLinkedListSentinel<ElementInSet*>>& table, int key)
{
    return table[key].nil_.next_;
}

void DirectAddressInsert
    (vector<DoublyLinkedListSentinel<ElementInSet*>>& table, 
    ElementInSet* element)
{
    table[element->key].Insert(element);
}

void DirectAddressDelete
    (vector<DoublyLinkedListSentinel<ElementInSet*>>& table, 
    DoublyLinkedListElement<ElementInSet*>* element)
{
    table[element->data_->key].Delete(element);
}

int main()
{
    ElementInSet e0;
    e0.key = 1;
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

    DoublyLinkedListElement<ElementInSet*>* result;

    vector<DoublyLinkedListSentinel<ElementInSet*>> table(4);
    DirectAddressInsert(table, &e1);
    DirectAddressInsert(table, &e3);
    DirectAddressInsert(table, &e0);
    DirectAddressInsert(table, &e2);

    result = DirectAddressSearch(table, 0);
    result = DirectAddressSearch(table, 1);
    result = DirectAddressSearch(table, 2);
    result = DirectAddressSearch(table, 3);

    DirectAddressDelete(table, result);

    result = DirectAddressSearch(table, 0);
    result = DirectAddressSearch(table, 1);
    result = DirectAddressSearch(table, 2);
    result = DirectAddressSearch(table, 3);

    return 0;
}
