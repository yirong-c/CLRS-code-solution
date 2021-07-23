#pragma once
#include <climits>
#include <string.h>
#include <cstdio>
#include <ctime>
#include <chrono>
#include <cmath>
#include <vector>
#include <list>
using namespace std;
using namespace std::chrono;

inline int BinaryTreeParent(int i)
{
	return (i - 1) / 2;
}

inline int BinaryTreeLeft(int i)
{
	return 2 * i + 1;
}

inline int BinaryTreeRight(int i)
{
	return 2 * i + 2;
}

inline void SwapInt(int& a, int& b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

template <typename T>
inline void SwapTemplate(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

inline int GetRangedRandomNum(int left_end, int right_end)
{
	srand((unsigned)time(NULL));
	return rand() % (right_end - left_end + 1) + left_end;
}

