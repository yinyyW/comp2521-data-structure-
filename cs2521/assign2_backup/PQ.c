#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "PQ.h"

typedef struct PQNode *Node;

struct PQNode {
	ItemPQ item;
	Node next;
} PQNode;

typedef struct PQRep {
	Node head;
	///Node tail;
} PQRep;

static void reorder(PQ q, ItemPQ it);

PQ newPQ() {
	PQ new = malloc(sizeof(struct PQRep));
	assert(new != NULL);
	new->head = NULL;
	//new->tail = NULL;
	return new;
}

void  addPQ(PQ q, ItemPQ it) {
	assert(q != NULL);
	//if key exist already
	Node currNode = q->head;
	Node toUpdate = NULL;
	while (currNode != NULL) {
		if ((currNode->item).key == it.key) {
			toUpdate = currNode;
			break;
		}
		currNode = currNode->next;
	}
	if (toUpdate != NULL) {
		toUpdate->item = it;
		return;
	}

	//make a new node
	Node new = malloc(sizeof(struct PQNode));
	assert(new != NULL);
	new->item = it;
	new->next = NULL;
	//insert node to queue
	//case1: no ele in queue
	if (q->head == NULL) {
		q->head = new;
		//q->tail = new;
		return;
	}
	//insert node in head
	if ((q->head->item).value >= it.value) {
		new->next = q->head;
		q->head = new;
		return;
	}
	//case3: insert in middle
	Node curr = q->head;
	while (curr->next != NULL && (curr->next->item).value < it.value) {
		curr = curr->next;
	}
	new->next = curr->next;
	curr->next = new;
	return;
}

ItemPQ  dequeuePQ(PQ q) {
	assert(q != NULL);
    assert(q->head != NULL);
	ItemPQ it = q->head->item;
	Node toDelete = q->head;
	q->head = q->head->next;
	free(toDelete);
	return it;
}

void  updatePQ(PQ q, ItemPQ it) {
	assert(q != NULL);
	if (q->head == NULL) return;
	Node curr = q->head;
	Node toUpdate = NULL;
	while (curr != NULL) {
		if ((curr->item).key == it.key) {
			toUpdate = curr;
			break;
		}
		curr = curr->next;
	}
	if (toUpdate == NULL) {
		return;
	}
	toUpdate->item = it;
	//if only one node in queue
	if (q->head->next == NULL) return;
	if ((q->head == toUpdate) && ((it.value) < (q->head->next->item).value)) return;
	//reorder
	reorder(q, it);
	return;
}

int PQEmpty(PQ q) {
	assert(q != NULL);
	if (q->head == NULL) {
		return 1;
	} else {
		return 0;
	}
}

void  showPQ(PQ q) {
	printf("Priority List: ");
	Node curr = q->head;
	while (curr != NULL) {
		printf("  %d value is %02d\n", (curr->item).key, (curr->item).value);
		curr = curr->next;
	}
	printf(" End\n");
}

void  freePQ(PQ q) {
	Node curr;
	Node next;
	assert(q != NULL);
	curr = q->head;
	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(q);
}

static void reorder(PQ q, ItemPQ it) {
	Node curr = q->head;
	Node toUpdate = NULL;
	Node prev = NULL;
	if ((curr->item).key == it.key) {
	    toUpdate = curr;
	    q->head = q->head->next;
	} else {
	    while (curr->next != NULL && (curr->next->item).key != it.key) {
		    curr = curr->next;
	    }
	    prev = curr;
	    toUpdate = curr->next;
	    //connect prev node to update's next
	    prev->next = toUpdate->next;
	}
	
	//add updated node to appropriate pos
	if (it.value <= (q->head->item).value) {
		toUpdate->next = q->head;
		q->head = toUpdate;
		return;
	}
	curr = q->head;
	while (curr->next != NULL && (curr->next->item).value < it.value) {
		curr = curr->next;
	}
	toUpdate->next = curr->next;
	curr->next = toUpdate;
	return;
}
