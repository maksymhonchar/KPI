#include <math.h>

double calc(double x, double y, double z) {
   	double a;
   
	if (x == y || x == 0 || z == 0 || sin(x) == 0) {
		return NAN;
	}
	else {
		a = (pow(x, (y + 1))) / (pow((x - y), (1 / z))) + (4 * y + z / x) + fabs(cos(y) / cos(x) + 0);
	}

   return a;
}