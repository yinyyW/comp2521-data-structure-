/*
 * Question 3
 * ===============================================
 * Write a function that inserts a new node with
 * value v at position i in a linked List, where
 * potision i is defined to be the location before
 * the ith node.
 *
 * calling insertAtI(L,100,1) with
 * L = [1]->[2]->[3]->NULL
 * modified L to be
 * L = [1]->[100]->[2]->[3]->NULL
 *
 * as the 1st node is [2] ([1] is the 0th)
 * ================================================
 * > You can assume you will never get a empty list.
 * > You can assume i is always valid (not out of bounds)
 */

#include <stdlib.h>
#include <stdio.h>

// Node
typedef struct _node {
  int value;
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
Node makeNode(int num);
void addNode(List L, Node n);
void showList(List L);
void insertAtI(List L, int b, int i);

// main function
int main(int argc, char* argv[]) {
  int i;
  int v;
  int num;
  int readIn;
  List L = newList();
  readIn = scanf("%d %d",&v,&i);
  readIn = scanf("%d",&num);
  while(readIn > 0) {
    addNode(L,makeNode(num));
    readIn = scanf("%d",&num);
  }
  insertAtI(L,v,i);
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
  free(n);
}

List newList(){
  List L = malloc(sizeof(list));
  L->head = NULL;
  L->tail = NULL;
  return L;
}

Node makeNode(int num){
  Node new = malloc(sizeof(node));
  new->value = num;
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
  // print out the head and tail
  if (L->head != NULL)
    printf("(H:%d|T:%d) ",L->head->value,L->tail->value);
  else
    printf("(H:NULL|T:NULL) ");
  // print out the rest of the list
  while(curr != NULL){
    printf("[%d]->",curr->value);
    curr = curr->next;
  }
  printf("NULL");
}

// =============================
// TODO: Complete this function
// =============================
void insertAtI(List L, int v, int i) {
    Node new = makeNode(v);
    if (i == 0) {
	Node temp = L->head;
	L->head = new;
	new->next = temp;
	return;
    }
//1->2->3
//1->4->2->3 i = 1
    int index;
    Node prev = NULL;
    Node curr = L->head;
    for (index = 0; index < i; index++) {
	prev = curr;
	curr = curr->next;
    }
    prev->next = new;
    new->next = curr;
}
