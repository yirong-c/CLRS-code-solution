#pragma once

#include "../stdafx.h"
#include "quicketsort.h"
#include "../element_class.h"

int Partition(vector<int>& A, int p, int r);
int RandomizedPartition(vector<int>& A, int p, int r);
int HoarePartition(vector<int>& A, int p, int r);
void FuzzySortPartition(vector<FuzzySortData>& A,
	int p, int r, FuzzySortData& overlap_interval, int& q, int& t);
void PartitionSpecificPivotIndex(vector<int>& A, int p, int r,
	int pivot_index, int& pivot_left_index, int& pivot_right_index);
void PartitionSpecificPivotValue(vector<int>& A, int begin_index, int end_index,
	int pivot_val, int& pivot_left_index, int& pivot_right_index);
void PartitionSpecificPivotIndex(vector< ElementWithKey* >& A, int p, int r,
	int pivot_index, int& pivot_left_index, int& pivot_right_index);
void PartitionSpecificPivotValue(vector< ElementWithKey* >& A, int begin_index,
	int end_index, int pivot_key_val, int& pivot_left_index, int& pivot_right_index);
