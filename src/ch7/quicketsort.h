#pragma once

#include "../stdafx.h"

/*
7-p-6
*/
class FuzzySortData
{
public:
	int a;//left endpoint
	int b;//right endpoint
	FuzzySortData() {}
	FuzzySortData(int a, int b)
	{
		this->a = a;
		this->b = b;
	}
};
