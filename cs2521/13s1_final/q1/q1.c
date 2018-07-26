// q1.c ... Question 1 in COMP1927 13s1 Final Exam
// Find maximum value in an array via recursive divide-and-conquer

#include <stdlib.h>
#include <stdio.h>

#define MAXARRAY 1000


int main(int argc, char **argv)
{
	int array[MAXARRAY];  // array storage
	int n;  // count of elements in array
	int val;  // next value read from stdin
	int ArrayMax(int *, int);

	// read array contents from stdin
	n = 0;
	while (fscanf(stdin,"%d",&val) == 1)
		array[n++] = val;

	// display maximum value
	if (n > 0)
		printf("Max = %d\n", ArrayMax(array,n));
	else
		printf("Array is empty\n");

	return 0;
}

// find maximum value in a[0..n-1]
int ArrayMax(int a[], int n)
{
	int max(int *, int, int);

	return max(a, 0, n-1);
}

// recursive function to find maximum in a[lo..hi]
/*
int max(int a[], int lo, int hi)
{
    if (lo >= hi) {
	return a[lo];
    }
    int mid = (lo+hi)/2;
    int low = max(a, lo, mid);
    int high = max(a, mid+1, hi);
    if (low<high) {
	return high;
    } else {
	return low;
    }
}*/































int max(int a[], int lo, int hi) {
    //base case
    if (lo == hi) {
        return a[lo];
    }
    //int mid = (lo + hi)/2;
    if (max(a, lo, hi-1) >= a[hi]) {
        return max(a, lo, hi-1);
    } else {
        return a[hi];
    }
}
