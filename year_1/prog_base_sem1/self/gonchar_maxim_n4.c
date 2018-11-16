#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

int main() {
	char *file_name = (char*)malloc(20*sizeof(char));
	int M, N;
	int i;
	char buff[200];
	FILE *fp;

	//Reading filename, N and M from user.
	//Write file with .txt
	puts("Please, write file with .txt");
	gets_s(file_name, 20);
	if (strstr(file_name, ".txt") == NULL) {
		puts("Please, write .txt next time");
		Sleep(2000);
		return;
	}
	//Input M and N numbers
	puts("Write M and N numbers");
	scanf("%i %i", &M, &N);
	if (M >= N) {
		puts("M is more than N or equals to it. Please, rewrite next time");
		Sleep(2000);
		return;
	}

	//Create file and add some items into it
	fp = fopen(file_name, "w+");
	fputs("C is an imperative (procedural) language. \
	It was designed to be compiled using a relatively straightforward compiler, \
	to provide low-level access to memory, to provide language constructs\
	that map efficiently to machine instructions, and to require minimal run-time support. \
	C was therefore useful for many applications that had formerly been coded in assembly language, \
	such as in system programming. Despite its low - level capabilities, the language was designed to encourage ", fp);
	//Close a stream.
	fclose(fp);

	//Read a file and write in console characters from M to N.
	fp = fopen(file_name, "r");
	fgets(buff, 200, fp);
	for (i = M; i < N; i++) {
		printf("%c", buff[i]);
	}
	puts("");
	//Close stream.
	fclose(fp);

	Sleep(2000);
	return 0;
}