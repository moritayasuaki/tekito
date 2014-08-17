#ifndef _DEPT_H_
#define _DEPT_H_

#include <stdlib.h>
#include "arch.h"
#include "bit.h"

#define imm_bit     1u
#define imm_msk     pw2m(imm_bit)
#define type_bit    3u
#define type_msk    pw2m(type_bit)

typedef enum {
    rflg_imm    = 0x0,  /* 0b000 */
    rflg_ref    = 0x1,
} rflg_t;

typedef enum {
    tflg_imm     = 0x0,  /* 0x000 */
    tflg_app     = 0x1,  /* 0b001 */
    tflg_abst    = 0x3,  /* 0b011 */
    tflg_prod    = 0x5,  /* 0b101 */
    tflg_hole    = 0x7,  /* 0b111 */
} tflg_t;

typedef union {
    raw_t raw;
    tflg_t tflg : 3;
} tref_t;

typedef struct {
    tref_t fun;
    tref_t arg;
} app_t;

typedef struct {
    tref_t type;
    tref_t expr;
} abst_t;

typedef struct {
    tref_t type;
    tref_t expr;
} prod_t;

typedef struct {
    tref_t car;
    tref_t cdr;
} cons_t;

typedef union {
    app_t app;
    abst_t abst;
    prod_t prod;
    cons_t cons;
} term_t;


static inline raw_t imm2raw(imm_t imm) {
    return (raw_t)(imm>>imm_bit);
}

static inline imm_t raw2imm(raw_t raw) {
    return (imm_t)(raw<<imm_bit);
}

static inline tflg_t tflg(tref_t ref) { return (-(ref.raw & imm_msk)) & (ref.raw & type_msk); }
static inline imm_t imm(tref_t ref) { return raw2imm(ref.raw); }
static inline term_t *term(tref_t ref) { return (term_t *)(ref.raw & (~type_msk)); }

static inline tref_t shift_imm(tref_t ref, imm_t d) {
    ref.raw += raw2imm((raw_t)d);
    return ref;
}

static inline tref_t fun(tref_t ref) { return term(ref)->app.fun; }

static inline tref_t arg(tref_t ref) { return term(ref)->app.arg; }

static inline tref_t type(tref_t ref) { return term(ref)->abst.type; }

static inline tref_t expr(tref_t ref) { return term(ref)->abst.expr; }

static inline tref_t alloc_tref(tflg_t tflg){
    tref_t ref;
    ref.raw = (raw_t)malloc(sizeof(term_t));
    ref.raw |= tflg;
    return ref;
}

#define car(ref) term(ref)->cons.car
#define cdr(ref) term(ref)->cons.cdr

typedef struct {
    bv_t app;
    bv_t abst;
    bv_t prod;
} vect_t;

typedef struct {
    tref_t *scope;
} scope_t;

typedef struct {
    u_t depth;
    scope_t scope;
    vect_t vect;
} ctx_t;

static inline vect_t *alloc_vect(u_t n) {
    vect_t *vect = (vect_t*)malloc(sizeof(vect_t));
    vect->app = alloc_bv(n);
    vect->abst = alloc_bv(n);
    vect->prod = alloc_bv(n);
    return vect;
}

#endif /*_DEPT_H_*/
