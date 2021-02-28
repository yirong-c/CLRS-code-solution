#pragma once

#include "stdafx.h"
#include "common_vector_sort_parameters.h"

void CountingSortStableOld(CommonVectorSortParameters& para);
void CountingSortStable(CommonSortParameters& para);
struct CountingSortStableReturnCounterReturnValueStruct
{
	//should be resize before function is called
	vector<int>* counter;
};
void CountingSortStableReturnCountingIndex(CommonSortParameters& para);
