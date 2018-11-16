#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "../headers/textModule.h"
#include "../headers/list.h"

#define SAMPLETEXT_PATH "src/data/sampleText.txt"
#define TOWRITETEXT_PATH "src/data/output.txt"

int main()
{
    text_t *text = nlp_getText(SAMPLETEXT_PATH);

    list_t *sentencesList = text_getSentencesList(text);
    char *textStr = (char *) malloc ( sizeof(char) * TEXT_MAX_LEN );
    memset(textStr, 0, TEXT_MAX_LEN);

    for (int i = 0; i < list_getSize(sentencesList); i++)
    {
        sentence_t *currentSentence = (sentence_t *) list_getNodeValueByIndex(sentencesList, i);
        int wordsInCurrentSentence = _sentence_getWordsAmount(currentSentence);

        char **curSentence = malloc ( sizeof(char *) * wordsInCurrentSentence);
        for (int k = 0; k < wordsInCurrentSentence; k++)
        {
            list_t *wordsList = sentence_getWordsList(currentSentence);
            word_t *currentWord = (word_t *) list_getNodeValueByIndex(wordsList, k);
            curSentence[k] = (char *) malloc ( sizeof ( char ) * (_word_getLength(currentWord)));
            sprintf(curSentence[k], "%s", word_getWord(currentWord));
        }
        // Sort words by length.
        _nlp_sort(curSentence, wordsInCurrentSentence);
        // copy words to text char array
        for (int k = 0; k < wordsInCurrentSentence - 1; k++)
        {
            strcat(textStr, curSentence[k]);
            strcat(textStr, ", ");
        }
        strcat(textStr, curSentence[wordsInCurrentSentence - 1]);
        strcat(textStr, "\n");
    }

    FILE *f = fopen(TOWRITETEXT_PATH, "w");
    fprintf(f, "%s", textStr);

    fclose(f);

    return 0;
}
