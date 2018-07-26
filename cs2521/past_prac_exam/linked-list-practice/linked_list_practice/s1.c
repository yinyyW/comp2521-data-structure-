
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
void removeDup(List L);

// main function
int main(int argc, char* argv[]) {
  int num;
  int i;
  int readIn;
  List L = newList();
  readIn = scanf("%d",&num);
  while(readIn > 0) {
    addNode(L,makeNode(num));
    readIn = scanf("%d",&num);
  }
  showList(L);
  printf("\n");
  removeDup(L);
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
  if (L->head != NULL)
    printf("(H:%d|T:%d) ",L->head->value,L->tail->value);
  else
    printf("(H:NULL|T:NULL) ");

  while(curr != NULL){
    printf("[%d]->",curr->value);
    curr = curr->next;
  }
  printf("NULL");
}

// =============================
// TODO: Complete this function
// =============================
void removeDup(List L) {
    Node curr = L->head->next;
    Node prev = L->head;
    while (curr->next != NULL) {
        Node p = L->head;
        while (p != curr) {
            if (p->value == curr->value) {
                Node temp = curr;
                prev->next = curr->next;
                temp->next = NULL;
                curr = prev;
                free(temp);
                break;
            }
            p = p->next;
        }
        prev = curr;
        curr = prev->next;
    }
    Node p2 = L->head;
    while (p2 != curr) {
        if (p2->value == curr->value) {
            Node temp = curr;
            L->tail = prev;
            L->tail->next = NULL;
            free(temp);
            break;
        }
        p2 = p2->next;
    }
}
