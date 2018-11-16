#pragma once

#include "../headers/list.h"

#define WORD_MAX_LEN 100000
#define SENTENCE_MAX_LEN 100000
#define TEXT_MAX_LEN 100000

#define SENTENCE_MAX_AMOUNT 10000
#define WORDS_MAX_AMOUNT 1000

typedef struct word_s word_t;
typedef struct sentence_s sentence_t;
typedef struct text_s text_t;

// Constructors and destructors.
text_t *text_new();
sentence_t *sentence_new();
word_t *word_new();
void text_delete(text_t *textObj);
void sentence_delete(sentence_t *sentenceObj);
void word_delete(word_t *wordObj);

// Getters and setters.
list_t *text_getSentencesList(const text_t *textObj);
list_t *sentence_getWordsList(const sentence_t *sentenceObj);
char *word_getWord(const word_t *wordObj);

// Printing methods.
void sentence_printSentence(const sentence_t *sentenceObj);
void word_printWord(const word_t *wordObj);

// NLP module functions.
text_t *nlp_getText(const char *filePath);
void nlp_sortSentenceWords(text_t *textObj);

// random shit
int _word_getLength(const word_t *wordObj);
int _text_getWordsAmount(const text_t *textObj);
int _text_getSentencesAmount(const text_t *textObj);
int _sentence_getWordsAmount(const sentence_t *sentenceObj);
void _nlp_sort(char **arr, int elems);
