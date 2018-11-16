//if everything is fine mul_avr should return 0; 
//if there will be an overflow error - it will return 1.
int mul_avr(int aNum, int bNum, int cNum, int *aResult)
{
	int res = 0;

	__asm {
		mov eax, aNum
			mov ebx, bNum
			mov ecx, cNum

			add eax, ebx
			jo OVERFLW_ERROR

			shr eax, 1
			imul eax, ecx
			jo OVERFLW_ERROR

			mov res, eax
	}
	*aResult = res;
	return 0;

OVERFLW_ERROR:
	return 1;
}