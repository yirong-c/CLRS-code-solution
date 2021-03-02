#pragma once

#include "stdafx.h"

int QuicksortRandomizedPartition(vector<int>& A, int p, int r);
void QuicksortPartitionSpecificPivotIndexReturnQAndT(vector<int>& A, int p, int r,
	int pivot_index, int& q, int& t);
