#include "utils.h"

// Paso las pruebas
// Justificación: Pendiente
int strLen(char *src) {
  int i = 0;
  while (src[i] != '\0' && src != "")
    i++;
  return i;
}

// Paso las pruebas
// Justificación: Pendiente
char *strDup(char *src) {
  int size = strLen(src);
  char *copia = (char *)malloc(size);
  for (int i = 0; i < size; i++)
    copia[i] = (char)src[i];
  return copia;
}

// Paso las pruebas
// Justificación: Pendiente
struct keysPredict *keysPredictNew() {
  struct keysPredict *kt =
      (struct keysPredict *)malloc(sizeof(struct keysPredict));
  kt->first = 0;
  kt->totalKeys = 0;
  kt->totalWords = 0;
  return kt;
}

void keysPredictAddWord(struct keysPredict *kt, char *word) {
  struct node *v_nodo = (struct node *)malloc(sizeof(struct node)); // Alojamos memoria para un nuevo
  char *n_word = strDup(word); // Copiamos palabra para el ultimo nodo de la palabra
  struct node *a = (struct node *)malloc(sizeof(struct node));
  if (strLen(word) > 0) { // Sólo se ejecuta si no le pasamos un string vacío
    if (kt->first == 0) {
      kt->first = addSortedNewNodeInLevel(&kt->first, word[0]);
      v_nodo = kt->first;
    } else {
      if (findNodeInLevel(&kt->first, word[0]) == NULL) {
        kt->first = addSortedNewNodeInLevel(&kt->first, word[0]);
      }
      v_nodo = findNodeInLevel(&kt->first, word[0]);
    }
    kt->totalKeys++;
    for (int i = 1; i < strLen(word); i++) { // Por cada letra en palabra...
      if (v_nodo->down == 0) {
        v_nodo->down = addSortedNewNodeInLevel(&v_nodo->down, word[i]);
      } else if (findNodeInLevel(&v_nodo->down, word[i]) == NULL) {
        v_nodo->down = addSortedNewNodeInLevel(&v_nodo->down, word[i]);
      }
      v_nodo = findNodeInLevel(&v_nodo->down, word[i]);
      kt->totalKeys++;
    }
    v_nodo->end = 1;
    v_nodo->word = n_word;
    kt->totalWords++;
  }
}

void keysPredictRemoveWord(struct keysPredict *kt, char *word) {
  if (strLen(word) > 0) {
    struct node *v_nodo = (struct node *)malloc(sizeof(struct node));
    v_nodo = keysPredictFind(kt, word);
    if (v_nodo != 0) {
      v_nodo->end = 0;
      free(v_nodo->word);
      kt->totalWords--;
    }
  }
}

struct node *keysPredictFind(struct keysPredict *kt, char *word) {
  if (strLen(word) > 0) {
    struct node *v_nodo = (struct node *)malloc(sizeof(struct node));
    v_nodo = kt->first;
    for (int i = 0; i < strLen(word); i++) { // Por cada letra en palabra...
      struct node *a = findNodeInLevel(
          &v_nodo,
          word[i]); // Al nodo a le asignamos (en caso de existir) el nodo del
                    // i-ésimo nivel cuya letra sea la i-ésima de la palabra
      if (a == 0) { // Si el nodo no existe...
        return 0;
      }
      if (i == strLen(word) - 1) {
        if (a->end == 1) {
          return a;
        } else {
          return 0;
        }
      }
      v_nodo = a;
      v_nodo = v_nodo->down;
    }
  } else {
    return 0;
  }
}

/*
Dadas las primeras letras de una palabra, busca todas las palabras que
contenga el prejo indicado. Para esto debe recorrer la estructura hasta
alcanzar la ultima letra del prejo. A partir de ese nodo, debe recontruir
todas las palabras que se puedan armar con la subestructura restante. Debe
retornar estas palabras en una estructura de tipo arreglo de punteros a string
(char**) como valor de retorno de la funcion. La cantidad de elementos de
este arreglo de punteros estara dada por las palabras encontradas y debera
retornarce en el puntero wordsCount pasado como parametro.
*/
struct node *recursiveFindPrefix(struct node *n, char *partialWord) {
  struct node *v_node = (struct node *)malloc(sizeof(struct node));
  if (strLen(partialWord) != 0) {
    v_node = findNodeInLevel(&n, partialWord[0]);
    if (v_node != NULL) {
      return recursiveFindPrefix(v_node->down, partialWord+1);
    } else {
      return 0;
    }

    // free(v_node);
  }
  return n;
}

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
  struct node *firstPrefixNode = (struct node *)malloc(sizeof(struct node)); // Alojamos memoria dinámica para el nodo que contiene el prefijo
  int wordsFromFirstPrefixNode = keysPredictCountWordAux(firstPrefixNode);
  char ** words = (char **)malloc(sizeof(char*)*wordsFromFirstPrefixNode); // Alojamos memoria dinámica para el arreglo de palabras
  firstPrefixNode = recursiveFindPrefix(kt->first, partialWord); // Encontramos el primer nodo que tenga el prefijo
  if (firstPrefixNode != 0) { // Si el primer nodo que tiene el prefijo no es nulo...
    recursivePredictListAll(firstPrefixNode, words, 2, wordsCount); // A partir del primer nodo que tenga prefijo listamos a todas las palabras en words
  }
  return words; // Retornamos el arreglo de palabras
}

/*
if (n->next == 0 && n->down == 0) {
  if (n->end != 0) return 1;
  else return 0;
} else {
if (n->end != 0) {
  if (n->next != 0) return keysPredictCountWordAux(n->next) + 1;
  if (n->down != 0) return keysPredictCountWordAux(n->down) + 1;
} else {
  if (n->next != 0) return keysPredictCountWordAux(n->next);
  if (n->down != 0) return keysPredictCountWordAux(n->down);
}}
*/
/*
if (n->next != 0) {
  if (n->next->end != 0) return keysPredictCountWordAux(n->next) + 1;
}
if (n->down != 0) {
  if (n->down->end != 0) return keysPredictCountWordAux(n->down) + 1;
}
if (n->end != 0) return 1;
else return 0;
*/
/*
if (n->next != 0 && n->down != 0) {
  if (n->next->end != 0 && n->down->end != 0) return keysPredictCountWordAux(n->next) + keysPredictCountWordAux(n->down) + 2;
  if (n->next->end != 0) return keysPredictCountWordAux(n->next) + 1;
  if (n->down->end != 0) return keysPredictCountWordAux(n->down) + 1;
}
if (n->next != 0) {
  if (n->next->end != 0) return keysPredictCountWordAux(n->next) + 1;
}
if (n->down != 0) {
  if (n->down->end != 0) return keysPredictCountWordAux(n->down) + 1;
}
if (n->end != 0) return 1;
else return 0;
*/
/*
  if (n->next != 0 && n->down != 0) {
      return keysPredictCountWordAux(n->next) + keysPredictCountWordAux(n->down) + 2;
  }
  if (n->next != 0) {
      if (n->next->end != 0) return keysPredictCountWordAux(n->next) + 1;
  }
  if (n->down != 0) {
      if (n->down->end != 0) return keysPredictCountWordAux(n->down) + 1;
  }
  if (n->end != 0) return 1;
  else return 0;
*/
/*
if(n->next != 0 && n->down != 0){
    return keysPredictCountWordAux(n->next) + keysPredictCountWordAux(n->down);
} else if (n->next !=  0) {
    return keysPredictCountWordAux (n->next);
} else if (n->down != 0) {
    return keysPredictCountWordAux (n->down);
} else {
    if (n->end != 0){
        return 1;
    } else {
        return 0;
    }
}
*/
/*
int wordsCountFromNode = 0;

if (n->next != 0 && n->down != 0){
    wordsCountFromNode = keysPredictCountWordAux(n->next) + keysPredictCountWordAux(n->down);
} else if (n->next !=  0) {
    wordsCountFromNode = keysPredictCountWordAux (n->next);
} else if (n->down != 0) {
    wordsCountFromNode = keysPredictCountWordAux (n->down);
}

if (n->end !=  0){
    return 1 +  wordsCountFromNode;
} else {
    return 0 +  wordsCountFromNode;
}
*/
/* sagrado
int wordsCountFromNode = 0;

if (n->next != 0 && n->down != 0){
    wordsCountFromNode = keysPredictCountWordAux(n->next) + keysPredictCountWordAux(n->down);
} else if (n->next !=  0) {
    wordsCountFromNode = keysPredictCountWordAux (n->next);
} else if (n->down != 0) {
    wordsCountFromNode = keysPredictCountWordAux (n->down);
}

if (n->end !=  0){
    return 1 +  wordsCountFromNode;
} else {
    return 0 + wordsCountFromNode;
}
*/
/* Error de segmentación
if (n->end != 0){
    if (n->next != 0 && n->down != 0){
        return keysPredictCountWordAux(n->next)+keysPredictCountWordAux(n->down)+1;
    } else if (n->next != 0){
        return keysPredictCountWordAux(n->next) + 1;
    } else if (n->down != 0){
        return keysPredictCountWordAux(n->next) + 1;
    }
    return 1;
} else {
    if (n->next != 0 && n->down != 0){
        return keysPredictCountWordAux(n->next)+keysPredictCountWordAux(n->down);
    } else if (n->next != 0){
        return keysPredictCountWordAux(n->next);
    } else if (n->down != 0){
        return keysPredictCountWordAux(n->next);
    }
    return 0;
}
*/
/* funco con variable
int wordsCountFromNode = 0;

if (n->next != 0 && n->down != 0){
    wordsCountFromNode = keysPredictCountWordAux(n->next) + keysPredictCountWordAux(n->down);
} else if (n->next !=  0) {
    wordsCountFromNode = keysPredictCountWordAux (n->next);
} else if (n->down != 0) {
    wordsCountFromNode = keysPredictCountWordAux (n->down);
}

if (n->end !=  0){
    return wordsCountFromNode + 1;
} else {
    return wordsCountFromNode;
}
*/
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

struct node *addSortedNewNodeInLevel(struct node **list, char character) {
  struct node *var_nodo = *list;
  struct node *newNode = (struct node *)malloc(sizeof(struct node));
  newNode->character = character;
  newNode->down = 0;
  newNode->end = 0;
  newNode->next = 0;
  newNode->word = 0;
  while (var_nodo != 0 && var_nodo->next != 0) { // Más de dos nodos
    // Agregar en medio
    if (var_nodo->character <= character &&
        var_nodo->next->character >= character) {
      newNode->next = var_nodo->next;
      var_nodo->next = newNode;
      return *list;
    } else if (var_nodo->next->next == 0 &&
               var_nodo->next->character < character) {
      var_nodo->next->next = newNode;
      return *list;
    } else if (var_nodo->character > character) {
      newNode->next = var_nodo;
      //*list = newNode;
      return newNode;
    }
    var_nodo = var_nodo->next;
  }
  if (var_nodo == 0) {
    //*list = newNode;
    return newNode;
  } else if (var_nodo->character < character) {
    var_nodo->next = newNode;
    return var_nodo;
  } else if (var_nodo->character > character) {
    newNode->next = var_nodo;
    //*list = newNode;
    return newNode;
  }
}

/*
Dado un puntero a un arreglo de punteros a strings y el tamaño del arreglo. Se
encarga de borrar una a una las strings y ademas borrar el arreglo.
*/

void deleteArrayOfWords(char **words, int wordsCount) {
  for (int i = 0; i < wordsCount; i++) {
    free(*(words + i)); // Liberamos la memoria del puntero a la i-ésima palabra
  }
}
