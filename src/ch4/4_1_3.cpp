#include "../stdafx.h"

//Divide-and-Conquer--------------------------------------------------
void FindMaxCrossingSubarray(const int* A, int low, int mid, int high,
    int& max_left, int& max_right, int& max_sum);
void FindMaxSubarrayDivideAndConquer(const int* A, int low, int high,
    int& max_low, int& max_high, int& max_sum);
//Brute-Force---------------------------------------------------------
void FindMaxSubarrayBruteForce(const int* A, int low, int high,
    int& max_low, int& max_high, int& max_sum);

void TimeTestDivideAndConquer(const int* A, int array_size)
{
    clock_t start, end;
    int max_low, max_high, max_sum, i, test_time, clock_time, clock_time_sum;
    test_time = 10;
    for (i = 0, clock_time_sum = 0; i < test_time; ++i)
    {
        start = clock();
        FindMaxSubarrayDivideAndConquer(A, 0, array_size, max_low, max_high, max_sum);
        end = clock();
        clock_time = end - start;
        clock_time_sum += clock_time;
    }
    printf("Divide-and-Conquer|array_size:%i|time:%i\n", array_size, clock_time_sum / test_time);
}

void TimeTestBruteForce(const int* A, int array_size)
{
    clock_t start, end;
    int max_low, max_high, max_sum, i, test_time, clock_time, clock_time_sum;
    test_time = 10;
    for (i = 0, clock_time_sum = 0; i < test_time; ++i)
    {
        start = clock();
        FindMaxSubarrayBruteForce(A, 0, array_size, max_low, max_high, max_sum);
        end = clock();
        clock_time = end - start;
        clock_time_sum += clock_time;
    }
    printf("Brute-Force|array_size:%i|time:%i\n", array_size, clock_time_sum / test_time);
}

void FindMaxSubarrayMixDivideAndConquerBruteForce(int n0, const int* A, int low, int high,
    int& max_low, int& max_high, int& max_sum)
{
    if (high - low <= n0)
    {
        FindMaxSubarrayBruteForce(A, low, high, max_low, max_high, max_sum);
    }
    else
    {
        int mid, left_low, left_high, left_sum, right_low, right_high, right_sum,
            cross_low, cross_high, cross_sum;
        mid = (low + high) / 2;
        FindMaxSubarrayMixDivideAndConquerBruteForce(n0, A, low, mid, left_low, left_high, left_sum);
        FindMaxSubarrayMixDivideAndConquerBruteForce(n0, A, mid + 1, high, right_low, right_high, right_sum);
        FindMaxCrossingSubarray(A, low, mid, high, cross_low, cross_high, cross_sum);
        if (left_sum >= right_sum && left_sum >= cross_sum)
        {
            max_low = left_low;
            max_high = left_high;
            max_sum = left_sum;
        }
        else if (right_sum >= left_sum && right_high >= cross_sum)
        {
            max_low = right_low;
            max_high = right_high;
            max_sum = right_sum;
        }
        else
        {
            max_low = cross_low;
            max_high = cross_high;
            max_sum = cross_sum;
        }
    }
}

void TimeTestMix(int n0, const int* A, int array_size)
{
    clock_t start, end;
    int max_low, max_high, max_sum, i, test_time, clock_time, clock_time_sum;
    test_time = 10;
    for (i = 0, clock_time_sum = 0; i < test_time; ++i)
    {
        start = clock();
        FindMaxSubarrayMixDivideAndConquerBruteForce(n0, A, 0, array_size, max_low, max_high, max_sum);
        end = clock();
        clock_time = end - start;
        clock_time_sum += clock_time;
    }
    printf("mix-n0:%i|array_size:%i|time:%i\n", n0, array_size,
        clock_time_sum / test_time);
}

int main_4_1_3()
{
    clock_t start, end;
    int *A, i;
    A = new int[500000]();
    for (i = 50; i > 0; --i)
    {
        TimeTestDivideAndConquer(A, i);
    }
    for (i = 50; i > 0; --i)
    {
        TimeTestBruteForce(A, i);
    }
    for (i = 50; i > 0; --i)
    {
        TimeTestMix(13, A, i);
    }
    delete[] A;
    return 0;
}
