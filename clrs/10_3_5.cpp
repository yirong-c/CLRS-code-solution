#include "stdafx.h"

/*
O(n)
parameter:
	L: list; length: n
	F: free list; length: m - n
10.3-5
*/
void CompactifyList(vector<int>& key, vector<int>& prev, vector<int>& next, 
	int& L_index, int& F_index)
{
	int i, next_index;
	i = 0;
	while (L_index != -1)
	{
		SwapTemplate(key[L_index], key[i]);
		SwapTemplate(prev[L_index], prev[i]);
		SwapTemplate(next[L_index], next[i]);
		if (F_index == i)
			F_index = L_index;
		prev[next[i]] = i;
		next[prev[i]] = i;
		prev[next[L_index]] = L_index;
		next[prev[L_index]] = L_index;
		L_index = next[i];
		++i;
	}
	L_index = 0;
}

int main_10_3_5()
{
	vector<int> key, prev, next;
	int L_index, F_index;
	key = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13 };
	prev = { 9,-1,-1,1,2,6,3,8,12,13,5,4,10,11 };
	next = { -1,3,4,6,11,10,5,-1,7,0,12,13,8,9 };
	L_index = 1;
	F_index = 2;
	CompactifyList(key, prev, next, L_index, F_index);
	return 0;
}
