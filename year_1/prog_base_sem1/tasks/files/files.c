#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fprocess(const char * pread, const char * pwrite) {
	int status = 1; //so much wow, amazing var
	char *wordToWrite = (char*) calloc(40, sizeof(char));
	FILE *file;
	file = fopen(pread, "r");
	char *sentence = (char*) malloc(100 * sizeof(char));
	while (fgets(sentence, 100, file) != NULL && status <= 4) {
		char *word, *maxWord;
		int maxLength = 0;
		maxWord = (char*) calloc(40, sizeof(char));
		word = (char*) calloc(40, sizeof(char));
		word = strtok(sentence, " ");
		while (word != NULL) {
			if ((int) strlen(word) > maxLength) {
				maxLength = strlen(word);
				strcpy(maxWord, word);
			}
			word = strtok(NULL, " ");
		}
		if (status == 4) {
			printf("%s\n", maxWord);
			wordToWrite = maxWord;
		}
		maxLength = 0;
		status++;
	}
	fclose(file);

	file = fopen(pwrite, "w+");
	fprintf(file, wordToWrite);
	fclose(file);
}

int main(void) {
	
	fprocess("temp.txt", "answer.txt");

	return 0;
}
