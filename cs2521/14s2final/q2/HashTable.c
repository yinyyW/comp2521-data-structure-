// HashTable.c ... implementation of HashTable library

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "List.h"
#include "HashTable.h"

typedef struct _hash_table_rep {
   int nslots;    // size of chains[] array
   int nvals;     // # keys stored in table
   List *chains;  // array of hash chains
} HashTableRep;

// hash function (int -> [0..nslots-1])
static int hash(int val, int nslots)
{
   return (val%nslots);
}

// create an empty hash table
HashTable newHashTable(int N)
{
   HashTable new;
   int i;
   new = malloc(sizeof(HashTableRep));
   assert(new != NULL);
   new->nslots = N;
   new->nvals = 0;
   new->chains = malloc(N*sizeof(List));
   assert(new->chains != NULL);
   for (i = 0; i < N; i++)
      new->chains[i] = newList();
   return new;
}

// free memory for a hash table
void dropHashTable(HashTable ht)
{
   assert(ht != NULL);
   int i;
   for (i = 0; i < ht->nslots; i++)
      dropList(ht->chains[i]);
   free(ht->chains);
   free(ht);
}

// display a hash table on stdout
void showHashTable(HashTable ht)
{
   assert(ht != NULL);
   int i;
   for (i = 0; i < ht->nslots; i++) {
      printf("[%2d] ",i);
      showList(ht->chains[i]);
   }
}

// add a new value into a HashTable
void insertHashTable(HashTable ht, int val)
{
   void expand(HashTable);
   assert(ht != NULL);
   if (ht->nvals > 2*ht->nslots) expand(ht);
   int h = hash(val,ht->nslots);
   appendList(ht->chains[h],val);
   ht->nvals++;
}

// double the number of slots/chains in a hash table
/*
void expand(HashTable ht)
{
    assert(ht != NULL);
    int num = ht->nslots * 2;
    List *new = malloc(sizeof(List) *num);
    int i;
    for (i=0; i < num; i++) {
	    new[i] = newList();
    }
    int j;
    for (j=0; j < ht->nslots; j++) {
	    int n;
	    int *vals = valuesFromList(ht->chains[j],&n);
	    int k;
	    for (k = 0; k < n; k++) {
	        int pos = hash(vals[k], num);
	        appendList(new[pos],vals[k]);
	    }
	    free(vals);
    }
    for (i = 0; i< ht->nslots;i++) {
	    dropList(ht->chains[i]);
    }
    free(ht->chains);

    ht->nslots = num;
    ht->chains = new;
}*/
































void expand(HashTable ht) {
    //init new ele of ht
    int numSlots = (ht->nslots) * 2;
    List *new = malloc(sizeof(List) * numSlots);
    int m;
    for (m = 0; m < numSlots; m++) {
        new[m] = newList();
    }
    //rehash
    int i;
    for (i=0; i < ht->nslots; i++) {
        int *size = malloc(sizeof(int));
        //int size;
        int *values = valuesFromList(ht->chains[i], size);
        int j;
        for (j=0; j < *size; j++) {
            int index = hash(values[j], numSlots);
            appendList(new[index], values[j]);
        }
        free(size);
        free(values);
    }
    //free memory
    int k;
    for (k = 0; k < ht->nslots;k++) {
        dropList(ht->chains[k]);
    }
    free(ht->chains);
    ht->chains = new;
    ht->nslots = numSlots;
}
