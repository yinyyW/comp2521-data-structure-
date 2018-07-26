#include <stdio.h>
#include <string.h>

int main() {
    char mid = (('Z' - 'A')/2) + 'A';
    printf("%c\n", mid);
    printf("%d\n", (mid > 'C' ? 1 : 0));
    return 0;
}
