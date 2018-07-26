/* iteratorG.c
   Generic Iterator implementation, using doubly linked list

   Written by: ....
   Date: ....

    You need to submit ONLY this file.... 

*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "iteratorG.h"

typedef struct Node {
    void *value;
    struct Node *next;
    struct Node *prev;
  // implement struct here .. 
} Node;

typedef struct IteratorGRep {
    Node *first;
    Node *last;
    Node *cursorPrev;
    Node *cursorNext;
    ElmCompareFp    cmpElm;
    ElmNewFp        newElm;
    ElmFreeFp       freeElm;
  // implement struct here .. 

} IteratorGRep;


/*
  Your  functions below .... 
 */
static Node *newNode(void *val, ElmNewFp newfp){
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    new->value = newfp(val);
    new->next = NULL;
    new->prev = NULL;
    return new;
}



IteratorG newIterator(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp){
	// implement function here and change return value 
	IteratorG   new;
	new = malloc(sizeof(struct IteratorGRep));
	if (new == NULL) {
	    fprintf(stderr, "Error!!  Cannot allocate memory for new Iterator\n");
	}

	new->first = NULL;
	new->last = NULL;
	new->cmpElm = cmpFp;
	new->newElm = newFp;
	new->freeElm = freeFp;

    new->cursorPrev = NULL;
    new->cursorNext = NULL;

	return new;
}

int  add(IteratorG it, void *vp){
	// implement function here and change return value
	assert(it != NULL);
	
	Node *new = newNode(vp, it->newElm);
	if (new == NULL) {
	    return 0;
	}

    if (it->first == NULL) {
	    new->prev = NULL;
	    new->next = NULL;
	    it->cursorNext = new;
	    it->cursorPrev = NULL;
	    it->first = new;
	    it->last = new;
    } else if (it->cursorPrev == NULL) {
        new->next = it->first;
        new->prev = NULL;
        it->first->prev = new;
        it->cursorNext = new;
        it->first = new;
    } else if (it->cursorNext == NULL) {
	    new->prev = it->cursorPrev;
	    new->next = NULL;
	    it->cursorPrev->next = new;
	    it->cursorNext = new;
	    it->last = new;
    } else {
        Node *temp = it->cursorNext;
        new->prev = it->cursorPrev;
        new->next = temp;
        it->cursorPrev->next = new;
        temp->prev = new;
        it->cursorNext = new;
    }
    return 1;
}
int  hasNext(IteratorG it){
	// implement function here and change return value
    if (it->cursorPrev != it->last) {
	    return 1;
    } else {
	    return 0;
    }
}
int  hasPrevious(IteratorG it){
	// implement function here and change return value
    if (it->cursorNext != it->first) {
	    return 1;
    } else {
	    return 0;
    }
}
void *next(IteratorG it){
	// implement function here 
    assert(it != NULL);
    //return pointer to next elem
    if (!hasNext(it)){
        return NULL;
    }
    void *p = it->cursorNext->value;

    //move cursor
    Node *temp = it->cursorNext;
    it->cursorNext = it->cursorNext->next;
    it->cursorPrev = temp;
	return p;
}
void *previous(IteratorG it){
    assert(it != NULL);
	// implement function here 
	if (!hasPrevious(it)){
	    return NULL;
	}
    void *p = it->cursorPrev->value;
    //move cursor
    Node *temp = it->cursorPrev;
    it->cursorNext = temp;
    it->cursorPrev = temp->prev;

	return p;
}
int  del(IteratorG it){
    assert(it != NULL);
	// implement function here and change return value
    if (it->cursorPrev == NULL) {
	    return 0;
    }

    if (it->cursorPrev == it->first){
	    Node *temp = it->cursorPrev;
	    it->first = it->cursorNext;
	    it->first->prev = NULL;
	    it->cursorPrev = NULL;
	    it->freeElm(temp->value);
	    free(temp);
    } else if (it->cursorPrev == it->last) {
        Node *temp = it->cursorPrev;
        it->last = temp->prev;
        it->last->next = NULL;
        it->cursorPrev = it->last;
        it->freeElm(temp->value);
        free(temp);
    } else {
        Node *temp = it->cursorPrev;
        it->cursorNext->prev = temp->prev;
        temp->prev->next = temp->next;
        it->cursorPrev = temp->prev;
        it->freeElm(temp->value);
        free(temp);
    }
    return 1;
}
int  set(IteratorG it, void *vp){
	// implement function here and change return value
    assert(it != NULL);
    if (it->cursorPrev == NULL) {
	    return 0;
    }
    it->freeElm(it->cursorPrev->value);
    it->cursorPrev->value = it->newElm(vp);
    return 1;
}
IteratorG advance(IteratorG it, int n){
	// implement function here and change return value
	IteratorG newIt = newIterator(it->cmpElm, it->newElm, it->freeElm);
	if (n == 0) {
	    return NULL;
	}
	int i;
	Node *curr = it->cursorNext;
    if (n > 0) {
        for(i = 0; i < n; i++){
            if (curr == NULL) {
                return NULL;
            }
            Node *new = newNode(curr->value, it->newElm);
            if (newIt->first == NULL) {
                new->prev = NULL;
	            new->next = NULL;
	            newIt->cursorNext = new;
	            newIt->cursorPrev = NULL;
	            newIt->first = new;
	            newIt->last = new;
            } else {
                newIt->last->next = new;
                new->prev = newIt->last;
                newIt->last = new;
            }
            it->cursorPrev = it->cursorNext;
            it->cursorNext = it->cursorNext->next;
            curr = curr->next;
        }
    }
    
    if (n < 0) {
        n = (-1)*n;
        Node *curr2 = it->cursorPrev;
        for(i = 0; i < n; i++){
            if (curr2 == NULL) {
                return NULL;
            }
            Node *new = newNode(curr2->value, it->newElm);
            if (newIt->first == NULL) {
                new->prev = NULL;
	            new->next = NULL;
	            newIt->cursorNext = new;
	            newIt->cursorPrev = NULL;
	            newIt->first = new;
	            newIt->last = new;
            } else {
                newIt->last->next = new;
                new->prev = newIt->last;
                newIt->last = new;
            }
            it->cursorNext = it->cursorPrev;
            it->cursorPrev = it->cursorPrev->prev;
            curr2 = curr2->prev;
        }
    }       
	
	return newIt;
}
void reverse(IteratorG it){
     Node *before = it->cursorPrev;
     Node *after = it->cursorNext;
     Node *curr = it->first;
     while (curr != NULL) {
        Node *temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
     }
     Node *head = it->first;
     it->first = it->last;
     it->last = head;

     it->cursorNext = before;
     it->cursorPrev = after;

	 return;
}
IteratorG find(IteratorG it, int (*fp) (void *vp) ){
	// implement function here and change return value 
	if (it->cursorNext == NULL) {
	    return NULL;
	}
	IteratorG newIt = newIterator(it->cmpElm, it->newElm, it->freeElm);
	Node *curr = it->cursorNext;

	while (curr != NULL) {
	    if(fp(curr->value)) {
	        Node *new = newNode(curr->value, it->newElm);
            if (newIt->first == NULL) {
                new->prev = NULL;
	            new->next = NULL;
	            newIt->cursorNext = new;
	            newIt->cursorPrev = NULL;
	            newIt->first = new;
	            newIt->last = new;
            } else {
                newIt->last->next = new;
                new->prev = newIt->last;
                newIt->last = new;
            }
        }
        curr = curr->next;
    }
	return newIt;
}
int distanceFromStart(IteratorG it){
	// implement function here and change return value 
	int cnt = 1;
	if (it->cursorPrev == NULL) {
	    return 0;
	}
	Node *curr = it->first;
	while (curr != it->cursorPrev) {
	    curr = curr->next;
	    cnt++;
	}
	return cnt;
}
int distanceToEnd(IteratorG it){
	// implement function here and change return value 
	int cnt = 1;
	if (it->cursorNext == NULL) {
	    return 0;
	}
	Node *curr = it->cursorNext;
	while (curr->next != NULL) {
	    curr = curr->next;
	    cnt++;
	}
	return cnt;
}
void reset(IteratorG it){
	// implement function here
	it->cursorNext = it->first;
	it->cursorPrev = NULL;
    
	return;
}
void freeIt(IteratorG it){
    if (it->first == NULL) {
        return;
    }
    Node *curr = it->first;
    while (curr->next != NULL) {
        Node *temp = curr;
        curr = curr->next;
        it->first = curr;
        it->freeElm(temp->value);
        free(temp);
    }
    it->freeElm(it->last->value);
    free(it->last);
    free(it);
	return;
}



// --------------------------------------





