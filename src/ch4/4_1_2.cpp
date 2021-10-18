#include "../stdafx.h"

void FindMaxSubarrayBruteForce(const int* A, int low, int high,
    int& max_low, int& max_high, int& max_sum)
{
    int i, j, loop_max_low, loop_max_high, loop_max_sum, loop_sum;
    for (j = low, max_sum = INT_MIN; j <= high; ++j)
    {
        for (i = j, loop_max_sum = INT_MIN, loop_sum = 0; i <= high; ++i)
        {
            loop_sum += A[i];
            if (loop_sum > loop_max_sum)
            {
                loop_max_low = j;
                loop_max_high = i;
                loop_max_sum = loop_sum;
            }
        }
        if (loop_max_sum > max_sum)
        {
            max_low = loop_max_low;
            max_high = loop_max_high;
            max_sum = loop_max_sum;
        }
    }
}

int main_4_1_2()
{
    clock_t start, end;
    int max_low, max_high, max_sum;
    int A[16] = { 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };
    start = clock();
    FindMaxSubarrayBruteForce(A, 0, 15, max_low, max_high, max_sum);
    end = clock();
    printf("time:%i\n", end - start);
    printf("max_low:%i\n", max_low);
    printf("max_high:%i\n", max_high);
    printf("max_sum:%i\n", max_sum);
    return 0;
}
