#include "stdafx.h"

void FindMaxCrossingSubarray(const int* A, int low, int mid, int high,
    int& max_left, int& max_right, int& max_sum)
{
    int left_sum, right_sum, sum, i;
    left_sum = INT_MIN;
    sum = 0;
    for (i = mid; i >= low; --i)
    {
        sum += A[i];
        if (sum > left_sum)
        {
            left_sum = sum;
            max_left = i;
        }
    }
    right_sum = INT_MIN;
    sum = 0;
    for (i = mid + 1; i <= high; ++i)
    {
        sum += A[i];
        if (sum > right_sum)
        {
            right_sum = sum;
            max_right = i;
        }
    }
    max_sum = left_sum + right_sum;
}

void FindMaxSubarrayDivideAndConquer(const int* A, int low, int high,
    int& max_low, int& max_high, int& max_sum)
{
    if (low == high)
    {
        max_low = low;
        max_high = high;
        max_sum = A[low];
    }
    else
    {
        int mid, left_low, left_high, left_sum, right_low, right_high, right_sum,
            cross_low, cross_high, cross_sum;
        mid = (low + high) / 2;
        FindMaxSubarrayDivideAndConquer(A, low, mid, left_low, left_high, left_sum);
        FindMaxSubarrayDivideAndConquer(A, mid + 1, high, right_low, right_high, right_sum);
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

int main_find_max_subarray_divide_and_conquer()
{
    int A[16] = { 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };
    int max_low, max_high, max_sum;
    FindMaxSubarrayDivideAndConquer(A, 0, 15, max_low, max_high, max_sum);
    printf("max_low:%i\n", max_low);
    printf("max_high:%i\n", max_high);
    printf("max_sum:%i\n", max_sum);
    return 0;
}
