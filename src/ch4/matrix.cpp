#include "matrix.h"

Array2D::Array2D(int i, int j)
{
	array_size = i * j;
	array_i_size = i;
	array_j_size = j;
	pointer = new int[array_size]();
	//printf("pointer:%p\n", pointer);
}

Array2D::Array2D(int i, int j, int* p)
{
	array_size = i * j;
	array_i_size = i;
	array_j_size = j;
	pointer = new int[array_size];
	memcpy(pointer, p, array_size * sizeof(int));
}

Array2D::~Array2D()
{
	delete[] pointer;
}

void Matrix::MatrixIndexSize::Devide(int i, int j)
{
	int length_half;
	if (i == 1)
	{
		row_length /= 2;
	}
	else if (i == 2)
	{
		length_half = row_length / 2;
		row_base_index += length_half;
		row_length -= length_half;
	}
	if (j == 1)
	{
		col_length /= 2;
	}
	else if (j == 2)
	{
		length_half = col_length / 2;
		col_base_index += length_half;
		col_length -= length_half;
	}
}

void Matrix::SetMatrixIndexSize(int row_base_index, int col_base_index, int row_length, int col_length)
{
	matrix_index_size.row_base_index = row_base_index;
	matrix_index_size.col_base_index = col_base_index;
	matrix_index_size.row_length = row_length;
	matrix_index_size.col_length = col_length;
}

void Matrix::SetMatrixIndexSizeExtend(int row_base_index, int col_base_index,
	int row_length, int col_length)
{
	matrix_index_size.row_base_index = row_base_index;
	matrix_index_size.col_base_index = col_base_index;
	double exp_double;
	exp_double = log(row_length > col_length ?
		row_length : col_length) / log(2);
	exp_double = exp_double > (int)exp_double ?
		(int)exp_double + 1 : (int)exp_double;
	matrix_index_size.row_length = pow(2.0, exp_double);
	matrix_index_size.col_length = matrix_index_size.row_length;
}

Matrix::Matrix(int i, int j) : Array2D(i, j)
{
	actual_row_length = i;
	actual_col_length = j;
	SetMatrixIndexSizeExtend(0, 0, i, j);
}

Matrix::Matrix(int i, int j, int do_not_extend) : Array2D(i, j)
{
	actual_row_length = i;
	actual_col_length = j;
	if (do_not_extend)
		SetMatrixIndexSize(0, 0, i, j);
	else
		SetMatrixIndexSizeExtend(0, 0, i, j);
}

Matrix::Matrix(int i, int j, int* p) : Array2D(i, j, p)
{
	actual_row_length = i;
	actual_col_length = j;
	SetMatrixIndexSizeExtend(0, 0, i, j);
}

Matrix::Matrix(int i, int j, int* p, int do_not_extend) : Array2D(i, j, p)
{
	actual_row_length = i;
	actual_col_length = j;
	if (do_not_extend)
		SetMatrixIndexSize(0, 0, i, j);
	else
		SetMatrixIndexSizeExtend(0, 0, i, j);
}

void Matrix::SetAddMatrixMember(int i, int j, int value)
{
	int array_i, array_j;
	array_i = matrix_index_size.row_base_index + i;
	array_j = matrix_index_size.col_base_index + j;
	SetArrayMemberCheckOverflow(array_i, array_j, GetArrayMemberCheckOverflow(array_i, array_j) + value);
}

void Matrix::SetSubMatrixMember(int i, int j, int value)
{
	int array_i, array_j;
	array_i = matrix_index_size.row_base_index + i;
	array_j = matrix_index_size.col_base_index + j;
	SetArrayMemberCheckOverflow(array_i, array_j, GetArrayMemberCheckOverflow(array_i, array_j) - value);
}

void Matrix::GetMatrixIndexSizeCopy(MatrixIndexSize& copy)
{
	memcpy(&copy, &matrix_index_size, sizeof(MatrixIndexSize));
}

void Matrix::SetMatrixIndexSizeCopy(const MatrixIndexSize& copy)
{
	memcpy(&matrix_index_size, &copy, sizeof(MatrixIndexSize));
}

void Matrix::SetMatrixIndexSizeCopyDevideObject(const MatrixIndexSize& copy, int i, int j)
{
	memcpy(&matrix_index_size, &copy, sizeof(MatrixIndexSize));
	matrix_index_size.Devide(i, j);
}

Matrix* Matrix::GetNewMatrixDevideObjectCopy(int i, int j)
{
	MatrixIndexSize matrix_index_size_copy_this_original;
	Matrix* devide_matrix;
	int loop_i, loop_j;
	this->GetMatrixIndexSizeCopy(matrix_index_size_copy_this_original);
	matrix_index_size.Devide(i, j);
	devide_matrix = new Matrix(matrix_index_size.row_length,
		matrix_index_size.col_length, 1);
	for (loop_i = 0; loop_i < matrix_index_size.row_length; ++loop_i)
		for (loop_j = 0; loop_j < matrix_index_size.col_length; ++loop_j)
			devide_matrix->SetMatrixMember(loop_i, loop_j,
				this->GetMatrixMember(loop_i, loop_j));
	this->SetMatrixIndexSizeCopy(matrix_index_size_copy_this_original);
	return devide_matrix;
}

Matrix* Matrix::GetNewMatrixDevideObjectAdditionSubtractionCopy(int add_or_sub,
	int i1, int j1, int i2, int j2)
{
	MatrixIndexSize matrix_index_size_copy_this_original;
	Matrix* devide_matrix;
	int loop_i, loop_j;
	this->GetMatrixIndexSizeCopy(matrix_index_size_copy_this_original);
	matrix_index_size.Devide(i1, j1);
	devide_matrix = new Matrix(matrix_index_size.row_length,
		matrix_index_size.col_length, 1);
	for (loop_i = 0; loop_i < matrix_index_size.row_length; ++loop_i)
		for (loop_j = 0; loop_j < matrix_index_size.col_length; ++loop_j)
			devide_matrix->SetMatrixMember(loop_i, loop_j,
				this->GetMatrixMember(loop_i, loop_j));
	this->SetMatrixIndexSizeCopyDevideObject(matrix_index_size_copy_this_original,
		i2, j2);
	for (loop_i = 0; loop_i < matrix_index_size.row_length; ++loop_i)
		for (loop_j = 0; loop_j < matrix_index_size.col_length; ++loop_j)
			add_or_sub ?
			devide_matrix->SetAddMatrixMember(loop_i, loop_j,
				this->GetMatrixMember(loop_i, loop_j)) :
			devide_matrix->SetSubMatrixMember(loop_i, loop_j,
				this->GetMatrixMember(loop_i, loop_j));
	this->SetMatrixIndexSizeCopy(matrix_index_size_copy_this_original);
	return devide_matrix;
}

void Matrix::SetAddSubMatrix(int add_or_sub, Matrix& matrix_b)
{
	int loop_i, loop_j;
	for (loop_i = 0; loop_i < matrix_index_size.row_length; ++loop_i)
		for (loop_j = 0; loop_j < matrix_index_size.col_length; ++loop_j)
			add_or_sub ?
			this->SetAddMatrixMember(loop_i, loop_j,
				matrix_b.GetMatrixMember(loop_i, loop_j)) :
			this->SetSubMatrixMember(loop_i, loop_j,
				matrix_b.GetMatrixMember(loop_i, loop_j));
}






