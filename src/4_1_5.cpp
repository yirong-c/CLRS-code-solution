#include "stdafx.h"

void FindMaxSubarrayLinearTime(const int* A, int low, int high,
    int& max_low, int& max_high, int& max_sum)
{
    int i, sum, low_now;
    max_sum = INT_MIN;
    for (i = low, sum = INT_MIN; i <= high; ++i)
    {
        if (sum <= 0)
        {
            low_now = i;
            sum = A[i];
        }
        else
        {
            sum += A[i];
        }
        if (sum > max_sum)
        {
            max_low = low_now;
            max_high = i;
            max_sum = sum;
        }
    }
}

int main_4_1_5()
{
    int A[16] = { 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };
    int max_low, max_high, max_sum;
    FindMaxSubarrayLinearTime(A, 0, 15, max_low, max_high, max_sum);
    printf("max_low:%i\n", max_low);
    printf("max_high:%i\n", max_high);
    printf("max_sum:%i\n", max_sum);
    return 0;
}
