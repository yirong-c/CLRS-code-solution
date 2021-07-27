#include "stdafx.h"

bool BitVectorSearch(vector<bool>& table, int key)
{
    return table[key];
}

void BitVectorInsert(vector<bool>& table, int key)
{
    table[key] = true;
}

void BitVectorDelete(vector<bool>& table, int key)
{
    table[key] = false;
}

int main()
{
    vector<bool> table(4);
    bool result;

    result = BitVectorSearch(table, 0);
    result = BitVectorSearch(table, 1);
    result = BitVectorSearch(table, 2);
    result = BitVectorSearch(table, 3);

    BitVectorInsert(table, 0);
    BitVectorInsert(table, 3);

    result = BitVectorSearch(table, 0);
    result = BitVectorSearch(table, 1);
    result = BitVectorSearch(table, 2);
    result = BitVectorSearch(table, 3);

    BitVectorDelete(table, 0);
    BitVectorDelete(table, 1);
    BitVectorDelete(table, 2);
    BitVectorDelete(table, 3);

    result = BitVectorSearch(table, 0);
    result = BitVectorSearch(table, 1);
    result = BitVectorSearch(table, 2);
    result = BitVectorSearch(table, 3);

    return 0;
}
