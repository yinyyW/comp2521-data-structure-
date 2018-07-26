/*
 * Question 6
 * ===============================================
 * Below is a linked list of patients at a
 * hospital and their priority in the queue to
 * see a doctor. Fill in the function getNextPatient()
 * which takes in a linked list of patients and
 * returns the name of the person with the highest
 * priority score.
 *
 * [joe 5]->[janice 10]->NULL
 * returns
 * janice
 * ================================================
 * > You can assume there is at least 1 patient
 * > You can assume there won't be a tie for
 *   highest priority i.e 2 people with priority
 *   10 which is the highest
 * > priority will always be a postive integer >=0
 * > Names won't repeat
 * > Don't modify the list
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFF_SIZE 256

// Patient
typedef struct _patient {
  char* name;
  int priority;
} patient;
typedef patient *Patient;

// Node
typedef struct _node {
  Patient p;
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
char* getNextPatient(List L);
void addPatient(List L, Patient p);
Patient makePatient(char* name, int pri);
List newList();
void freeNode(Node n);

// main function
int main(int argc, char* argv[]) {
  char str[BUFF_SIZE];
  int pri;
  int readIn;
  List L = newList();
  readIn = scanf("%s %d",str,&pri);
  while(readIn > 0) {
    Patient p = makePatient(str,pri);
    addPatient(L,p);
    readIn = scanf("%s %d",str,&pri);
  }
  printf("%s\n",getNextPatient(L));
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
  free(n->p->name);
  free(n->p);
  free(n);
}
List newList(){
  List L = malloc(sizeof(list));
  L->head = NULL;
  L->tail = NULL;
  return L;
}

Patient makePatient(char* name, int pri){
  Patient p = malloc(sizeof(patient));
  p->name = strdup(name);
  p->priority = pri;
  return p;
}

void addPatient(List L, Patient p){
  Node new = malloc(sizeof(node));
  new->next = NULL;
  new->p = p;
  if (L->head == NULL) {
    L->head = new;
    L->tail = new;
  }else{
    L->tail->next = new;
    L->tail = new;
  }
}

// =============================
// TODO: Complete this function
// =============================
char* getNextPatient(List L) {
  return "I DUNNO!";
}
