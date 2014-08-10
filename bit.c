#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "bit.h"

#define veb(n) veb ## n ## _t

typedef u_t veb(0);

typedef struct {
    u_t max;
    u_t min;
    veb(0) summary;
    veb(0) cluster[1ull<<((1ull<<0)*lg_bitsof(u_t))];
} veb(1);

typedef struct {
    u_t max;
    u_t min;
    veb(1) summary;
    veb(1) cluster[1ull<<((1ull<<1)*lg_bitsof(u_t))];
} veb(2);

typedef struct {
    u_t max;
    u_t min;
    veb(2) summary;
    veb(2) cluster[1ull<<((1ull<<2)*lg_bitsof(u_t))];
} veb(3);
typedef struct {
    u_t max;
    u_t min;
    veb(3) summary;
    veb(3) cluster[1ull<<((1ull<<3)*lg_bitsof(u_t))];
} veb(4);

/* u_t min_veb(u_t level, veb_t *veb) { return veb->min;} */
/* u_t max_veb(u_t level, veb_t *veb) { return veb->max;} */

/* u_t member_veb(u_t level, u_t val, veb_t *veb) {  */
    /* if(level == 1) return  */
    /* if ( veb->max < veb->min) { */
        /* return 0; */
    /* } else if (veb->max == veb->min) { */
        /* return member_veb(level-1, veb->cluster[0]); */
    /* } else if ( veb->max > veb->min) { */
    /* } */
/* } */

/* u_t insert_veb(u_t level, u_t val, veb_t *veb) { */
    /* if ( veb->max < veb->min ) { */
        /* veb->max = val; */
        /* veb->min = val; */
    /* } if ( veb->max == veb->min ) { */
        /* if (veb->max < val) { */
            /* veb->max = val; */
        /* } */
        /* if (veb->min > val) { */
            /* veb->min = val; */
            /* val = veb->min; */
        /* } */
    /* } */
/* } */
int main(void) {
    veb(3) *t;
    t = mmap(NULL, 1ull<<48, PROT_WRITE|PROT_READ, MAP_ANON|MAP_PRIVATE, -1, 0);
    printf("%lx\n",sizeof(veb(3)));
    printf("%jx\n",(uintmax_t)t);
}


