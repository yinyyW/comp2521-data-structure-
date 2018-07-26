#include <stdlib.h>
#include <stdio.h>

void *positiveIntNew(void const *vp){
  int v = * (int *) vp ;   
  // OR use local method like int v = getInt(vp);
  
  int *ip = malloc(sizeof(int));
  *ip = v;
  return ip;
}


int main() {
    void *value;
    void *new;
    int a[5] = {0,1,2,3,4};
    value = positiveIntNew(value);
    new = value;
    return 0;
}
