#include "stdafx.h"
#include "matrix.h"

class YoungTableCoordinate
{
public:
	int row;
	int col;
	YoungTableCoordinate(){}
	YoungTableCoordinate(int row, int col)
	{
		this->row = row;
		this->col = col;
	}
	bool CheckMatrixOverflow(Matrix& matrix)
	{
		return matrix.actual_row_length <= row || matrix.actual_col_length <= col ||
			row < 0 || col < 0;
	}
	bool operator ==(const YoungTableCoordinate& c2)
	{
		return this->row == c2.row && this->col == c2.col;
	}
	bool operator !=(const YoungTableCoordinate& c2)
	{
		return !(this->row == c2.row && this->col == c2.col);
	}
};

//O(m + n)
void YoungTableauify(Matrix& matrix, YoungTableCoordinate& coordinate)
{
	YoungTableCoordinate under, right, smallest;
	under = right = smallest = coordinate;
	under.row++;
	right.col++;
	if (!under.CheckMatrixOverflow(matrix) &&
		matrix.GetMatrixMember(under.row, under.col) < 
		matrix.GetMatrixMember(smallest.row, smallest.col))
		smallest = under;
	if (!right.CheckMatrixOverflow(matrix) &&
		matrix.GetMatrixMember(right.row, right.col) <
		matrix.GetMatrixMember(smallest.row, smallest.col))
		smallest = right;
	if (smallest != coordinate)
	{
		SwapInt(matrix.GetMatrixMemberRef(smallest.row, smallest.col),
			matrix.GetMatrixMemberRef(coordinate.row, coordinate.col));
		YoungTableauify(matrix, smallest);
	}
}

//O(m + n)
int YoungTableauExtractMin(Matrix& matrix)
{
	int min_val;
	YoungTableCoordinate coordinate;
	if (matrix.array_size < 1)
		throw "underflow";
	coordinate.row = 0;
	coordinate.col = 0;
	int& min = matrix.GetMatrixMemberRef(0, 0);
	int& last = matrix.GetMatrixMemberRef(matrix.actual_row_length - 1, 
		matrix.actual_col_length - 1);
	min_val = min;
	min = last;
	last = INT_MAX;
	YoungTableauify(matrix, coordinate);
	return min_val;
}

//O(m + n)
void YoungTableauDecreaseKey(Matrix& matrix, YoungTableCoordinate& coordinate, 
	int key)
{
	YoungTableCoordinate left, above;
	int left_val, above_val, flag;
	if (key > matrix.GetMatrixMember(coordinate.row, coordinate.col))
		throw "new key is greater than current key";
	while (1)
	{
		flag = 0;
		left = above = coordinate;
		above.row = coordinate.row - 1;
		left.col = coordinate.col - 1;
		if (!above.CheckMatrixOverflow(matrix))
		{
			above_val = matrix.GetMatrixMember(above.row, above.col);
			if (above_val > key)
			{
				flag = 1;
			}
		}
		if (!left.CheckMatrixOverflow(matrix))
		{
			left_val = matrix.GetMatrixMember(left.row, left.col);
			if (left_val > key)
			{
				if(!(flag && left_val < above_val))
					flag = 2;
			}
		}
		if (flag == 1)
		{
			matrix.SetMatrixMember(coordinate.row, coordinate.col, above_val);
			coordinate = above;
		}
		else if (flag == 2)
		{
			matrix.SetMatrixMember(coordinate.row, coordinate.col, left_val);
			coordinate = left;
		}
		else
		{
			break;
		}
	}
	matrix.SetMatrixMember(coordinate.row, coordinate.col, key);
}

//O(m + n)
void YoungTableauInsertNonFull(Matrix& matrix, int key)
{
	YoungTableCoordinate coordinate(matrix.actual_row_length - 1,
		matrix.actual_col_length - 1);
	YoungTableauDecreaseKey(matrix, coordinate, key);
}

//O(n^3)
void YoungTableauSquareMatrixSort(Matrix& matrix, int row_col_size, 
	vector<int>& sorted)
{
	int i, smallest_index_col, smallest_val, loop_val;
	vector<int> indexs(row_col_size, 0);
	while (1)
	{
		for (i = 0, smallest_val = INT_MAX; i < row_col_size; ++i)
		{
			if (indexs[i] < row_col_size)
			{
				loop_val = matrix.GetMatrixMember(indexs[i], i);
				if (loop_val < smallest_val)
				{
					smallest_index_col = i;
					smallest_val = loop_val;
				}
			}
		}
		if (smallest_val != INT_MAX)
		{
			indexs[smallest_index_col]++;
			sorted.push_back(smallest_val);
		}
		else
		{
			break;
		}
	}
}

//O(m + n)
bool YoungTableauFindNum(Matrix& matrix, int find_key, YoungTableCoordinate& pos)
{
	int key;
	pos.row = matrix.actual_row_length - 1;
	pos.col = 0;
	while (1)
	{
		if (pos.CheckMatrixOverflow(matrix))
			return false;
		key = matrix.GetMatrixMember(pos.row, pos.col);
		if (find_key > key)
			pos.col++;
		else if (find_key < key)
			pos.row--;
		else
			return true;
	}
}

int main_6_p_3()
{
	int ret;
	int arr[16] = { 1,2,3,4,5,6,7,8,9,10,11,INT_MAX,13,14,INT_MAX,INT_MAX };
	Matrix matrix(4, 4, arr);

	YoungTableCoordinate coordinate;
	ret = YoungTableauFindNum(matrix, 15, coordinate);

	vector<int> sorted;
	YoungTableauSquareMatrixSort(matrix, 4, sorted);

	YoungTableauInsertNonFull(matrix, 8);

	return 0;
}