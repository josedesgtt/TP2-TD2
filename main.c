#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/*
Ejercicio 5 (Uso de inteligencia artificial)

1) En el trabajo no se hizo uso de la IA como herramienta de asistencia a la hora de la resolución de ejercicios.
2) Tomando en cuenta lo dicho en la pregunta anterior, no es posible responder esta pregunta.
3) No nos hemos encontrado con alguna dificultad a la hora de usar IA por el mismo hecho de que no la usamos.
4) Con respecto a este lenguaje no. Nosotros sí creemos que puede llegar a ser de utilidad pero en este trabajo no fue necesario la asistencia de esta herramienta.
*/

void predictAndPrintAll(struct keysPredict* kt, char* partialWord ) {
    char** words;
    int wordsCount;
    words = keysPredictRun(kt, partialWord, &wordsCount);
    printf("Predicts (%i): %s = ", wordsCount, partialWord);
    for(int i=0; i<wordsCount; i++) {
        printf("%s, ", words[i]);
    }
    printf("\n");
    deleteArrayOfWords(words, wordsCount);
    free(words);
}

void findAndPrintAll(struct keysPredict* kt, char* word ) {
    struct node* result = keysPredictFind(kt, word);
    printf("Find: %s = %i\n", word, result==0);
}

// TESTING DEL CÓDIGO
int main() {

    // EJERCICIO 1
    // Preraramos las variables para testear
    char* len1 = "aro";
    char* len2 = "abcdefghijklmn-opqrstuvwxyz0123456789";
    char* len3 = "dicho";
    char* len4 = "o";

    // int strLen(char *src)
    printf("Probando strLen(char *src);\n");
    printf("strLen(\"%s%s%i%s", len1, "\") -> ", strLen(len1), "\n");
    printf("strLen(\"%s%s%i%s", len2, "\") -> ", strLen(len2), "\n");
    printf("strLen(\"%s%s%i%s", len3, "\") -> ", strLen(len3), "\n");
    printf("strLen(\"%s%s%i%s", len4, "\") -> ", strLen(len4), "\n");

    // char* strDup(char *src)
    char* dup1 = strDup(len1);
    char* dup2 = strDup(len2);
    char* dup3 = strDup(len3);
    char* dup4 = strDup(len4);
    printf("\nProbando strDup(char *src);\n");
    printf("strDup(\"%s%s%s%s", len1, "\") -> \"", dup1, "\"\n");
    printf("strDup(\"%s%s%s%s", len2, "\") -> \"", dup2, "\"\n");
    printf("strDup(\"%s%s%s%s", len3, "\") -> \"", dup3, "\"\n");
    printf("strDup(\"%s%s%s%s", len4, "\") -> \"", dup4, "\"\n");
    printf("\n");

    // EJERCICIO 2
    // Preparamos las variables para testear
    struct node *n1 = (struct node*)malloc(sizeof(struct node)),*n2 = (struct node*)malloc(sizeof(struct node)), *n3 = (struct node*)malloc(sizeof(struct node));
    initNode(n1,'a',0,n2,0,0);
    initNode(n2,'r',0,n3,0,0);
    initNode(n3,'o',0,0,0,dup1);
    free(dup1);
    free(dup2);
    free(dup3);
    free(dup4);

    struct node *n11 = (struct node*)malloc(sizeof(struct node)), *n12 = (struct node*)malloc(sizeof(struct node)), *n13 = (struct node*)malloc(sizeof(struct node)), *n21 = (struct node*)malloc(sizeof(struct node)), *n22 = (struct node*)malloc(sizeof(struct node)), *n23 = (struct node*)malloc(sizeof(struct node)), *n31 = (struct node*)malloc(sizeof(struct node)), *n32 = (struct node*)malloc(sizeof(struct node)), *n33 = (struct node*)malloc(sizeof(struct node));
    initNode(n11,'a',n12,n21,0,0);
    initNode(n12,'b',n13,0,0,0);
    initNode(n13,'d',0,0,0,0);
    initNode(n21,'b',n22,n31,0,0);
    initNode(n22,'c',n23,0,0,0);
    initNode(n23,'d',0,0,0,0);
    initNode(n31,'a',n32,0,0,0);
    initNode(n32,'b',n33,0,0,0);
    initNode(n33,'c',0,0,0,0);

    // struct node *findNodeInLevel(struct node **list, char character)
    printf("Buscamos letras con findNodeInLevel (Si=1/No=0) \n-Primer nivel:\n");
    printf("Encontramos \'a\'?: %i%s", !(findNodeInLevel(&n1, 'a') == 0), "\n");
    printf("Encontramos \'y\'?: %i%s", !(findNodeInLevel(&n1, 'y') == 0), "\n");
    printf("Encontramos \'8\'?: %i%s", !(findNodeInLevel(&n1, '8') == 0), "\n");
    printf("-Segundo nivel:\n");
    printf("Encontramos \'r\'?: %i%s", !(findNodeInLevel(&n2, 'r') == 0), "\n");
    printf("Encontramos \'t\'?: %i%s", !(findNodeInLevel(&n2, 't') == 0), "\n");
    printf("Encontramos \'7\'?: %i%s", !(findNodeInLevel(&n2, '7') == 0), "\n");
    printf("-Tercer nivel:\n");
    printf("Encontramos \'o\'?: %i%s", !(findNodeInLevel(&n3, 'o') == 0), "\n");
    printf("Encontramos \'w\'?: %i%s", !(findNodeInLevel(&n3, 'w') == 0), "\n");
    printf("Encontramos \'4\'?: %i%s", !(findNodeInLevel(&n3, '4') == 0), "\n");


    // struct node* addSortedNewNodeInLevel(struct node** list, char character)
    struct keysPredict* kt_aux = keysPredictNew();
    kt_aux->first = n11;
    printf("\nAgregamos letras con addSortedNewNodeInLevel\nAntes de añadir:\n");
    keysPredictPrint(kt_aux);
    printf("\nAñadimos \'c\' en el primer nivel, \'a\' en el segundo y \' \':\n");
    kt_aux->first = addSortedNewNodeInLevel(&(kt_aux->first), 'c');
    kt_aux->first->down = addSortedNewNodeInLevel(&kt_aux->first->down, 'a');
    kt_aux->first->down->down = addSortedNewNodeInLevel(&kt_aux->first->down->down, ' ');
    keysPredictPrint(kt_aux);
    keysPredictDelete(kt_aux);
    free(n1);
    free(n2);
    free(n3);

    // EJERCICIO 3

    struct keysPredict* kt = keysPredictNew();

    // Testeamos con casos chicos
    printf("\nTesteamos casos con keysPredict chicos:\n");
    keysPredictAddWord(kt, "alfajor");
    keysPredictAddWord(kt, "canoa");
    keysPredictAddWord(kt, "rinoceronte");
    keysPredictAddWord(kt, "casa");
    keysPredictAddWord(kt, "rino");
    keysPredictAddWord(kt, "camion");
    keysPredictPrint(kt);

    predictAndPrintAll(kt,"c");
    predictAndPrintAll(kt,"ca");
    predictAndPrintAll(kt, "cam");
    predictAndPrintAll(kt, "can");
    predictAndPrintAll(kt,"casa");
    predictAndPrintAll(kt, "camion");
    predictAndPrintAll(kt, "c");
    predictAndPrintAll(kt,"casas");


    // Testeamos con casos grandes: Usamos el predict.c y dicc.txt, probamos todas las combinaciones de prefijos de dos letras posibles.
    // También probamos borrando la mitad y más del diccionario.

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
    predictAndPrintAll(kt, "a");

    // keysPredict - predecir palabras

    keysPredictRemoveWord(kt,"");
    keysPredictRemoveWord(kt,"zaz");
    keysPredictRemoveWord(kt,"aaa");
    keysPredictRemoveWord(kt,"papa");
    keysPredictRemoveWord(kt,"pata");
    keysPredictRemoveWord(kt,"q");
    keysPredictPrint(kt);

    // keysPredict - borrar diccionario
    keysPredictDelete(kt);
    return 0;
}

