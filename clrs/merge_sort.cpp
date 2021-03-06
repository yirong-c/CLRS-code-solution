#include "merge_sort.h"

void Merge(int* A, int p, int q, int r)
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
    for (k = p, i = 0, j = 0; k < r + 1; ++k)
    {
        if (L[i] <= R[j])
            A[k] = L[i++];
        else
            A[k] = R[j++];
    }
    delete[] L;
    delete[] R;
}

void MergeSort(int* A, int p, int r)
{
    if (p < r)
    {
        int q;
        q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

void Merge(CommonSortParameters& para, 
    vector<int>& index_table_A, vector<int>& index_table_B,
    int left_index, int middle_index, int right_index)
{
    //middle value is include in subset 1
    int i, j, merge_index, i_key, j_key;
    i = left_index;//index of subset 1
    j = middle_index + 1;//index of subset 2
    for (merge_index = left_index; merge_index <= right_index; ++merge_index)
    {
        if (i > middle_index)
        {
            i_key = INT_MAX;
            para.t1_get_key_from_container(para.container_1, index_table_A[j],
                &j_key, para.data);
        }
        else if (j > right_index)
        {
            j_key = INT_MAX;
            para.t1_get_key_from_container(para.container_1, index_table_A[i],
                &i_key, para.data);
        }
        else
        {
            para.t1_get_key_from_container(para.container_1, index_table_A[i],
                &i_key, para.data);
            para.t1_get_key_from_container(para.container_1, index_table_A[j],
                &j_key, para.data);
        }
        if (i_key <= j_key)
            index_table_B[merge_index] = index_table_A[i++];
        else
            index_table_B[merge_index] = index_table_A[j++];
    }
}

void RecursiveFuncMergeSort(CommonSortParameters& para, 
    vector<int>& index_table_A, vector<int>& index_table_B,
    int left_index, int right_index)
{
    int middle_index;
    /*
    vector<int> *index_table_input_pointer, *index_table_output_pointer;
    index_table_input_pointer = &index_table_A;
    index_table_output_pointer = &index_table_B;
    */
    if (left_index < right_index)
    {
        middle_index = (left_index + right_index) / 2;
        RecursiveFuncMergeSort(para, index_table_B, index_table_A,
            left_index, middle_index);
        RecursiveFuncMergeSort(para, index_table_B, index_table_A,
            middle_index + 1, right_index);
        Merge(para, index_table_A, index_table_B, 
            left_index, middle_index, right_index);
    }
}

/*
жи(nlgn)
stable
Parameters:
    container_1: input containers (vector) of elements
    container_2: output containers (vector) of elements; resize before function is called
    t1_container_elements_size: size of elements in container_1
    t1_get_key_from_container: get key from container_1
    t1_copy_element_between_containers: copy element from container_1 to container_2
*/
void MergeSort(CommonSortParameters& para)
{
    int i;
    vector<int> index_table_A(para.t1_container_elements_size);
    vector<int> index_table_B;
    for (i = 0; i < para.t1_container_elements_size; ++i)
        index_table_A[i] = i;
    index_table_B = index_table_A;
    RecursiveFuncMergeSort(para, index_table_A, index_table_B, 
        0, para.t1_container_elements_size - 1);
    for (i = 0; i < para.t1_container_elements_size; ++i)
        para.t1_copy_element_between_containers(para.container_1, index_table_B[i],
            para.container_2, i, para.data);
}

void Merge(vector<int>& A, int p, int q, int r)
{
    int n1, n2, i, j, k;
    vector<int>::iterator it;
    vector<int> L, R;
    it = A.begin();
    n1 = q - p + 1;
    n2 = r - q;
    L.reserve(n1 + 1);
    R.reserve(n2 + 1);
    L.assign(it + p, it + p + n1);
    R.assign(it + p + n1, it + p + n1 + n2);
    L.push_back(INT_MAX);
    R.push_back(INT_MAX);
    for (k = p, i = 0, j = 0; k < r + 1; ++k)
    {
        if (L[i] <= R[j])
            A[k] = L[i++];
        else
            A[k] = R[j++];
    }
}

void MergeSort(vector<int>& A, int p, int r)
{
    if (p < r)
    {
        int q;
        q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

void MergeReverse(vector<int>& A, int p, int q, int r)
{
    int n1, n2, i, j, k;
    vector<int>::iterator it;
    vector<int> L, R;
    it = A.begin();
    n1 = q - p + 1;
    n2 = r - q;
    L.reserve(n1 + 1);
    R.reserve(n2 + 1);
    L.assign(it + p, it + p + n1);
    R.assign(it + p + n1, it + p + n1 + n2);
    L.push_back(INT_MIN);
    R.push_back(INT_MIN);
    for (k = p, i = 0, j = 0; k < r + 1; ++k)
    {
        if (L[i] >= R[j])
            A[k] = L[i++];
        else
            A[k] = R[j++];
    }
}

void MergeSortReverse(vector<int>& A, int p, int r)
{
    if (p < r)
    {
        int q;
        q = (p + r) / 2;
        MergeSortReverse(A, p, q);
        MergeSortReverse(A, q + 1, r);
        MergeReverse(A, p, q, r);
    }
}

void Merge(vector< ElementWithKey* >& A, int p, int q, int r)
{
    int n1, n2, i, j, k;
    vector< ElementWithKey* >::iterator it;
    vector< ElementWithKey* > L, R;
    ElementWithKey max_key(INT_MAX);
    it = A.begin();
    n1 = q - p + 1;
    n2 = r - q;
    L.reserve(n1 + 1);
    R.reserve(n2 + 1);
    L.assign(it + p, it + p + n1);
    R.assign(it + p + n1, it + p + n1 + n2);
    L.push_back(&max_key);
    R.push_back(&max_key);
    for (k = p, i = 0, j = 0; k < r + 1; ++k)
    {
        if (L[i]->key_ <= R[j]->key_)
            A[k] = L[i++];
        else
            A[k] = R[j++];
    }
}

void MergeSort(vector< ElementWithKey* >& A, int p, int r)
{
    if (p < r)
    {
        int q;
        q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

int main_merge_sort()
{
    int A[5] = { 2,3,8,6,1 };
    MergeSort(A, 0, 4);
    for (int i = 0; i < 5; i++)
        printf("%d ", A[i]);
    printf("\n");
    return 0;
}
