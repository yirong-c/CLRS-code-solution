#pragma once
#include "../stdafx.h"

class Array2D
{
public:
	int* pointer;
	int array_size;
	int array_i_size;
	int array_j_size;

	Array2D(int i, int j);
	Array2D(int i, int j, int* p);
	~Array2D();

	inline int GetArrayMember(int i, int j)
	{
		return *(pointer + i * array_i_size + j);
	}
	inline void SetArrayMember(int i, int j, int value)
	{
		*(pointer + i * array_i_size + j) = value;
	}
	inline int GetArrayMemberCheckOverflow(int i, int j)
	{
		if (i >= array_i_size || j >= array_j_size)
			return 0;
		return *(pointer + i * array_i_size + j);
	}
	inline void SetArrayMemberCheckOverflow(int i, int j, int value)
	{
		if (i >= array_i_size || j >= array_j_size)
			return;
		*(pointer + i * array_i_size + j) = value;
	}
	inline int& GetArrayMemberRef(int i, int j)
	{
		return *(pointer + i * array_i_size + j);
	}
};

class Matrix : public Array2D
{
public:
	class MatrixIndexSize
	{
	public:
		int row_base_index;
		int col_base_index;
		int row_length;
		int col_length;

		void Devide(int i, int j);
	};

	int actual_row_length;
	int actual_col_length;
	MatrixIndexSize matrix_index_size;

	void SetMatrixIndexSize(int row_base_index, int col_base_index,
		int row_length, int col_length);
	void SetMatrixIndexSizeExtend(int row_base_index, int col_base_index,
		int row_length, int col_length);
	Matrix(int i, int j);
	Matrix(int i, int j, int do_not_extend);
	Matrix(int i, int j, int* p);
	Matrix(int i, int j, int* p, int do_not_extend);

	inline int& GetMatrixMemberRef(int i, int j)
	{
		return GetArrayMemberRef(matrix_index_size.row_base_index + i,
			matrix_index_size.col_base_index + j);
	}
	inline int GetMatrixMember(int i, int j)
	{
		return GetArrayMemberCheckOverflow(matrix_index_size.row_base_index + i,
			matrix_index_size.col_base_index + j);
	}
	inline void SetMatrixMember(int i, int j, int value)
	{
		SetArrayMemberCheckOverflow(matrix_index_size.row_base_index + i,
			matrix_index_size.col_base_index + j, value);
	}

	void SetAddMatrixMember(int i, int j, int value);
	void SetSubMatrixMember(int i, int j, int value);
	void GetMatrixIndexSizeCopy(MatrixIndexSize& copy);
	void SetMatrixIndexSizeCopy(const MatrixIndexSize& copy);
	void SetMatrixIndexSizeCopyDevideObject(const MatrixIndexSize& copy,
		int i, int j);
	Matrix* GetNewMatrixDevideObjectCopy(int i, int j);
	Matrix* GetNewMatrixDevideObjectAdditionSubtractionCopy(int add_or_sub,
		int i1, int j1, int i2, int j2);
	void SetAddSubMatrix(int add_or_sub, Matrix& matrix_b);
};


