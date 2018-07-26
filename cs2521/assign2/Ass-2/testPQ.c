#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    PQ q = newPQ();  
    ItemPQ n1;
    n1.key = 0;
    n1.value = 10;
    ItemPQ n2;
    n2.key = 1;
    n2.value = 15;
    ItemPQ n3;
    n3.key = 2;
    n3.value = 12;

    addPQ(q, n1);
    addPQ(q, n2);
    addPQ(q, n3);


    showPQ(q);
    n1.value = 20;
    updatePQ(q, n1);
    showPQ(q);

    ItemPQ n4 = dequeuePQ(q);
    printf("%d has been removed\n", n4.key);
    showPQ(q);

    
    addPQ(q, n4);
    n4.value = 40;
    updatePQ(q, n4);
    showPQ(q);

    freePQ(q);
    return EXIT_SUCCESS;
}
