#include "stdafx.h"
#include "matrix.h"

void SquareMatrixMultiply(Matrix& A, Matrix& B, Matrix& C)
{
	int i, j, k, c;
	for (i = 0; i < C.array_i_size; ++i)
		for (j = 0; j < C.array_j_size; ++j)
		{
			for (k = 0, c = 0; k < C.array_j_size; ++k)
				c += A.GetMatrixMember(i, k) * B.GetMatrixMember(k, j);
			C.SetMatrixMember(i, j, c);
		}
}

void SquareMatrixMultiplyRecursive(Matrix& A, Matrix& B, Matrix& C)
{
	int a, b;
	Matrix::MatrixIndexSize a_matrix_index_size, b_matrix_index_size, 
		c_matrix_index_size;
	A.GetMatrixIndexSizeCopy(a_matrix_index_size);
	B.GetMatrixIndexSizeCopy(b_matrix_index_size);
	C.GetMatrixIndexSizeCopy(c_matrix_index_size);
	if (c_matrix_index_size.row_length <= 1)
	{
		a = A.GetMatrixMember(0, 0);
		b = B.GetMatrixMember(0, 0);
		C.SetAddMatrixMember(0, 0, a * b);
	}
	else
	{
		//C11
		A.SetMatrixIndexSizeCopyDevideObject(a_matrix_index_size, 1, 1);
		B.SetMatrixIndexSizeCopyDevideObject(b_matrix_index_size, 1, 1);
		C.SetMatrixIndexSizeCopyDevideObject(c_matrix_index_size, 1, 1);
		SquareMatrixMultiplyRecursive(A, B, C);
		A.SetMatrixIndexSizeCopyDevideObject(a_matrix_index_size, 1, 2);
		B.SetMatrixIndexSizeCopyDevideObject(b_matrix_index_size, 2, 1);
		C.SetMatrixIndexSizeCopyDevideObject(c_matrix_index_size, 1, 1);
		SquareMatrixMultiplyRecursive(A, B, C);
		//C12
		A.SetMatrixIndexSizeCopyDevideObject(a_matrix_index_size, 1, 1);
		B.SetMatrixIndexSizeCopyDevideObject(b_matrix_index_size, 1, 2);
		C.SetMatrixIndexSizeCopyDevideObject(c_matrix_index_size, 1, 2);
		SquareMatrixMultiplyRecursive(A, B, C);
		A.SetMatrixIndexSizeCopyDevideObject(a_matrix_index_size, 1, 2);
		B.SetMatrixIndexSizeCopyDevideObject(b_matrix_index_size, 2, 2);
		C.SetMatrixIndexSizeCopyDevideObject(c_matrix_index_size, 1, 2);
		SquareMatrixMultiplyRecursive(A, B, C);
		//C21
		A.SetMatrixIndexSizeCopyDevideObject(a_matrix_index_size, 2, 1);
		B.SetMatrixIndexSizeCopyDevideObject(b_matrix_index_size, 1, 1);
		C.SetMatrixIndexSizeCopyDevideObject(c_matrix_index_size, 2, 1);
		SquareMatrixMultiplyRecursive(A, B, C);
		A.SetMatrixIndexSizeCopyDevideObject(a_matrix_index_size, 2, 2);
		B.SetMatrixIndexSizeCopyDevideObject(b_matrix_index_size, 2, 1);
		C.SetMatrixIndexSizeCopyDevideObject(c_matrix_index_size, 2, 1);
		SquareMatrixMultiplyRecursive(A, B, C);
		//C22
		A.SetMatrixIndexSizeCopyDevideObject(a_matrix_index_size, 2, 1);
		B.SetMatrixIndexSizeCopyDevideObject(b_matrix_index_size, 1, 2);
		C.SetMatrixIndexSizeCopyDevideObject(c_matrix_index_size, 2, 2);
		SquareMatrixMultiplyRecursive(A, B, C);
		A.SetMatrixIndexSizeCopyDevideObject(a_matrix_index_size, 2, 2);
		B.SetMatrixIndexSizeCopyDevideObject(b_matrix_index_size, 2, 2);
		C.SetMatrixIndexSizeCopyDevideObject(c_matrix_index_size, 2, 2);
		SquareMatrixMultiplyRecursive(A, B, C);
	}
}

void SquareMatrixMultiplyRecursiveEntrance(Matrix& A, Matrix& B, Matrix& C)
{
	Matrix::MatrixIndexSize a_matrix_index_size, b_matrix_index_size,
		c_matrix_index_size;
	A.GetMatrixIndexSizeCopy(a_matrix_index_size);
	B.GetMatrixIndexSizeCopy(b_matrix_index_size);
	C.GetMatrixIndexSizeCopy(c_matrix_index_size);
	SquareMatrixMultiplyRecursive(A, B, C);
	A.SetMatrixIndexSizeCopy(a_matrix_index_size);
	B.SetMatrixIndexSizeCopy(b_matrix_index_size);
	C.SetMatrixIndexSizeCopy(c_matrix_index_size);
}

void SquareMatrixMultiplyStrassen(Matrix& A, Matrix& B, Matrix& C)
{
	int a, b;
	Matrix::MatrixIndexSize a_matrix_index_size, b_matrix_index_size,
		c_matrix_index_size;
	Matrix* s1, * s2, * s3, * s4, * s5, * s6, * s7, * s8, * s9, * s10,
		* p1, * p2, * p3, * p4, * p5, * p6, * p7;
	A.GetMatrixIndexSizeCopy(a_matrix_index_size);
	B.GetMatrixIndexSizeCopy(b_matrix_index_size);
	C.GetMatrixIndexSizeCopy(c_matrix_index_size);
	if (c_matrix_index_size.row_length <= 1)
	{
		a = A.GetMatrixMember(0, 0);
		b = B.GetMatrixMember(0, 0);
		C.SetAddMatrixMember(0, 0, a * b);
	}
	else
	{
		s1 = B.GetNewMatrixDevideObjectAdditionSubtractionCopy(0, 1, 2, 2, 2);
		s2 = A.GetNewMatrixDevideObjectAdditionSubtractionCopy(1, 1, 1, 1, 2);
		s3 = A.GetNewMatrixDevideObjectAdditionSubtractionCopy(1, 2, 1, 2, 2);
		s4 = B.GetNewMatrixDevideObjectAdditionSubtractionCopy(0, 2, 1, 1, 1);
		s5 = A.GetNewMatrixDevideObjectAdditionSubtractionCopy(1, 1, 1, 2, 2);
		s6 = B.GetNewMatrixDevideObjectAdditionSubtractionCopy(1, 1, 1, 2, 2);
		s7 = A.GetNewMatrixDevideObjectAdditionSubtractionCopy(0, 1, 2, 2, 2);
		s8 = B.GetNewMatrixDevideObjectAdditionSubtractionCopy(1, 2, 1, 2, 2);
		s9 = A.GetNewMatrixDevideObjectAdditionSubtractionCopy(0, 1, 1, 2, 1);
		s10 = B.GetNewMatrixDevideObjectAdditionSubtractionCopy(1, 1, 1, 1, 2);
		p1 = new Matrix(s1->matrix_index_size.row_length,
			s1->matrix_index_size.col_length);
		p2 = new Matrix(s1->matrix_index_size.row_length,
			s1->matrix_index_size.col_length);
		p3 = new Matrix(s1->matrix_index_size.row_length,
			s1->matrix_index_size.col_length);
		p4 = new Matrix(s1->matrix_index_size.row_length,
			s1->matrix_index_size.col_length);
		p5 = new Matrix(s1->matrix_index_size.row_length,
			s1->matrix_index_size.col_length);
		p6 = new Matrix(s1->matrix_index_size.row_length,
			s1->matrix_index_size.col_length);
		p7 = new Matrix(s1->matrix_index_size.row_length,
			s1->matrix_index_size.col_length);
		//P1
		A.SetMatrixIndexSizeCopyDevideObject(a_matrix_index_size, 1, 1);
		SquareMatrixMultiplyStrassen(A, *s1, *p1);
		//P2
		B.SetMatrixIndexSizeCopyDevideObject(b_matrix_index_size, 2, 2);
		SquareMatrixMultiplyStrassen(*s2, B, *p2);
		//P3
		B.SetMatrixIndexSizeCopyDevideObject(b_matrix_index_size, 1, 1);
		SquareMatrixMultiplyStrassen(*s3, B, *p3);
		//P4
		A.SetMatrixIndexSizeCopyDevideObject(a_matrix_index_size, 2, 2);
		SquareMatrixMultiplyStrassen(A, *s4, *p4);
		//P5
		SquareMatrixMultiplyStrassen(*s5, *s6, *p5);
		//P6
		SquareMatrixMultiplyStrassen(*s7, *s8, *p6);
		//P7
		SquareMatrixMultiplyStrassen(*s9, *s10, *p7);
		//C11
		C.SetMatrixIndexSizeCopyDevideObject(c_matrix_index_size, 1, 1);
		C.SetAddSubMatrix(1, *p5);
		C.SetAddSubMatrix(1, *p4);
		C.SetAddSubMatrix(0, *p2);
		C.SetAddSubMatrix(1, *p6);
		//C12
		C.SetMatrixIndexSizeCopyDevideObject(c_matrix_index_size, 1, 2);
		C.SetAddSubMatrix(1, *p1);
		C.SetAddSubMatrix(1, *p2);
		//C21
		C.SetMatrixIndexSizeCopyDevideObject(c_matrix_index_size, 2, 1);
		C.SetAddSubMatrix(1, *p3);
		C.SetAddSubMatrix(1, *p4);
		//C21
		C.SetMatrixIndexSizeCopyDevideObject(c_matrix_index_size, 2, 2);
		C.SetAddSubMatrix(1, *p5);
		C.SetAddSubMatrix(1, *p1);
		C.SetAddSubMatrix(0, *p3);
		C.SetAddSubMatrix(0, *p7);
		delete s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, p1, p2, p3, p4, p5, p6, p7;
		A.SetMatrixIndexSizeCopy(a_matrix_index_size);
		B.SetMatrixIndexSizeCopy(b_matrix_index_size);
		C.SetMatrixIndexSizeCopy(c_matrix_index_size);
	}
}

void SquareMatrixMultiplyStrassenEntrance(Matrix& A, Matrix& B, Matrix& C)
{
	SquareMatrixMultiplyStrassen(A, B, C);
}

int main_square_matrix_multiply()
{
	int arr[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	Matrix A(3, 3, arr), B(3, 3, arr), C(3, 3);
	//int a[4] = { 1,3,7,5 };
	//int b[4] = { 6,8,4,2 };
	//Matrix A(2, 2, a), B(2, 2, b), C(2, 2);
	SquareMatrixMultiplyStrassenEntrance(A, B, C);
	//SquareMatrixMultiplyRecursiveEntrance(A, B, C);
	//SquareMatrixMultiply(A, B, C);
	return 0;
}
