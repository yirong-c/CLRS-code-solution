#include "stdafx.h"

class MatchJugsResult
{
public:
	int red;
	int blue;
	MatchJugsResult(int blue)
	{
		this->blue = blue;
	}
	MatchJugsResult(int red, int blue)
	{
		this->red = red;
		this->blue = blue;
	}
};

void RandomizedMatchJugs(vector<int>& red_set, vector<int>& blue_set,
	vector<MatchJugsResult>& result)
{
	vector<int> red_small, red_big, blue_small, blue_big;
	int size, random_red_index, random_red_value, result_vector_index, i;
	size = red_set.size();
	if (size <= 0)
	{
		return;
	}
	else if (size == 1)
	{
		result.push_back(MatchJugsResult(red_set[0], blue_set[0]));
		return;
	}
	result_vector_index = result.size() - 1;
	random_red_index = GetRangedRandomNum(0, size - 1);
	random_red_value = red_set[random_red_index];

	blue_small.reserve(size - 1);
	blue_big.reserve(size - 1);
	for (i = 0; i < size; ++i)
		if (blue_set[i] < random_red_value)
			blue_small.push_back(blue_set[i]);
		else if (blue_set[i] > random_red_value)
			blue_big.push_back(blue_set[i]);
		else
			result.push_back(MatchJugsResult(blue_set[i]));
	blue_small.shrink_to_fit();
	blue_big.shrink_to_fit();

	red_small.reserve(size - blue_small.size() - 1);
	red_big.reserve(size - blue_big.size() - 1);
	for (i = 0; i < size; ++i)
		if (red_set[i] < random_red_value)
			red_small.push_back(red_set[i]);
		else if (red_set[i] > random_red_value)
			red_big.push_back(red_set[i]);
		else
			result[++result_vector_index].red = red_set[i];
	red_small.shrink_to_fit();
	red_big.shrink_to_fit();

	RandomizedMatchJugs(red_small, blue_small, result);
	RandomizedMatchJugs(red_big, blue_big, result);
}

int main_8_p_4()
{
	int size;
	vector<int> red_set, blue_set;
	red_set = { 1,3,5,7,9 };
	blue_set = { 7,1,9,3,5 };
	size = red_set.size();
	vector<MatchJugsResult> result;
	result.reserve(size);
	RandomizedMatchJugs(red_set, blue_set, result);

	return 0;
}