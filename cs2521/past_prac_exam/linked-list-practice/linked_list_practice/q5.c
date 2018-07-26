/*
 * Question 5
 * ===============================================
 * I have this awesome double linked list which
 * i used to store my favourite carley ray jepson
 * songs but i've accidently put in the data in the
 * wrong order! can you reverse the list for me?
 * ===============================================
 * finish the reverseList function that via pointer
 * manipulations (i.e without creating a new list)
 * reverses the list
 *
 * NULL<-1<->2<->3<->4<->5->NULL
 * becomes
 * NULL<-5<->4<->3<->2<->1->NULL
 *
 * ===============================================
 * > you won't be given an empty List
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFF_SIZE 256

// Node
typedef struct _node {
  char* song;
  struct _node *next;
  struct _node *prev;
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
void reverseList(List L);

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
  reverseList(L);
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
  free(n->song);
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
  new->song = strdup(word);
  new->next = NULL;
  new->prev = NULL;
  return new;
}

void addNode(List L, Node n){
  if (L->head == NULL) {
    L->head = n;
    L->tail = n;
  }else{
    L->tail->next = n;
    n->prev = L->tail;
    L->tail = n;
  }
}

void showList(List L){
  printf("FORWARD: ");
  Node curr = L->head;
  while(curr != NULL){
    printf("[%s]->",curr->song);
    curr = curr->next;
  }
  printf("NULL\nBACKWARD: ");
  curr = L->tail;
  while(curr != NULL){
    printf("[%s]->",curr->song);
    curr = curr->prev;
  }
  printf("NULL");
}

// =============================
// TODO: Complete this function
// =============================
void reverseList(List L) {

}
