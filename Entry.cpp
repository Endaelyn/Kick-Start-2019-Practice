#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;

// note: stream can't be copied, use reference instead
int(*choose_problem(char round_char, int problem_num))(ifstream&);

// round A
int training(ifstream&);
int parcels(ifstream&);
// round B
int palindromes(ifstream&);

int main()
{
	char round_char = 'B';
	int problem_num = 1;
	int(*problem)(ifstream&) = nullptr;

	if (!(isalpha(round_char) && (problem_num >= 1 && problem_num <= 3)))
	{
		cout << "Please choose a existing problem.";
		return -1;
	}

	// read input from file
	/* input file name should be copied from
	 * file of corresponding problem */
	ifstream fin;
	fin.open("Input\\Input - ?");
	if (!fin.is_open())
	{
		cout << "Input file not found.";
		return -1;
	}

	problem = choose_problem(round_char, problem_num);

	int T;
	fin >> T;
	for (int t = 0; t < T; t++)
	{
		cout << "Case #" << t + 1 << ": " << (*problem)(fin) << endl;
	}
	fin.close();

	return 0;
}

int(*choose_problem(char r_c, int p_n))(ifstream&)
{
	switch (r_c)
	{
	case 'A':
	case 'a':
	{
		switch (p_n)
		{
		case 1:
			return &training;
		case 2:
			return &parcels;
		default:
			break;
		}
		return nullptr;
		break;
	}
	case 'B':
	case 'b':
	{
		switch (p_n)
		{
		case 1:
			return &palindromes;
		case 2:
			break;
		default:
			break;
		}
		return nullptr;
		break;
	}
	default:
		return nullptr;
		break;
	}
}