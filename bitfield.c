#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

_Static_assert(sizeof(uintmax_t) != 64, "not support uintmax_t == 64");

typedef enum {
    pflg_imm,
    pflg_ptr
} pflg;

typedef struct {
    pflg isptr : 1;
    intmax_t var : 63;
} imm;

typedef struct {
    pflg pflg : 1;
    uintmax_t tag : 2;
    uintmax_t ptr : 61;
} ptr;

typedef union term{
    uintmax_t bit;
    imm imm;
    ptr ptr;
} term;

typedef struct cell{
    term car;
    term cdr;
} cell;

int main(void) {
    term a;
    a.bit = -4;
    printf("%lu\n",sizeof(cell));
    printf("%u\n",a.imm.isptr);
    printf("%jd\n",a.imm.var);
    printf("%jx\n",a.bit);
    return 0;
}
