#include "pch.h"
#include <fstream>
#include <queue>
using namespace std;

struct loc
{
	int r, c;
};

int C_dist(int plus1, int minus1, int r2, int c2)
{
	return max(abs(plus1 - (r2 + c2)), abs(minus1 - (r2 - c2)));
}

// multiple-source BFS
int deli_time(int** & grid, queue<loc> & offices, int R, int C)
{
	queue<loc> Q = offices;
	int max_time = 0;
	while (!Q.empty())
	{
		int row = Q.front().r, col = Q.front().c;
		if (row > 0)
		{
			if (grid[row - 1][col] < 0)
			{
				grid[row - 1][col] = grid[row][col] + 1;
				Q.push({ row - 1, col });
				if (grid[row - 1][col] > max_time)
				{
					max_time = grid[row - 1][col];
				}
			}
		}
		if (row < R - 1)
		{
			if (grid[row + 1][col] < 0)
			{
				grid[row + 1][col] = grid[row][col] + 1;
				Q.push({ row + 1, col });
				if (grid[row + 1][col] > max_time)
				{
					max_time = grid[row + 1][col];
				}
			}
		}
		if (col > 0)
		{
			if (grid[row][col - 1] < 0)
			{
				grid[row][col - 1] = grid[row][col] + 1;
				Q.push({ row, col - 1 });
				if (grid[row][col - 1] > max_time)
				{
					max_time = grid[row][col - 1];
				}
			}
		}
		if (col < C - 1)
		{
			if (grid[row][col + 1] < 0)
			{
				grid[row][col + 1] = grid[row][col] + 1;
				Q.push({ row, col + 1 });
				if (grid[row][col + 1] > max_time)
				{
					max_time = grid[row][col + 1];
				}
			}
		}
		Q.pop();
	}
	return max_time;
}

bool K_avail(int** & grid, int K, int R, int C)
{
	// convert Manhattan distance to Chebyshev distance
	int max_plus = 0;			// maximized r1 + c1
	int min_plus = R + C - 2;	// minimized r1 + c1
	int max_minus = 1 - C;		// maximized r1 - c1
	int min_minus = R - 1;		// minimized r1 - c1

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (grid[i][j] > K)
			{
				if (i + j > max_plus)
				{
					max_plus = i + j;
				}
				if (i + j < min_plus)
				{
					min_plus = i + j;
				}
				if (i - j > max_minus)
				{
					max_minus = i - j;
				}
				if (i - j < min_minus)
				{
					min_minus = i - j;
				}
			}
		}
	}

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (C_dist(max_plus, max_minus, i, j) <= K &&
				C_dist(max_plus, min_minus, i, j) <= K &&
				C_dist(min_plus, max_minus, i, j) <= K &&
				C_dist(min_plus, min_minus, i, j) <= K)
			{
				return true;
			}
		}
	}
	return false;
}

int parcels(ifstream& fin)
{
	// input case
	queue<loc> offices;
	int K = 0, maxK = 0, minK = 0;
	int R, C;
	fin >> R >> C;

	int** grid = new int*[R];
	for (int i = 0; i < R; i++)
	{
		grid[i] = new int[C];
		fin.get(); // get rid of 'return' char
		for (int j = 0; j < C; j++)
		{
			grid[i][j] = int(fin.get() - '0' - 1);
			/* positive value of grid[i][j] means its
			 * min delivery time, -1 means not known. */
			if (grid[i][j] == 0)
			{
				offices.push({ i, j });
			}
		}
	}

	// bi-search
	if (offices.empty())
	{
		grid[R / 2][C / 2] = 0;
		offices.push({ R / 2, C / 2 });
		K = deli_time(grid, offices, R, C);
	}
	else
	{
		maxK = deli_time(grid, offices, R, C);
		K = maxK / 2;
		while (minK < maxK - 1)
		{
			if (K_avail(grid, K, R, C))
			{
				maxK = K;
				K = (K + minK) / 2;
			}
			else
			{
				minK = K;
				K = (K + maxK) / 2;
			}
		}
		if (K_avail(grid, minK, R, C))
		{
			K = minK;
		}
		else
		{
			K = maxK;
		}
	}

	for (int i = R - 1; i >= 0; i--)
	{
		delete[] grid[i];
	}
	delete[] grid;

	return K;
}
