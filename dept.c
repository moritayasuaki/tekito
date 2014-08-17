#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dept.h"

#define MAX_DEPTH 0x1000000

void print(tref_t r) {
    switch (tflg(r)) {
    case tflg_imm:
        printf("V%jd",imm(r));
        break;
    case tflg_app:
        printf("(");
        print(fun(r));
        printf(" ");
        print(arg(r));
        printf(")");
        break;
    case tflg_abst:
        printf("λ");
        print(type(r));
        printf(".");
        print(expr(r));
        break;
    case tflg_prod:
        printf("∀");
        print(type(r));
        printf(".");
        print(expr(r));
        break;
    }
}

tref_t shift(imm_t n, imm_t d, tref_t r) {
    switch (tflg(r)) {
    case tflg_imm:
        if(imm(r) > n) r = shift_imm(r, d);
        break;
    case tflg_app:
        r = shift(n,d,fun(r));
        r = shift(n,d,arg(r));
        break;
    case tflg_abst:
    case tflg_prod:
        r = shift(n,d,type(r));
        r = shift(n-1,d,expr(r));
        break;
    }
    return r;
}

tref_t copy_term(tref_t r) {
    tref_t nr;
    switch (tflg(r)) {
    case tflg_imm:
        nr = r;
        break;
    case tflg_app:
    case tflg_abst:
    case tflg_prod:
        nr = alloc_tref(tflg(r));
        car(nr) = copy_term(car(r));
        cdr(nr) = copy_term(cdr(r));
        break;
    }
    return nr;
}

tref_t subst_all(imm_t n, tref_t r, tref_t s) {
    switch (tflg(r)) {
    case tflg_imm:
        if (imm(r) == n)
        r = shift(0,n,copy_term(s));
        break;
    case tflg_app:
        car(r) = subst_all(n,car(r), s);
        cdr(r) = subst_all(n,cdr(r), s);
        break;
    case tflg_abst:
    case tflg_prod:
        car(r) = subst_all(n, car(r), s);
        cdr(r) = subst_all(n-1, cdr(r), s);
        break;
    }
    return r;
}

int main(int argc, char *argv[]) {
    tref_t top = {tflg_hole};
    vect_t *vect = alloc_vect(MAX_DEPTH);
    printf("%jx\n",top.raw);
    return 0;
}

