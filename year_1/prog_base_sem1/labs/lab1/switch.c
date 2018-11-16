#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int exec(int op, int a, int b) {
	int result;
	
	int data_type;
	if(op < 0){
		int temp;
		temp = a;
		a = b;
		b = temp;		
	}

	switch (op)
	{
	case 0:
		result = -a;
		break;
	case 1:
		result = a + b;
		break;
	case 2:
		result = a - b;
		break;
	case 3:
		result = a*b;
		break;
	case 4:
		result = a / b;
		break;
	case 5:
		result = abs(a);	
		break;
	case 6:
		pow(a, b);		
		break;
	case 7:
	case 13:
	case 77:
		result = a%b;
		break;
	case 8:
		result = max(a, b);
		// if (a>b){
		// 	return a;
		// }
		// if (a<b){
		// 	return b;
		// }
		// else{
		// 	return 0;
		// }
		break;
	case 9:
		result = min(a, b);
		// if (a<b){
		// 	return a;
		// }
		// if (a>b){
		// 	return b;
		// }
		// else{
		// 	return 0;
		// }
		break;
	case 10:
		switch (abs(b)%8)
		{
		case 0:
			result = abs(a)*sizeof(char);
			break;
		case 1:
			result = abs(a)*sizeof(signed char);
			break;
		case 2:
			result = abs(a)*sizeof(short);
			break;
		case 3:
			result = abs(a)*sizeof(unsigned int);
			break;
		case 4:
			result = abs(a)*sizeof(long);
			break;
		case 5:
			result = abs(a)*sizeof(unsigned long long);
			break;
		case 6:
			result = abs(a)*sizeof(float);
			break;
		case 7:
			result = abs(a)*sizeof(double);
			break;
		}
		break;
	case 11:
		result = M_PI*((a+b)%(4+0+2))/b;
		break;
	}
	default:
		if (op < 100) {
			result = (op%abs(a + 1)) + (op%abs(b + 1));
		}
		else if (op >= 100)
		{
			result = -1;
		}
		break;
	}

	return result;
}
