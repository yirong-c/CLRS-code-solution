#pragma once

#include "stdafx.h"
#include "common_sort_parameters.h"
#include "element_class.h"

void MergeSort(CommonSortParameters& para);
void MergeSort(vector<int>& A, int p, int r);
void MergeSortReverse(vector<int>& A, int p, int r);
void MergeSort(vector< ElementWithKey* >& A, int p, int r);
