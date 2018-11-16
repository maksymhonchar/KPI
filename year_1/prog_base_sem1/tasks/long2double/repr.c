#include <math.h>

double long2double(long long myLong) {
	
	int numsArr[64];
	double expArr[11], fractArr[52];
	double fractDec = 0, expDec = 0, signDec;
	int i;

	//Convert myLong to binary. numsArr[i] = 1 digit
	for (i = 0; i <= 63; i++) {
		numsArr[i] = (myLong & (1LL << 63 - i)) ? 1 : 0;
	}
	//Add 1and0 to arrays
	for (i = 0; i < 11; i++) {
		expArr[i] = numsArr[i + 1];
	}
	for (i = 0; i < 52; i++) {
		fractArr[i] = numsArr[i + 12];
	}
	//Convert arrays to dec nums
	signDec = numsArr[0];
	for (i = 0; i <= 10; i++) {
		expDec += expArr[i] * pow(2, i);
	}
	for (i = 0; i < 52; i++) {
		fractDec += fractArr[i] * pow(2, -i - 1);
	}
	//Do final calculations and return result
	if (expDec == 0 && fractDec != 0) {
		return pow(-1, signDec) * pow(2, -1022) * fractDec;
	}
	if (expDec >0 && expDec < 2047) {
		return pow(-1, signDec) * pow(2, expDec - 1023) * (fractDec + 1);
	}
	if (expDec == 2047 && fractDec != 0) {
		return NAN;
	}
	if (expDec == 2047 && fractDec == 0 && signDec == 1) {
		return -INFINITY;
	}
	if (expDec == 2047 && fractDec == 0 && signDec == 0) {
		return INFINITY;
	}
	if (expDec == 0 && fractDec == 0 && signDec == 1) {
		return -0;
	}
	if (expDec == 0 && fractDec == 0 && signDec == 0) {
		return 0;
	}

}