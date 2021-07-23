#include "stdafx.h"

//with inversion
int inversions = 0;

void MergeWithInversion(int* A, int p, int q, int r)
{
    int n1, n2, * L, * R, i, j, k;
    n1 = q - p + 1;
    n2 = r - q;
    L = new int[n1 + 1];
    R = new int[n2 + 1];
    memcpy(L, A + p, n1 * sizeof(int));
    memcpy(R, A + p + n1, n2 * sizeof(int));
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    i = n1 - 1;
    j = n2 - 1;
    while (i >= 0 && j >= 0)//жи(n)
    {
        if (L[i] <= R[j])
        {
            j--;
        }
        else
        {
            i--;
            inversions = inversions + j + 1;
        }
    }
    for (k = p, i = 0, j = 0; k < r + 1; ++k)//жи(n)
    {
        if (L[i] <= R[j])
            A[k] = L[i++];
        else
            A[k] = R[j++];
    }
    delete[] L;
    delete[] R;
}

void MergeWithInversionOpt1(int* A, int p, int q, int r)
{
    int n1, n2, * L, * R, i, j, k;
    n1 = q - p + 1;
    n2 = r - q;
    L = new int[n1 + 1];
    R = new int[n2 + 1];
    memcpy(L, A + p, n1 * sizeof(int));
    memcpy(R, A + p + n1, n2 * sizeof(int));
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    for (k = p, i = 0, j = 0; k < r + 1; ++k)//жи(n)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i++];
        }
        else
        {
            A[k] = R[j++];
            inversions = inversions + (n1 - i);
        }
    }
    delete[] L;
    delete[] R;
}

void MergeSortWithInversion(int* A, int p, int r)
{
    if (p < r)
    {
        int q;
        q = (p + r) / 2;
        MergeSortWithInversion(A, p, q);
        MergeSortWithInversion(A, q + 1, r);
        //MergeWithInversion(A, p, q, r);
        MergeWithInversionOpt1(A, p, q, r);
    }
}

int main_2_p_4 ()
{
    int A[5] = { 2,3,8,6,1 };
    MergeSortWithInversion(A, 0, 4);
    printf("%i\n", inversions);
    return 0;
}
