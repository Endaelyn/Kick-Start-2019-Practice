#include "pch.h"
#include <fstream>
using namespace std;

bool formable(char* blocks, int** prefix_sum, int L, int R)
{
	const int letters = 26;
	int num = 0;
	bool single_letter = false;
	
	for (int i = 0; i < letters; i++)
	{
		if (L > 1)
		{
			num = prefix_sum[i][R - 1] - prefix_sum[i][L - 2];
		}
		else
		{
			num = prefix_sum[i][R - 1];
		}

		if (num % 2 == 1)
		{
			if (single_letter)
			{
				return false;
			}
			else
			{
				single_letter = true;
			}
		}
	}

	return true;
}

int palindromes(ifstream& fin)
{
	int N, Q;
	fin >> N >> Q;
	char* blocks = new char[N];
	const int letters = 26;
	int* prefix_sum[letters];
	for (int i = 0; i < letters; i++)
	{
		prefix_sum[i] = new int[N] {};
	}
	int ans = 0;

	// calculate prefix sum of each letter in O(N * letters) time
	fin >> blocks[0];
	prefix_sum[int(blocks[0] - 'A')][0]++;
	for (int j = 1; j < N; j++)
	{
		for (int i = 0; i < letters; i++)
		{
			prefix_sum[i][j] = prefix_sum[i][j - 1];
		}
		fin >> blocks[j];
		prefix_sum[int(blocks[j] - 'A')][j]++;
	}

	// calculate Q questions
	for (int q = 0; q < Q; q++)
	{
		int L, R;
		fin >> L >> R;
		if (formable(blocks, prefix_sum, L, R))
		{
			ans++;
		}
	}

	for (int i = 0; i < letters; i++)
	{
		delete[] prefix_sum[i];
	}
	delete[] blocks;
	return ans;
}