#pragma once

#include "stdafx.h"
#include "quicketsort.h"

int Partition(vector<int>& A, int p, int r);
int RandomizedPartition(vector<int>& A, int p, int r);
int HoarePartition(vector<int>& A, int p, int r);
void PartitionSpecificPivotIndex(vector<int>& A, int p, int r,
	int pivot_index, int& pivot_left_index, int& pivot_right_index);
void FuzzySortPartition(vector<FuzzySortData>& A,
	int p, int r, FuzzySortData& overlap_interval, int& q, int& t);
void PartitionSpecificPivotValue(vector<int>& A, int begin_index, int end_index,
	int pivot_val, int& pivot_left_index, int& pivot_right_index);
