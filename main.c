#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void predictAndPrintAll(struct keysPredict* kt, char* partialWord ) {
    char** words;
    int wordsCount;
    words = keysPredictRun(kt, partialWord, &wordsCount);
    printf("Predicts: %s = ", partialWord);
    for(int i=0; i<wordsCount; i++) {
        printf("%s,", words[i]);
    }
    printf("\n");
    deleteArrayOfWords(words, wordsCount);
}

void findAndPrintAll(struct keysPredict* kt, char* word ) {
    struct node* result = keysPredictFind(kt, word);
    printf("Find: %s = %i\n", word, result==0);
}

int main() {

    // COMPLETAR

    // A Continuacion dejamos algunos ejemplos de como
    // llamar a las funciones pedidas. Este codigo debe
    // ser borrado / modificado.


    // strLen
    int len = strLen("aro");
    printf("strLen(\"aro\") -> \"%i\"\n", len);
    printf("\n");

    // strDup
    char* dup = strDup("aro");
    printf("strDup(\"aro\") -> \"%s\"\n", dup);
    free(dup);
    printf("\n");

    // Nuestro testing para funciones del ejercicio 2
    /*
    // struct node* findNodeInLevel(struct node** list, char character)
    struct keysPredict* kt = (struct keysPredict*)malloc(sizeof(struct keysPredict));

    struct node* n1 = (struct node*)malloc(sizeof(struct node));
    struct node* n2 = (struct node*)malloc(sizeof(struct node));
    struct node* n3 = (struct node*)malloc(sizeof(struct node));
    n1->character = 'a';
    n1->end = 0;
    n1->next = 0;
    n1->word = 0;
    n1->down  = n2;
    n2->character = 'r';
    n2->end = 0;
    n2->next = 0;
    n2->word = 0;
    n2->down = n3;
    n2->character = 'o';
    n3->end = 1;
    n3->next = 0;
    n3->word = dup;
    n3->down = 0;

    char character= 'a';

    struct node* nt = (struct node*)malloc(sizeof(struct node));
    nt = findNodeInLevel(&n1, character);
    //printf("Encontramos letra 'a' (1), no encontramos (0) - Resultado: %p\n", (void*)nt);
    printf("Encontramos letra 'a', no encontramos (0) - Resultado: %c\n", nt->character);

    struct node* nn1 = (struct node*)malloc(sizeof(struct node));
    struct node* nn2 = (struct node*)malloc(sizeof(struct node));
    struct node* nn3 = (struct node*)malloc(sizeof(struct node));

    struct node* nnt = (struct node*)malloc(sizeof(struct node));
    nnt = findNodeInLevel(&nn1, character);
    printf("Encontramos letra 'a', no encontramos (0) - Resultado: %p\n", (void*)nnt);

    // struct node* addSortedNewNodeInLevel(struct node** list, char character)

    struct node* n11 = (struct node*)malloc(sizeof(struct node));
    struct node* n12 = (struct node*)malloc(sizeof(struct node));
    struct node* n13 = (struct node*)malloc(sizeof(struct node));

    struct node* n21 = (struct node*)malloc(sizeof(struct node));
    struct node* n22 = (struct node*)malloc(sizeof(struct node));
    struct node* n23 = (struct node*)malloc(sizeof(struct node));

    struct node* n31 = (struct node*)malloc(sizeof(struct node));
    struct node* n32 = (struct node*)malloc(sizeof(struct node));
    struct node* n33 = (struct node*)malloc(sizeof(struct node));


    n11->character = 'a';
    n11->end = 0;
    n11->next = n12;
    n11->word = 0;
    n11->down  = n21;

    n12->character =  'b';
    n12->end = 0;
    n12->next = n13;
    n12->word = 0;
    n12->down = 0;

    n13->character = 'd';
    n13->end = 0;
    n13->next = 0;
    n13->word = 0;
    n13->down = 0;

    n21->character = 'b';
    n21->end = 0;
    n21->next = n22;
    n21->word = 0;
    n21->down  = n31;

    n22->character =  'c';
    n22->end = 0;
    n22->next = n23;
    n22->word = 0;
    n22->down = 0;

    n23->character = 'd';
    n13->end = 0;
    n13->next = 0;
    n13->word = 0;
    n13->down = 0;

    n31->character = 'a';
    n31->end = 0;
    n31->next = n32;
    n31->word = 0;
    n31->down  = 0;

    n32->character = 'b';
    n32->end = 0;
    n32->next = n33;
    n32->word = 0;
    n32->down  = 0;

    n33->character = 'c';
    n33->end = 0;
    n33->next = 0;
    n33->word = 0;
    n33->down  = 0;

    kt->first = n11;
    kt->totalKeys = 3;
    kt->totalWords = 0;

    printf("El caracter siguiente deberÃ­a ser b:  %c\n", addSortedNewNodeInLevel(&n11->down, 'a')->next->character);
    keysPredictPrint(kt);


    */

    // Testing oficial ejercicio 3

    // keysPredict
    struct keysPredict* kt = keysPredictNew();

    // keysPredict - crear un diccionario
    keysPredictAddWord(kt, "papanatas");

    keysPredictAddWord(kt, "zanahoria");
    keysPredictAddWord(kt, "oreja");
    keysPredictAddWord(kt, "ricardo");
    keysPredictAddWord(kt, "zaz");
    keysPredictAddWord(kt, "a");
    keysPredictAddWord(kt, "");
    keysPredictAddWord(kt, "b");
    keysPredictAddWord(kt, "ab");
    keysPredictAddWord(kt, "abfff");
    keysPredictAddWord(kt, "abfgato");
    keysPredictAddWord(kt, "bebe");
    keysPredictAddWord(kt, "pata");
    keysPredictPrint(kt);

    // keysPredict - listar todas las palabras
    char** words, **words2;
    int wordsCount;
    words = keysPredictListAll(kt, &wordsCount);
    printf("Palabras encontradas: \n");
    for(int i=0; i<wordsCount; i++) {
        printf("\"%s\"\n", words[i]);
    }
    printf("Palabras con prefijo \"za\": \n");
    words2 = keysPredictRun(kt, "za", &wordsCount);
    for(int i=0; i<2; i++) {
        printf("\"%s\"\n", words2[i]);
    }
    printf("%i", keysPredictCountWordAux(kt->first));
    deleteArrayOfWords(words, wordsCount);

    // keysPredict - encontrar palabras

    findAndPrintAll(kt, "arotu");
    findAndPrintAll(kt, "pata");
    findAndPrintAll(kt, "a");
    findAndPrintAll(kt, "zazz");

    // keysPredict - predecir palabras

    predictAndPrintAll(kt,"or");
    predictAndPrintAll(kt,"ab");
    predictAndPrintAll(kt,"pa");
    predictAndPrintAll(kt,"pap");
    predictAndPrintAll(kt,"q");
    predictAndPrintAll(kt,"zap");

    // keysPredict - predecir palabras

    keysPredictRemoveWord(kt,"");
    keysPredictRemoveWord(kt,"zaz");
    keysPredictRemoveWord(kt,"aaa");
    keysPredictRemoveWord(kt,"papa");
    keysPredictRemoveWord(kt,"pata");
    keysPredictPrint(kt);

    // keysPredict - borrar diccionario
    keysPredictDelete(kt);
    return 0;
}