#pragma once

#include "stdafx.h"
#include "element_class.h"

int LinearSelect(vector<int>& A, int begin_index, int end_index, int i_index);
int LinearSelectMedian(vector<int>& A, int begin_index, 
	int end_index, int& pivot_left_index, int& pivot_right_index);
int LinearSelect(vector< ElementWithKey* >& A, int begin_index,
	int end_index, int i_index);
