#ifndef __BIT_H__
#define __BIT_H__
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define bitsof(type) (sizeof(type)*CHAR_BIT)
#define dbs64 0x218a392cd3d5dbfull
#define dbs64map ((const uintmax_t[64]){0,1,2,7,3,13,8,19,4,25,14,28,9,34,20,40,5,17,26,38,15,46,29,48,10,31,35,54,21,50,41,57,63,6,12,18,24,27,33,39,16,37,45,47,30,53,49,56,62,11,23,32,36,44,52,55,61,22,43,51,60,42,59,58})
#define dbs64lg(powerof2) (dbs64map[(((powerof2)*dbs64)>>(64-6))&(~-64)])
#define bsum0(ofs,b) (((b)>>(ofs))&1)
#define bsum1(ofs,b) (bsum0(ofs,b) + bsum0(ofs+1,b))
#define bsum2(ofs,b) (bsum1(ofs,b) + bsum1(ofs+2,b))
#define bsum3(ofs,b) (bsum2(ofs,b) + bsum2(ofs+4,b))
#define bsum4(ofs,b) (bsum3(ofs,b) + bsum3(ofs+8,b))
#define bsum5(ofs,b) (bsum4(ofs,b) + bsum4(ofs+16,b))
#define bsum6(ofs,b) (bsum5(ofs,b) + bsum5(ofs+32,b))
#define lg_bitsof(type) (bsum6(0,~-bitsof(type)))
#define msb(type)     ((1ull)<<(bitsof(type)-1))

typedef uintmax_t u_t;
typedef u_t * bv_t;

static inline u_t cmsk(u_t c) {return ~-!c;}
static inline u_t shl(u_t n,u_t b) {return b<<n;}
static inline u_t shr(u_t n,u_t b) {return b>>n;}
static inline u_t shror(u_t n, u_t b){return b|shr(n,b);}
static inline u_t pw2(u_t n) {return shl(n,1ull);}
static inline u_t pw2m(u_t n) {return ~-pw2(n);}
static inline u_t ppw2(u_t n) {return pw2(pw2(n));}
static inline u_t ppw2m(u_t n) {return ~-ppw2(n);}
static inline u_t ppw2p(u_t n) {return -~ppw2(n);}
static inline u_t i2m(u_t n) {return -1ull/ppw2p(n);}
static inline u_t bwadd(u_t n,u_t b) {return (b&i2m(n))+(shr(pw2(n),b)&i2m(n));}
static inline u_t bwswp(u_t n,u_t b) {return shl(pw2(n),b&i2m(n))|(shr(pw2(n),b)&i2m(n));}
static inline u_t dz(u_t a, u_t b) {return cmsk(a>b)&(a-b);}
static inline u_t max(u_t a, u_t b) {return b+dz(a,b);}
static inline u_t min(u_t a, u_t b) {return a-dz(a,b);}
static inline u_t bmrg(u_t n, u_t a, u_t b) {return a<<n|(n?b>>(bitsof(u_t)-n):0);}

static inline u_t pop(u_t b) {
    u_t n;
    for(n=0;n<lg_bitsof(b);n++) b=bwadd(n,b);
    return b;
}

static inline u_t rev(u_t b) {
    u_t n;
    for(n=0;n<lg_bitsof(b);n++) b=bwswp(n,b);
    return b;
}

static inline u_t fill(u_t b) {
    u_t n;
    for(n=0;n<lg_bitsof(b);n++) b=shror(n,b);
    return b;
}

static inline u_t lg2(u_t b){
    return pop(fill(b-1));
}

static inline void bset_bv(u_t i, bv_t bv) {
    bv[shr(lg_bitsof(bv[0]),i)] |= pw2(i&pw2m(lg_bitsof(bv[0])));
}
static inline void bclr_bv(u_t i, bv_t bv) {
    bv[shr(lg_bitsof(bv[0]),i)] &= ~pw2(i&pw2m(lg_bitsof(bv[0])));
}
static inline void bmov_bv(u_t i, bv_t bv, u_t u) {
    u?bset_bv(i,bv):bclr_bv(i,bv);
}

static inline u_t btst_bv(u_t i, bv_t bv) {
    return !!(bv[shr(lg_bitsof(bv[0]),i)] & pw2(i&pw2m(lg_bitsof(bv[0]))));
}

static inline u_t rnk_u(u_t *s, u_t b) {
    u_t m = min(bitsof(b),*s);
    *s -= m;
    return pop(shl(bitsof(b)-m,b));
}

static inline u_t rnk_bv(u_t s, bv_t bv) {
    u_t r=0;
    while(s) r+=rnk_u(&s,*(bv++));
    return r;
}

static inline u_t sel_u(u_t *r, u_t b) {
    int n;
    u_t s=0,t[lg_bitsof(b)+1]={b},d;
    for(n=0;n<lg_bitsof(b);n++) t[n+1]=bwadd(n,t[n]);
    if(*r>t[lg_bitsof(b)]) return *r-=t[lg_bitsof(b)],s+=bitsof(b);
    for(n=lg_bitsof(b)-1;n>=0;n--) if(*r>(d=(t[n]>>s)&ppw2m(n))) *r-=d,s+=pw2(n);
    return *r-=1,s+=1;
}

static inline u_t sel_bv(u_t r, bv_t bv) {
    u_t s=0;
    while(r) s+=sel_u(&r,*(bv++));
    return s;
}

static inline void xchg(u_t *x,u_t *y) {*x^=*y;*y^=*x;*x^=*y;}

static inline u_t xorshift(u_t *r){*r^=*r>>12;*r^=*r<<25;*r^=*r>>27;return (*r)*2685821657736338717ull;}

static inline u_t atob(char *s){
    u_t ans=0;
    while(*s) {
        ans <<= 1;
        ans |= !(*s-'0');
        s++;
    }
    return ans;
}

static void dump_bv(bv_t bv, u_t n) {
    n = ((n+bitsof(bv[0])-1)>>lg_bitsof(bv[0]))-1;
    printf("%jx",bv[n]);
    while (n--)
        printf("%016jx",bv[n]);
    printf("\n");
}

static inline void print_bv(bv_t bv, u_t n){
    while(n--)
        putchar('0'+btst_bv(n,bv));
    putchar('\n');
}

static inline bv_t alloc_bv(u_t n) {
    return (bv_t)malloc(sizeof(u_t)*((n+bitsof(u_t)-1)>>lg_bitsof(u_t)));
}

static inline bv_t calloc_bv(u_t n) {
    return (bv_t)calloc(1,sizeof(u_t)*((n+bitsof(u_t)-1)>>lg_bitsof(u_t)));
}

#endif /* __BIT_H__ */
