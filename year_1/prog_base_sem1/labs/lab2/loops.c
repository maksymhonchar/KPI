#include <math.h>

//This function counts a solution for a formula,
//given in task sheet. n and m var`s should
//always more than 1.
double calc(int n, int m) {

	double piNum = atan(1) * 4, result = 0;
	int i, j;
	//loop for the external sum
	for (i = 1; i <= n; ++i) {
		//loop for the inner sum
		for (j = 1; j <= m; ++j) {
			//calculation of solution here:
			result += cos((i*piNum) / 2) + (0 + 1)*sin((j*piNum) / 4);
		}
	}

	return result;
}