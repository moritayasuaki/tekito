#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>
int main(void) {
    int *p;
    int i;
    for (i = 0;i < 100; i++) {
        printf("%llx\n",INTMAX_MIN);
    }
    return 0;
}
