/*
 * Question 4
 * ===============================================
 * oh dear, someone trolled me and filled my
 * linked list of my favourite words up with the
 * word "MEMES", could you go through the list and
 * delete any node that contains the word "MEMES"?
 * ================================================
 * Fill in the function "removeMemes()" which takes
 * in a list and delete all nodes containing the
 * word MEMES
 *
 * [hello]->[world]->[MEMES]->NULL
 * becomes
 * [hello]->[world]->NULL
 * ================================================
 * > you may be given an empty List
 * > You won't be given a NULL list struct
 * > only delete strings that are exactly "MEMES"
 * > you are allowed to use string.h functions
 *   like strcmp
 * > yes i think this is hilarious, i'm a simple man
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFF_SIZE 256

// Node
typedef struct _node {
  char* word;
  struct _node *next;
} node;
typedef node *Node;

// List
typedef struct _list {
  Node head;
  Node tail;
} list;
typedef list *List;

// prototypes
List newList();
void freeNode(Node n);
Node makeNode(char* word);
void addNode(List L, Node n);
void showList(List L);
void removeMemes(List L);

// main function
int main(int argc, char* argv[]) {
  char str[BUFF_SIZE];
  int readIn;
  List L = newList();
  readIn = scanf("%s",str);
  while(readIn > 0) {
    addNode(L,makeNode(str));
    readIn = scanf("%s",str);
  }
  removeMemes(L);
  showList(L);
  // i'm a good boy and free my memory
  Node curr = L->head;
  while(curr != NULL){
    Node next = curr->next;
    freeNode(curr);
    curr = next;
  }
  free(L);
  return EXIT_SUCCESS;
}

void freeNode(Node n) {
  free(n->word);
  free(n);
}

List newList(){
  List L = malloc(sizeof(list));
  L->head = NULL;
  L->tail = NULL;
  return L;
}

Node makeNode(char* word){
  Node new = malloc(sizeof(node));
  new->word = strdup(word);
  new->next = NULL;
  return new;
}

void addNode(List L, Node n){
  if (L->head == NULL) {
    L->head = n;
    L->tail = n;
  }else{
    L->tail->next = n;
    L->tail = n;
  }
}

void showList(List L){
  Node curr = L->head;
  if (L->head != NULL)
    printf("(H:%s|T:%s) ",L->head->word,L->tail->word);
  else
    printf("(H:%s|T:%s) ","NULL","NULL");

  while(curr != NULL){
    printf("[%s]->",curr->word);
    curr = curr->next;
  }
  printf("NULL");
}

// =============================
// TODO: Complete this function
// =============================
void removeMemes(List L) {

}
