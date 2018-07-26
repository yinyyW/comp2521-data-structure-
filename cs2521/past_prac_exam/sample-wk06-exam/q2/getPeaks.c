// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/

DLList getPeaks(DLList L){

	DLList peaksL = newDLList();

	if (L->nitems < 2) {
	    return peaksL;
	}

    L->curr = L->first->next;
    while (L->curr != L->last){
        if (L->curr->prev->value < L->curr->value && L->curr->next->value < L->curr->value) {
            if (peaksL->nitems == 0) {
                DLListNodeP new = newDLListNode(L->curr->value);
                peaksL->first = new;
                peaksL->last = new;
                peaksL->curr = new;
                peaksL->nitems = 1;
             } else {
                DLListNodeP new = newDLListNode(L->curr->value);
                DLListNodeP temp = peaksL->last;
                peaksL->last = new;
                peaksL->last->prev = temp;
                temp->next = peaksL->last;
                peaksL->nitems++;
                peaksL->curr = peaksL->last;
            }
        }
        L->curr = L->curr->next;
    }
	return peaksL;

}



