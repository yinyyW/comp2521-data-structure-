#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"

int isHeap(BTree t);

int isHeap(BTree t) {
    if (t == NULL) {
        return 1;
    }
    if (t->data < t->left->data) {
        return 0;
    } else if (t->data < t->right->data) {
        return 0;
    } else if (isHeap(t->left) == 0 || isHeap(t->right) == 0) {
        return 0;
    }
    return 1;
}
        
