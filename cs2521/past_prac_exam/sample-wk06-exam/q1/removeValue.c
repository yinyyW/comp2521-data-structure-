// removeValue.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "removeValue" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/



void removeValue(DLList L, int value){
    while (L->first->value == value && L->first->next != NULL) {
        DLListNode *temp = L->first;
        L->first = temp->next;
        L->first->prev = NULL;
        L->curr = L->first;
        L->nitems--;
        free(temp);
    }
   
    L->curr = L->first;
    while (L->curr->next != NULL) {
        if (L->curr->value == value) {
            DLListNode *temp = L->curr;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            L->curr = L->first;
            free(temp);
            L->nitems--;
        } else {
            L->curr = L->curr->next;
        }
    }

    if (L->last->value == value && L->nitems>1) {
        DLListNode *temp = L->last;
        L->last = temp->prev;
        L->last->next = NULL;
        L->curr = L->last;
        free(temp);
        L->nitems--;
    }
    if (L->last->value == value && L->first == L->last) {
        DLListNode *temp = L->first;
        L->first = NULL;
        L->last = NULL;
        L->curr = NULL;
        L->nitems = 0;
        free(temp);
    }
    return;
}



