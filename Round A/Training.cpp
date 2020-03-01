#include "pch.h"
#include <fstream>
#include <algorithm>
using namespace std;

bool cmp(int a, int b)
{
	return a < b;
}

int training(ifstream& fin)
{
	// input case
	int N, P, result = 0, min_res = INT32_MAX;
	fin >> N >> P;

	int* S = new int[N];
	for (int i = 0; i < N; i++)
	{
		fin >> S[i];
	}

	// sort by skill rating
	sort(S, S + N, cmp);

	// do something
	int pre_sum = 0;
	for (int i = 0; i < P; i++)
	{
		pre_sum += S[i];
	}

	for (int i = 0; i < N - P + 1; i++)
	{
		result = P * S[i + P - 1] - pre_sum; // compute result in O(1) instead of O(P)
		if (result < min_res)
		{
			min_res = result;
		}
		pre_sum += S[i + P] - S[i];
	}

	delete[] S;

	return min_res;
}