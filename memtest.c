#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
int main(void) {
    int *p;
    int i;
    for (i = 0;i < 100; i++) {
        p = malloc(sizeof(int));
        printf("%llx\n",(uint64_t)p);
    }
    return 0;
}
