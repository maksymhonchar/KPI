#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "LittleAlgorithm.h"

int main()
{
	int adjacencyMatrix[MATRIX_SIZE][MATRIX_SIZE] = {
		{ 0,5,29,8,13,10 },
		{ 5,0,7,11,15,9 },
		{ 29,7,0,9,18,11 },
		{ 8,11,9,0,3,17 },
		{ 13,15,18,3,0,6 },
		{ 10,9,11,17,6,0 }
	};

	/*
	{N,5,29,8,13,10},
	{5,N,7,11,15,9},
	{29,7,N,9,18,11},
	{8,11,9,N,3,17},
	{13,15,18,3,N,6},
	{10,9,11,17,6,N}	
	*/

	for (int i = 0; i < MATRIX_SIZE; i++)
		adjacencyMatrix[i][i] = INT_MAX;

	print(adjacencyMatrix, MATRIX_SIZE);

	puts("Branch and bound algorithm.");
	int L = algorithmLittle(adjacencyMatrix, MATRIX_SIZE);
	printf("Minimal length is: %d\n", L - 1);

	system("pause");
	return 0;
}

int algorithmLittle(int Matr[MATRIX_SIZE][MATRIX_SIZE], int n)
{
	int size = n - 1;
	int L = 0;

	while (n > 2)
	{
		for (int i = 1; i < n; i++)
		{
			int min = INT_MAX;
			for (int j = 1; j < n; j++)
			{
				if (Matr[i][j] < min)
					min = Matr[i][j];
			}
			L += min;
			for (int j = 1; j < n; j++)
			{
				if (Matr[i][j] != INT_MAX)
					Matr[i][j] -= min;
			}
		}
		int cnt = 0;
		for (int i = 1; i < n; i++)
		{
			int min = INT_MAX;
			for (int j = 1; j < n; j++)
			{
				if (Matr[j][i] < min)
					min = Matr[j][i];
			}
			L += min;
			for (int j = 1; j < n; j++)
			{
				if (Matr[j][i] != INT_MAX)
					Matr[j][i] -= min;
				if (Matr[j][i] == 0)
					cnt++;
			}
		}
		Zero *aZero = new Zero[cnt];
		int index = 0;
		for (int i = 1; i < n; i++)
		{
			for (int j = 1; j < n; j++)
			{
				if (Matr[i][j] == 0)
				{
					aZero[index].i = i;
					aZero[index].j = j;
					index++;
				}
			}
		}
		for (int index = 0; index < cnt; index++)
		{
			int min = INT_MAX;
			for (int i = 1; i < n; i++)
			{
				if (aZero[index].i != i && min > Matr[i][aZero[index].j])
					min = Matr[i][aZero[index].j];
			}
			aZero[index].data += min;
			min = INT_MAX;
			for (int j = 1; j < n; j++)
			{
				if (aZero[index].j != j && min > Matr[aZero[index].i][j])
					min = Matr[aZero[index].i][j];
			}
			aZero[index].data += min;
		}
		Zero max;
		max = aZero[0];
		for (int i = 0; i < cnt; i++)
		{
			if (aZero[i].data > max.data)
				max = aZero[i];
		}
		n--;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				if (j < max.j && i >= max.i)
					Matr[i][j] = Matr[i + 1][j];
				else if (j >= max.j)
					if (i < max.i)
						Matr[i][j] = Matr[i][j + 1];
					else
						Matr[i][j] = Matr[i + 1][j + 1];
			}

		bool flag = false;
		for (int i = 1; i < n; i++)
		{
			for (int j = 1; j < n; j++)
			{
				if (Matr[i][j] == INT_MAX) break;
				if (j == n - 1)
				{
					int ind = 1;
					while (!flag)
					{
						for (int k = i + 1; k < n; k++)
						{
							if (Matr[ind][k] == INT_MAX) break;
							if (k == n - 1)
							{
								Matr[i][ind] = INT_MAX;
								flag = true;
							}
						}
						ind++;
						if (ind == n)
						{
							Matr[i][j] = INT_MAX;
							flag = true;
						}
					}
				}
			}
			if (flag) break;
		}
		delete aZero;
	}

	return (L);
}

void print(int Matr[MATRIX_SIZE][MATRIX_SIZE], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Matr[i][j] == INT_MAX) {
				printf("%4c", '_');
				continue;
			}
			printf("%4d", Matr[i][j]);
		}
		puts("");
	}
	puts("");
}
