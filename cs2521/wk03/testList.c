// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

int main(int argc, char *argv[])
{
	DLList myList;
	myList = getDLList(stdin);
	putDLList(stdout,myList);
	assert(validDLList(myList));
	printf("\n");
    //delete list containing only one node
    printf("test:delete list containing only one line\n");
    putDLList(stdout, myList);
    DLListDelete(myList);
    printf("\n");
    assert(validDLList(myList));

    //test:insert node to the empty list
    printf("test:insert one line to the empty list\n");
    putDLList(stdout, myList);
    printf("############\n");
    DLListBefore(myList, "First Line");
    putDLList(stdout, myList);
    printf("\n");
    assert(validDLList(myList));
    
    
    //test:insert line after current 
    printf("test:insert line after current\n");
    putDLList(stdout, myList);
    printf("############\n");
    DLListAfter(myList, "Second Line");
    putDLList(stdout, myList);
    printf("\n");
    assert(validDLList(myList));
    
    //test:insert line after current
    printf("test:insert another line after current\n");
    putDLList(stdout, myList);
    printf("############\n");
    DLListAfter(myList, "A new line");
    putDLList(stdout, myList);
    printf("\n");
    assert(validDLList(myList));

    //test:delete current line
    printf("test:delete current line\n");
    putDLList(stdout, myList);
    printf("############\n");
    DLListDelete(myList);
    putDLList(stdout, myList);
    printf("\n");
    assert(validDLList(myList));

    //test:delete line
    printf("test:delete line\n");
    putDLList(stdout, myList);
    printf("############\n");
    DLListDelete(myList);
    putDLList(stdout, myList);
    printf("\n");
    assert(validDLList(myList));

    //test:insert node before
    printf("test:insert a line before current\n");
    putDLList(stdout, myList);
    printf("############\n");
    DLListBefore(myList, "Put a new line");
    putDLList(stdout, myList);
    printf("\n");
    assert(validDLList(myList));
    
    
    printf("test:delete all lines\n");
    putDLList(stdout, myList);
    printf("############\n");
    DLListDelete(myList);
    putDLList(stdout, myList);
    printf("\n");
    assert(validDLList(myList));
    
    putDLList(stdout, myList);
    printf("############\n");
    DLListDelete(myList);
    putDLList(stdout, myList);
    printf("\n");
    assert(validDLList(myList));
	
	return 0;
}
