#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "../headers/textModule.h"
#include "../headers/list.h"

//----------------------------------------->>> Private structures <<<-----------------------------------------

struct word_s
{
    char *word;
};

struct sentence_s
{
    list_t *words;
};

struct text_s
{
    list_t *sentences;
};

//----------------------------------------->>> Private methods <<<-----------------------------------------

void _nlp_sort(char **arr, int elems)
{
    for (int i = 0; i < elems - 1; i++)
    {
        for (int d = 0; d < elems - i - 1; d++)
        {
            if (strlen(arr[d]) > strlen(arr[d+1]))
            {
                char tmp[10000] = "\0";
                strcpy(tmp, arr[d]);
                strcpy(arr[d], arr[d+1]);
                strcpy(arr[d+1], tmp);
            }
        }
    }
}

int _sentence_getWordsAmount(const sentence_t *sentenceObj)
{
    return (list_getSize(sentenceObj->words));
}

int _text_getSentencesAmount(const text_t *textObj)
{
    return (list_getSize(textObj->sentences));
}

int _text_getWordsAmount(const text_t *textObj)
{
    int amountOfWords = 0;
    for (int i = 0; i < _text_getSentencesAmount(textObj); i++)
    {
        sentence_t *currentSentence = (sentence_t *) list_getNodeValueByIndex(textObj->sentences, i);
        amountOfWords += _sentence_getWordsAmount(currentSentence);
    }
    return (amountOfWords);
}

int _word_getLength(const word_t *wordObj)
{
    if (wordObj->word == NULL)
    {
        return (0);
    }
    else
    {
        return (strlen(wordObj->word));
    }
}

//----------------------------------------->>> Public methods <<<-----------------------------------------

text_t *text_new()
{
    text_t *out = (text_t *) malloc ( sizeof ( struct text_s ) );
    out->sentences = list_new();
    return (out);
}

sentence_t *sentence_new()
{
    sentence_t *out = (sentence_t *) malloc ( sizeof ( struct sentence_s ) );
    out->words = list_new();
    return (out);
}

word_t *word_new()
{
    word_t *out = (word_t *) malloc ( sizeof ( struct word_s ) );
    out->word = (char *) malloc ( sizeof(char) * WORD_MAX_LEN );
    return (out);
}

void text_delete(text_t *textObj)
{
    list_delete(textObj->sentences);
    free (textObj);
}

void sentence_delete(sentence_t *sentenceObj)
{
    list_delete(sentenceObj->words);
    free (sentenceObj);
}

void word_delete(word_t *wordObj)
{
    free (wordObj->word);
    free (wordObj);
}

text_t *nlp_getText(const char *filePath)
{
    // Get text from file.
    char textBuffer[TEXT_MAX_LEN] = "\0";
    FILE *file = fopen(filePath, "r");
    int len = fread(textBuffer, 1, sizeof(textBuffer), file);
    textBuffer[len] = '\0';

    // Create text object to hold list of sentences in text.
    text_t *text = text_new();

    // Fill array of sentences.
    char **sentences = malloc ( sizeof(char *) * SENTENCE_MAX_AMOUNT);
    for (int i = 0; i < SENTENCE_MAX_AMOUNT; i++)
        sentences[i] = (char *) malloc ( sizeof(char) * SENTENCE_MAX_LEN);
    const char *endings = ".!?";
    char *token = strtok(textBuffer, endings);
    int sentenceCounter = 0;
    while (token != NULL)
    {
        strcpy(sentences[sentenceCounter++], token);
        token = strtok(NULL, endings);
    }

    // Fill list of sentences and words in text object.
    const char *endingsWords = " ,()\n\r\'\"/\\><;:~`[]";
    for (int i = 0; i < sentenceCounter; i++)
    {
        sentence_t *curSentence = sentence_new();
        // Get words for each sentence.
        token = strtok(sentences[i], endingsWords);
        while (token != NULL)
        {
            word_t *currentWord = word_new();
            strcpy(currentWord->word, token);
            list_insertLast(curSentence->words, (void *)currentWord);
            token = strtok(NULL, endingsWords);
        }
        list_insertLast(text->sentences, (void *) curSentence);
    }

    // Free allocated memory & close stream.
    fclose(file);
    for (int i = 0; i < SENTENCE_MAX_AMOUNT; i++)
        free (sentences[i]);
    free (sentences);

    // Return prepared text structure.
    return (text);
}

//----------------------------------------->>> Getters & setters <<<-----------------------------------------

list_t *text_getSentencesList(const text_t *textObj)
{
    return (textObj->sentences);
}

list_t *sentence_getWordsList(const sentence_t *sentenceObj)
{
    return (sentenceObj->words);
}

char *word_getWord(const word_t *wordObj)
{
    return (wordObj->word);
}

//----------------------------------------->>> Printing methods <<<-----------------------------------------

void sentence_printSentence(const sentence_t *sentenceObj)
{
    for (int i = 0; i < list_getSize(sentenceObj->words); i++)
    {
        word_t *currentWord = list_getNodeValueByIndex(sentenceObj->words, i);
        printf("%s ", word_getWord(currentWord));
    }
    puts("");
}

void word_printWord(const word_t *wordObj)
{
    puts(word_getWord(wordObj));
}
