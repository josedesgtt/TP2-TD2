#include "utils.h"

int strLen(char* src) {
    int i = 1;
    while (src[i] != '\0') i++;
    return i;
}

char* strDup(char* src) {
    int size = strLen(src);
    char* copia = (char*) malloc(size);
    for (int i=0; i<size; i++) copia[i] = (char) src[i];
    return copia;
}

// Keys Predict

struct keysPredict* keysPredictNew() {
    struct keysPredict* kt = (struct keysPredict*)malloc(sizeof(struct keysPredict));
    kt->first = 0;
    kt->totalKeys = 0;
    kt->totalWords = 0;
    return kt;
}

void keysPredictAddWord(struct keysPredict* kt, char* word) {

    // COMPLETAR

}

void keysPredictRemoveWord(struct keysPredict* kt, char* word) {

    // COMPLETAR
}

struct node* keysPredictFind(struct keysPredict* kt, char* word) {

    // COMPLETAR

    return 0;
}

char** keysPredictRun(struct keysPredict* kt, char* partialWord, int* wordsCount) {

    // COMPLETAR

    return 0;
}

int keysPredictCountWordAux(struct node* n) {

    // COMPLETAR
}

char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {

    // COMPLETAR

    return 0;
}

void keysPredictDelete(struct keysPredict* kt) {

    // COMPLETAR

}

void keysPredictPrint(struct keysPredict* kt) {
    printf("--- Predict --- Keys: %i Words: %i\n", kt->totalKeys, kt->totalWords);
    keysPredictPrintAux(kt->first, 0);
    printf("---\n");
}

void keysPredictPrintAux(struct node* n, int level) {
    if(!n) return;
    struct node* current = n;
    while(current) {
        for(int i=0; i<level;i++) printf(" |   ");
        if(current->end) {
            printf("[%c]\n",current->character);
        } else  {
            printf(" %c \n",current->character);
        }
        keysPredictPrintAux(current->down, level+1);
        current = current->next;
    }
}

// Auxiliar functions

struct node* findNodeInLevel(struct node** list, char character) {

    return n;
}

struct node* addSortedNewNodeInLevel(struct node** list, char character) {

    // COMPLETAR

    return 0;
}

void deleteArrayOfWords(char** words, int wordsCount) {

    // COMPLETAR
}
