#include "utils.h"


// Paso las pruebas
// Justificación: Pendiente
int strLen(char* src) {
    int i = 1;
    while (src[i] != '\0') i++;
    return i;
}

// Paso las pruebas
// Justificación: Pendiente
char* strDup(char* src) {
    int size = strLen(src);
    char* copia = (char*) malloc(size);
    for (int i=0; i<size; i++) copia[i] = (char) src[i];
    return copia;
}

// Paso las pruebas
// Justificación: Pendiente
struct keysPredict* keysPredictNew() {
    struct keysPredict* kt = (struct keysPredict*)malloc(sizeof(struct keysPredict));
    kt->first = 0;
    kt->totalKeys = 0;
    kt->totalWords = 0;
    return kt;
}


// No paso las pruebas
// Justificación: Pendiente
void keysPredictAddWord(struct keysPredict* kt, char* word) {
    struct node* varNode = (struct node *)malloc(sizeof(struct node));
    struct node* a = (struct node *)malloc(sizeof(struct node));
    char* newWord = strDup(word);
    for (int i=0; i<strLen(word); i++) {
        if (varNode == 0) {
            varNode = addSortedNewNodeInLevel(&(kt->first), word[i]);
            varNode = varNode->down;
            kt->totalKeys++;
        } else {
            a = findNodeInLevel(&varNode, word[i]);
            if (a == 0) {
                a = addSortedNewNodeInLevel(&varNode, word[i]);
                varNode = a->down;
                kt->totalKeys++;
            }
            if (i==strLen(word)-1){
                a = findNodeInLevel(&varNode, word[i]);
                a->word = newWord;
                a->end = 1;
            }
        }
    }
    kt->totalWords++;
}

void keysPredictRemoveWord(struct keysPredict* kt, char* word) {
    struct node* v_nodo = (struct node*)malloc(sizeof(struct node));
    v_nodo = kt->first;
    /*
    int i = 0;
    while (i<strLen(word)-1){
        v_nodo = v_nodo->down;
        i++;
    }
    findNodeInLevel(&v_nodo, *(word + strLen(word) - 1));
    // ult: -> a | b | c | c | d
    */

    for (int i=0; i<strLen(word); i++) {    // Por cada letra en palabra...
        struct node* a = findNodeInLevel(&v_nodo, word[i]);  // Al nodo a le asignamos (en caso de existir) el nodo del i-ésimo nivel cuya letra sea la i-ésima de la palabra
        if (a == 0) {    // Si el nodo no existe...
            i = strLen(word);
        }
        if (i==strLen(word)-1){ // Si estamos en trabajando con el último nodo...
            a->end = 0;
            free(a->word);
        }
        v_nodo = v_nodo->down;
    }
}

struct node* keysPredictFind(struct keysPredict* kt, char* word) {
    struct node* v_nodo = (struct node*)malloc(sizeof(struct node));
    v_nodo = kt->first;
    for (int i=0; i<strLen(word); i++) {    // Por cada letra en palabra...
        struct node* a = findNodeInLevel(&v_nodo, word[i]);  // Al nodo a le asignamos (en caso de existir) el nodo del i-ésimo nivel cuya letra sea la i-ésima de la palabra
        if (a == 0) {    // Si el nodo no existe...
            return 0;
        }
        if (i==strLen(word)){
            if(a->end == 1 && a->word == word){
                return a;
            } else {
                return 0;
            }
        }
        v_nodo = v_nodo->down;
    }
}

char** keysPredictRun(struct keysPredict* kt, char* partialWord, int* wordsCount) {
    /*
    -
    */
}

int keysPredictCountWordAux(struct node* n) {

    // COMPLETAR
}

char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {

    // COMPLETAR

    return 0;
}

void recursiveDelete(struct node* n){
	if (n->next != 0){
		recursiveDelete(n->next);
	}
	if (n->down != 0){
		recursiveDelete(n->down);
	}
	if (n->word != 0){
		deleteArrayOfWords(&n->word, 1);
	}
	free(n);
}

void keysPredictDelete(struct keysPredict* kt) {
	struct node *var_node = malloc(sizeof(struct node));
	var_node = kt->first;
	recursiveDelete(var_node);
	free(kt);
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

// Paso las pruebas
// Justificación: Pendiente
struct node* findNodeInLevel(struct node** list, char character) {
    struct node* varNodo = *list; // Desreferenciamos list para obtener un puntero al nodo
    while (varNodo != 0) {
        if (varNodo->character == character) {
            return varNodo;
        }
        varNodo =  varNodo->next;
    }
    return 0;
}

/*
struct node* addSortedNewNodeInLevel(struct node** list, char character)
Dada una lista de nodos, agrega un nuevo nodo a la lista de forma ordenada. Este nodo llevará
el caracter pasado por parámetro y el resto de sus datos en cero.
*/

struct node* addSortedNewNodeInLevel(struct node** list, char character) {
    struct node* var_nodo = *list;
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->character = character;
    newNode->down = 0;
    newNode->end = 0;
    newNode->next = 0;
    newNode->word = 0;
    while (var_nodo != 0 && var_nodo->next != 0){ // Más de dos nodos
        // Agregar en medio
        if (var_nodo->character <= character && var_nodo->next->character >= character){
            newNode->next = var_nodo->next;
            var_nodo->next = newNode;
            return *list;
        } else if (var_nodo->next->next == 0 && var_nodo->next->character < character) {
            var_nodo->next->next = newNode;
            return *list;
        } else if (var_nodo->character > character) {
            newNode->next = var_nodo;
            *list = newNode;
            return newNode;
        }
        var_nodo = var_nodo->next;
    }
    if (var_nodo == 0){
        *list = newNode;
        return var_nodo;
    } else if (var_nodo->character < character){
        var_nodo->next = newNode;
        return var_nodo;
    } else if (var_nodo->character > character){
        newNode->next = var_nodo;
        *list = newNode;
        return newNode;
    }
}

/*
Dado un puntero a un arreglo de punteros a strings y el tamaño del arreglo. Se encarga de borrar
una a una las strings y ademas borrar el arreglo.
*/

void deleteArrayOfWords(char** words, int wordsCount) {
    for (int i = 0; i<wordsCount; i++){
        free(*(words + i)); // Liberamos la memoria del puntero a la i-ésima palabra
    }
}
