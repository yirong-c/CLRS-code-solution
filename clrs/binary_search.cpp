//2.3-5

int BinarySearch(const int* arr, int left, int right, int num)
{
	int mid;
	if (left >= right)
	{
		if (arr[left] == num)
		{
			return left;
		}
		return -1;
	}
	else
	{
		mid = (right + left) / 2;
		if (arr[mid] == num)
		{
			return mid;
		}
		else if (arr[mid] > num)
		{
			return BinarySearch(arr, left, mid - 1, num);
		}
		else
		{
			return BinarySearch(arr, mid + 1, right, num);
		}
	}
}

int main_binary_search()
{
	int ret;
	int arr[8] = { 1,3,4,10,58,62,63,89 };
	ret = BinarySearch(arr, 0, 8, 12);
	return 0;
}
