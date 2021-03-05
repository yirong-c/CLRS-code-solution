#pragma once

#include "stdafx.h"

int LinearSelect(vector<int>& A, int begin_index, int end_index, int i_index);
int LinearSelectReturnPivotIndex(vector<int>& A, int begin_index, int end_index,
	int i_index, int& pivot_left_index, int& pivot_right_index);
int LinearSelectMedianReturnPivotIndex(vector<int>& A, int begin_index, 
	int end_index, int& pivot_left_index, int& pivot_right_index);
