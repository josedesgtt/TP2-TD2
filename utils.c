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

/*
Agrega una nueva palabra a la estructura keysPredict. Para esto debe ir recorriendo cada lista
y en cada nivel agregar cada letra de la palabra en caso de ser necesario. Al final, en el último
nodo, correspondiente a la última letra de la palabra, deberá hacer una copia de la palabra y
agregarla en el nodo. Además deberá marcar este nodo como final, indicando un 1 en end.
*/

void keysPredictAddWord(struct keysPredict* kt, char* word) {
    struct node* v_nodo = (struct node *) malloc(sizeof(struct node)); // Alojamos memoria para un nuevo nodo
    v_nodo = kt->first; // Asignamos a v_nodo la dirección del primer nodo del primer nivel
    char* n_word = strDup(word); // Copiamos palabra para el último nodo de la palabra
    for (int i=0; i<strLen(word); i++) {    // Por cada letra en palabra...
        struct node* a = findNodeInLevel(&v_nodo, word[i]);  // Al nodo a le asignamos (en caso de existir) el nodo del i-ésimo nivel cuya letra sea la i-ésima de la palabra
        if (a == NULL) {   // Si el nodo no existe...
            addSortedNewNodeInLevel(&v_nodo, word[i]);  //  Lo creamos
        }
        if (i==strLen(word)-1){ // Si estamos en trabajando con el último nodo...
            a = findNodeInLevel(&v_nodo, word[i]); //
            // Configuramos el nodo
            a->word = n_word;
            a->end = 1;
        }
        v_nodo = v_nodo->down;

     }
}

/*
Busca el nodo correspondiente a la ultima letra de la palabra a borrar y borra la palabra
almacenada en dicho nodo. Adicionalmente marca el nodo con un 0 en end. Notar que los nodos
de las letras que correspondian a la palabra no son borrados, sino que solo se borra la palabra
del ultimo nodo. Es decir, la estructura va a quedar con nodos que podran no existir para las
palabras que realmente tiene la estructura.
*/
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
        if (a == NULL) {    // Si el nodo no existe...
            i = strlen(word);
        }
        if (i==strLen(word)-1){ // Si estamos en trabajando con el último nodo...
            a->end = 0;
            free(a->word);
        }
        v_nodo = v_nodo->down;
    }
}

/*
Busca en la estructura el nodo correspondiente a la palabra indicada, de no encontrarlo retorna
un cero. Para esto debe recorrer la estructura segun cada letra de la palabra. El nodo retornado
sera valido si esta marcado en end con 1 y el puntero word tiene la palabra buscada.
*/

struct node* keysPredictFind(struct keysPredict* kt, char* word) {
    struct node* v_nodo = (struct node*)malloc(sizeof(struct node));
    v_nodo = kt->first;
    for (int i=0; i<strLen(word); i++) {    // Por cada letra en palabra...
        struct node* a = findNodeInLevel(&v_nodo, word[i]);  // Al nodo a le asignamos (en caso de existir) el nodo del i-ésimo nivel cuya letra sea la i-ésima de la palabra
        if (a == NULL) {    // Si el nodo no existe...
            return 0;
        }
        if (i==strLen(word)){
            if(a->end == 1 && a->word == *word){
                return a;
            } else {
                return 0;
            }
        }
        v_nodo = v_nodo->down;
    }
}

/*
Dadas las primeras letras de una palabra, busca todas las palabras que contenga el prejo
indicado. Para esto debe recorrer la estructura hasta alcanzar la ultima letra del prejo. A
partir de ese nodo, debe recontruir todas las palabras que se puedan armar con la subestructura
restante. Debe retornar estas palabras en una estructura de tipo arreglo de punteros a string
(char**) como valor de retorno de la funcion. La cantidad de elementos de este arreglo de
punteros estara dada por las palabras encontradas y debera retornarce en el puntero wordsCount
pasado como parametro.
*/
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

/*
struct node* findNodeInLevel(struct node** list, char character)
Dada una lista de nodos, retorna un puntero al nodo que tiene el caracter pasado por parámetro.
*/

struct node* findNodeInLevel(struct node** list, char character) {
    struct node* var_nodo = *list;
    while (var_nodo != NULL && var_nodo->next != NULL) {
        if (var_nodo->character == character) {
            return var_nodo;
        }
        var_nodo =  var_nodo->next;
    }
    return NULL;
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
    newNode->down = NULL;
    newNode->end = NULL;
    newNode->next = NULL;
    newNode->word = NULL;
    while (var_nodo != NULL && var_nodo->next != NULL){
        if (var_nodo->character <= character && var_nodo->next->character >= character){
            newNode->next = var_nodo->next;
            var_nodo->next = newNode;
            return *list;
        } else if (var_nodo->next->next == NULL && var_nodo->next->character < character) {
            var_nodo->next->next = newNode;
            return *list;
        } else if (var_nodo->character > character) {
            var_nodo = newNode;
            return newNode;
        }
        var_nodo = var_nodo->next;
    }
    if (var_nodo == NULL){
        var_nodo = newNode;
        return var_nodo;
    } else if (var_nodo->character < character){
        var_nodo->next = newNode;
        return var_nodo;
    } else if (var_nodo->character > character){
        newNode->next = var_nodo;
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
