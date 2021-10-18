#include "../element_class.h"
#include "selection.h"

class ElementWithCounterPart : public ElementWithKey
{
public:
	ElementWithCounterPart* greater_;//counter
	ElementWithCounterPart* lower_;//self key
	bool left_over_;
	ElementWithCounterPart(int key) : ElementWithKey(key) {}
	ElementWithCounterPart(int key, bool left_over, 
		ElementWithCounterPart* greater, ElementWithCounterPart* lower) :
		ElementWithKey(key)
	{
		greater_ = greater;
		lower_ = lower;
		left_over_ = left_over;
	}
};

int SelectSmallOrderStatistic(vector<ElementWithCounterPart*>& A, int i)
{
	int size, size_sub_even, is_left_over_exist, j, j2, ret;
	size = A.size();
	if (size < 2 * i)
		return LinearSelect((vector<ElementWithKey*>&)A, 0, size - 1, i - 1);
	size_sub_even = size / 2;
	is_left_over_exist = size % 2;
	vector<ElementWithCounterPart*> sub_array;
	sub_array.reserve(size_sub_even + is_left_over_exist);
	//divide + compare
	for (j = 0; j < size_sub_even; ++j)
	{
		if (A[j]->key_ < A[size_sub_even + j]->key_)
		{
			sub_array.push_back(new ElementWithCounterPart(
				A[j]->key_, false, 
				A[size_sub_even + j], A[j]));
		}
		else
		{
			sub_array.push_back(new ElementWithCounterPart(
				A[size_sub_even + j]->key_, false, 
				A[j], A[size_sub_even + j]));
		}
	}
	if (is_left_over_exist)
		sub_array.push_back(new ElementWithCounterPart(
			A[size - 1]->key_, true,
			NULL, A[size - 1]));
	//recursively
	SelectSmallOrderStatistic(sub_array, i);
	//swap
	for (j = 0, j2 = 0; j + j2 < size_sub_even + is_left_over_exist; )
	{
		if (sub_array[j + j2]->left_over_)
		{
			A[size_sub_even + j + j2] = sub_array[j + j2]->lower_;
			delete sub_array[j + j2];
			++j2;
		}
		else
		{
			A[j] = sub_array[j + j2]->greater_;
			A[size_sub_even + j + j2] = sub_array[j + j2]->lower_;
			delete sub_array[j + j2];
			++j;
		}
	}
	//select
	sub_array.resize(2 * i);
	for (j = 0; j < i; ++j)
	{
		sub_array[j] = A[j];
		sub_array[i + j] = A[size_sub_even + j];
	}
	ret = LinearSelect((vector<ElementWithKey*>&)sub_array, 0, 2 * i - 1, i - 1);
	for (j = 0; j < i; ++j)
	{
		A[j] = sub_array[j];
		A[size_sub_even + j] = sub_array[i + j];
	}
	return ret;
}

int main_9_p_3()
{
	int ret;
	ElementWithCounterPart e1(1);
	ElementWithCounterPart e2(2);
	ElementWithCounterPart e3(3);
	ElementWithCounterPart e4(4);
	ElementWithCounterPart e5(5);
	ElementWithCounterPart e6(6);
	ElementWithCounterPart e7(7);
	ElementWithCounterPart e8(8);
	ElementWithCounterPart e9(9);
	ElementWithCounterPart e10(10);
	ElementWithCounterPart e11(11);
	ElementWithCounterPart e12(12);
	ElementWithCounterPart e13(13);
	ElementWithCounterPart e14(14);
	ElementWithCounterPart e15(15);
	ElementWithCounterPart e16(16);
	vector<ElementWithCounterPart*> A;
	//A = { &e1,&e2,&e3,&e4,&e5,&e6,&e7,&e8,&e9,&e10,&e11,&e12,&e13,&e14,&e15,&e16 };
	A = { &e10,&e1,&e6,&e12,&e14,&e4,&e1,&e2,&e3,
		&e16,&e11,&e13,&e8,&e15,&e3,&e7,&e5,&e6,&e7,&e8,&e9,&e10,&e11,&e12,&e13,&e14 };//&e2,&e9,&e5,
	ret = SelectSmallOrderStatistic(A, 3);

	return 0;
}
