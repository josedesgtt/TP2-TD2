#include "utils.h"

/*
Devuelve la longitud de una cadena de texto.
*/
int strLen(char *src) {
  int i = 0;
  // Itera siempre y cuando no se detecte el null termina
  while (src[i] != '\0' && src != "")
    i++;
  return i;
}

/*
Devuelve una copia de una cadena de texto.
*/
char* strDup(char* src) {
  //Declaramos el size y el espacio de memoria donde vamos a guardar la copa (+1 por el null termina)
  int size = strLen(src);
  char* copia = (char *)malloc(sizeof(char)*(size+1));
  copia[size] = '\0';
  // Va copiando caracter a caracter
  for (int i = 0; i < size; i++)
    copia[i] = (char)src[i];
  return copia;
}

/*
Crea una nueva instancia vacía de tipo keysPredict.
*/
struct keysPredict *keysPredictNew() {
  struct keysPredict *kt = (struct keysPredict *)malloc(sizeof(struct keysPredict));
  kt->first = 0;
  kt->totalKeys = 0;
  kt->totalWords = 0;
  return kt;
}

/*
Agrega una palabra a un keysPredict.
*/
void keysPredictAddWord(struct keysPredict *kt, char *word) {
  struct node *v_nodo; // Nodo para iterar
  char *n_word = strDup(word); // Copiamos palabra para el ultimo nodo de la palabra
  if (strLen(word) > 0) { // Sólo se ejecuta si no le pasamos un string vacío
    if (kt->first == 0) { // En caso de que kt este completamente vacio
      kt->first = addSortedNewNodeInLevel(&kt->first, word[0]);
      v_nodo = kt->first;
    } else { //Si kt tiene algo
      if (findNodeInLevel(&kt->first, word[0]) == NULL) { //Se fija si se encuentra el primer nodo
        kt->first = addSortedNewNodeInLevel(&kt->first, word[0]); //Si no está, lo agrega
      } 
      v_nodo = findNodeInLevel(&kt->first, word[0]); //Guardamos el puntero al primer nodo
    }
    kt->totalKeys++;
    for (int i = 1; i < strLen(word); i++) { // Por cada letra en palabra...
      if (v_nodo->down == 0) { //En caso de que en el nivel de abajo no haya nada
        v_nodo->down = addSortedNewNodeInLevel(&v_nodo->down, word[i]);
      } else if (findNodeInLevel(&v_nodo->down, word[i]) == NULL) { // En caso de que sí haya algo, pero de que ese caracter no esté
        v_nodo->down = addSortedNewNodeInLevel(&v_nodo->down, word[i]);
      }
      v_nodo = findNodeInLevel(&v_nodo->down, word[i]); //Guardamos el puntero al nodo en cuestión
      kt->totalKeys++;
    }
    // Una vez que llega al final de la palabra, guarda la palabra en el ultimo nodo
    v_nodo->end = 1;
    v_nodo->word = n_word;
    kt->totalWords++;
  }
}

/*
Borra una palabra de un keysPredict.
*/
void keysPredictRemoveWord(struct keysPredict *kt, char *word) {
  if (strLen(word) > 0) { // En caso de que la palabra no esté vacía
     struct node *v_nodo = keysPredictFind(kt, word); // Busca el último nodo de la palabra
    if (v_nodo != 0) { // En caso de que lo encuentre
      v_nodo->end = 0;
      free(v_nodo->word); // Borra la palabra
      kt->totalWords--;
    }
    free(v_nodo);
  }
}

/*
Busca una palabra en un keysPredict y retorna el puntero a su último nodo.
*/
struct node *keysPredictFind(struct keysPredict *kt, char *word) {
  if (strLen(word) > 0) { // Se ejecuta sólo si no le pasamos una palabra vacía
    struct node *v_nodo = (struct node *)malloc(sizeof(struct node));
    v_nodo = kt->first;
    for (int i = 0; i < strLen(word); i++) { // Por cada letra en palabra...
      // Al nodo a le asignamos (en caso de existir) el nodo del i-ésimo nivel cuya letra sea la i-ésima de la palabra
      struct node *a = findNodeInLevel(&v_nodo,word[i]);
      if (a == 0) { // Si el nodo no existe...
        return 0;
      }
      if (i == strLen(word) - 1) { //En caso de que lleguemos al último caracter de la palabra
        if (a->end == 1) { //Si está cargada la palabra, retorna el puntero a este nodo
          return a;
        } else { //Sino, no retorna nada
          return 0;
        }
      }
      v_nodo = a;
      v_nodo = v_nodo->down; //Necesario para iterar
    }
  } else { // En caso de que nos hayan pasado una palabra vacía
    return 0;
  }
}

/*
Función auxiliar correspondiente a keysPredictRun, busca (de existir) el nivel de abajo del último nodo del prefijo solicitado.
*/
struct node* recursiveFindPrefix(struct node* n, char* partialWord) {
  struct node* v_node = (struct node *)malloc(sizeof(struct node));
  if (strLen(partialWord) != 1) { //En caso de que no hayamos llegado a la última letra del prefijo
    v_node = findNodeInLevel(&n, partialWord[0]); //Busca la letra correspondiente
    if (v_node != NULL) { //Si existe, sigue iterando
      return recursiveFindPrefix(v_node->down, partialWord + 1); 
    } else { //Sino, retorna 0
      return 0;
    }
  }
  v_node = findNodeInLevel(&n, partialWord[0]); //Busca la última letra
  if (v_node != NULL) { //Si la encuentra, retorna el puntero al primer nodo del nivel de abajo
    return v_node->down;
  } else { //Sino, no retorna nada
    return 0;
  }
}

/*
Función auxiliar para keysPredictListAll. Devuelve sólo
*/
void recursivePredictListAll(struct node *n, char **list, int totalWords, int *wordsCount) {
  if (totalWords != 0) {
    if (n->next != 0) {
      recursivePredictListAll(n->next, list, totalWords, wordsCount);
    }
    if (n->down != 0) {
      recursivePredictListAll(n->down, list, totalWords, wordsCount);
    }
    if (n->end != 0) {
      list[*wordsCount] = strDup(n->word);
      totalWords--;
      (*wordsCount)++;
    }
  }
}

char **keysPredictRun(struct keysPredict *kt, char *partialWord, int *wordsCount) {
  *wordsCount = 0;
  char  **words;
  struct node *firstPrefixNode = (struct node*)malloc(sizeof(struct node)); // Alojamos memoria dinámica para el nodo que
  // contiene el prefijo
  firstPrefixNode = recursiveFindPrefix(kt->first,partialWord); // Encontramos el primer nodo que tenga el prefijo
  // Alojamos memoria dinámica                                               // para el arreglo de palabras
  if (firstPrefixNode != 0) { // Si el primer nodo que tiene el prefijo no es nulo...
    int wordsFromFirstPrefixNode = keysPredictCountWordAux(firstPrefixNode);
    if (wordsFromFirstPrefixNode != 0) {
      words = (char **)malloc(sizeof(char) *wordsFromFirstPrefixNode);
      recursivePredictListAll(firstPrefixNode, words, wordsFromFirstPrefixNode, wordsCount); // A partir del primer nodo que tenga prefijo listamos a
    // todas las palabras en words
    } else {
      words = 0;
    }
  } else {
    words = 0;
  }
  return words; // Retornamos el arreglo de palabras
}

int keysPredictCountWordAux(struct node *n) {
    if (n->next != 0 && n->down != 0){
        if (n->end != 0){
            return keysPredictCountWordAux(n->next)+keysPredictCountWordAux(n->down)+1;
        } else {
            return keysPredictCountWordAux(n->next)+keysPredictCountWordAux(n->down);
        }
    } else if (n->next != 0){
        if (n->end != 0){
            return keysPredictCountWordAux(n->next)+1;
        } else {
            return keysPredictCountWordAux(n->next);
        }
    } else if (n->down != 0){
        if (n->end != 0){
            return keysPredictCountWordAux(n->down)+1;
        } else {
            return keysPredictCountWordAux(n->down);
        }
    } else {
        if (n->end !=0) {
            return 1;
        } else {
            return 0;
        }
    }
}

char **keysPredictListAll(struct keysPredict *kt, int *wordsCount) {
  *wordsCount = 0;
  char **ktWords = (char **)malloc(sizeof(char *) * kt->totalWords);
  recursivePredictListAll(kt->first, ktWords, kt->totalWords, wordsCount);
  return ktWords;
}

void recursiveDelete(struct node *n) {
  if (n->next != 0) {
    recursiveDelete(n->next);
  }
  if (n->down != 0) {
    recursiveDelete(n->down);
  }
  if (n->end != 0) {
    deleteArrayOfWords(&(n->word), 1);
  }
  free(n);
}

void keysPredictDelete(struct keysPredict *kt) {
  struct node *var_node = (struct node *)malloc(sizeof(struct node));
  var_node = kt->first;
  recursiveDelete(var_node);
  free(kt);
}

void keysPredictPrint(struct keysPredict *kt) {
  printf("--- Predict --- Keys: %i Words: %i\n", kt->totalKeys, kt->totalWords);
  keysPredictPrintAux(kt->first, 0);
  printf("---\n");
}

void keysPredictPrintAux(struct node *n, int level) {
  if (!n)
    return;
  struct node *current = n;
  while (current) {
    for (int i = 0; i < level; i++)
      printf(" |   ");
    if (current->end) {
      printf("[%c]\n", current->character);
    } else {
      printf(" %c \n", current->character);
    }
    keysPredictPrintAux(current->down, level + 1);
    current = current->next;
  }
}

void initNode(struct node* node, char input_character, struct node* input_next, struct node* input_down, int input_end, char* input_word) {
  node->character = input_character;
  node->next = input_next;
  node->down  = input_down;
  node->end = input_end;
  node->word = input_word;
}

// Auxiliar functions



// Paso las pruebas
// Justificación: Pendiente
struct node *findNodeInLevel(struct node **list, char character) {
  struct node *varNodo =
      *list; // Desreferenciamos list para obtener un puntero al nodo
  while (varNodo != 0) {
    if (varNodo->character == character) {
      return varNodo;
    }
    varNodo = varNodo->next;
  }
  return 0;
}

/*
struct node* addSortedNewNodeInLevel(struct node** list, char character)
Dada una lista de nodos, agrega un nuevo nodo a la lista de forma ordenada.
Este nodo llevará el caracter pasado por parámetro y el resto de sus datos en
cero.
*/

struct node* addSortedNewNodeInLevel(struct node **list, char character) {
  struct node* var_nodo = *list;
  struct node* newNode = (struct node* )malloc(sizeof(struct node));
  float aux_char, aux_var_nodo_char, aux_var_nodo_next_char;
  newNode->character = character;
  newNode->down = 0;
  newNode->end = 0;
  newNode->next = 0;
  newNode->word = 0;
  aux_char = (float)character;
  if (aux_char == 45.0) {
    aux_char = 110.5;
  }
  while (var_nodo != 0 && var_nodo->next != 0) { // Más de dos nodos
    // Agregar en medio
    aux_var_nodo_char = (float)var_nodo->character;
    aux_var_nodo_next_char = (float)var_nodo->next->character;
    if (aux_var_nodo_char == 45.0) {
      aux_var_nodo_char = 110.5;
    }
    if (aux_var_nodo_next_char == 45.0) {
      aux_var_nodo_next_char = 110.5;
    }
    if (aux_var_nodo_char <= aux_char && aux_var_nodo_next_char >= aux_char) {
      newNode->next = var_nodo->next;
      var_nodo->next = newNode;
      return *list;
    } else if (var_nodo->next->next == 0 && aux_var_nodo_next_char < aux_char) {
      var_nodo->next->next = newNode;
      return *list;
    } else if (aux_var_nodo_char > aux_char) {
      newNode->next = var_nodo;
      //list = newNode;
      return newNode;
    }
    var_nodo = var_nodo->next;
  }
  if (var_nodo == 0) {
    //list = newNode;
    return newNode;
  } else {
    aux_var_nodo_char = (float)var_nodo->character;
    if (aux_var_nodo_char == 45.0) {
      aux_var_nodo_char = 110.5;
    }
    if (aux_var_nodo_char < aux_char) {
      var_nodo->next = newNode;
      return var_nodo;
    }
    else if (aux_var_nodo_char > aux_char) {
      newNode->next = var_nodo;
      //list = newNode;
      return newNode;
    }
  }
}
/*
Dado un puntero a un arreglo de punteros a strings y el tamaño del arreglo. Se
encarga de borrar una a una las strings y ademas borrar el arreglo.
*/

void deleteArrayOfWords(char **words, int wordsCount) {
  for (int i = wordsCount-1; i >= 0; i--) {
    free(*(words + i)); // Liberamos la memoria del puntero a la i-ésima palabra
  }
}
