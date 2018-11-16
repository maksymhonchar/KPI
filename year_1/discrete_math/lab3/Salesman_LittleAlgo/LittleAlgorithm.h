#pragma once

#define MATRIX_SIZE 6

struct Zero
{
	int i;
	int j;
	int data = 0;
};

int algorithmLittle(int Matr[MATRIX_SIZE][MATRIX_SIZE], int n);
void print(int Matr[MATRIX_SIZE][MATRIX_SIZE], int n);
