#include <stdio.h>
#include <stdint.h>

#define vec(f,x) ((uint64_t[]){f(0,x),f(1,x),f(2,x),f(3,x),f(4,x),f(5,x)})
#define map(f,x) ((uint64_t[]){f(0,x[0]),f(1,x[1]),f(2,x[2]),f(3,x[3]),f(4,x[4]),f(5,x[5])})
#define unfold(f,x) ((uint64_t[]){\
        f(0,x),\
        f(1,f(0,x)),\
        f(2,f(1,f(0,x))),\
        f(3,f(2,f(1,f(0,x)))),\
        f(4,f(3,f(2,f(1,f(0,x))))),\
        f(5,f(4,f(3,f(2,f(1,f(0,x))))))})
#define id(n,x) (x)
#define succ(n,x) (-~(x))
#define pred(n,x) (~-(x))
#define pw2(n,x) ((x)<<(n))
#define pw2m(n,x) (pw2(n,x)-1)
#define ppw2(n,x) (pw2(pw2(n,1ull),x))
#define ppw2m(n,x) pred(n,ppw2(n,x))
#define ppw2p(n,x) succ(n,ppw2(n,x))
#define dppw2p(n,x) (-1ull/ppw2p(n,x))
#define fold(f,x,v) ((uint64_t[]){\
        f(0,v,x[0]),\
        f(1,f(0,v,x[0]),x[1]),\
        f(2,f(1,f(0,v,x[0]),x[1]),x[2]),\
        f(3,f(2,f(1,f(0,v,x[0]),x[1]),x[2]),x[3]),\
        f(4,f(3,f(2,f(1,f(0,v,x[0]),x[1]),x[2]),x[3]),x[4]),\
        f(5,f(4,f(3,f(2,f(1,f(0,v,x[0]),x[1]),x[2]),x[3]),x[4]),x[5])})
#define sr2(n,x) ((x)|((x)>>pw2(n,1ull)))
#define bwadd(n,x) (((x)&dppw2p(n,1ull))+(((x)>>pw2(n,1ull))&dppw2p(n,1ull)))
#define bwrev(n,x) (((((x)&dppw2p(n,1ull))<<pw2(n,1ull)))|(((x)>>pw2(n,1ull))&dppw2p(n,1ull)))
#define pop(x) (unfold(bwadd,x)[5])
#define rev(x) (unfold(bwrev,x)[5])
#define lg2(x) pop(unfold(sr2,pred(0,x))[5])

int main(void) {
    int i;
    printf("%016llx\n",pw2(5,0x1ull));
    printf("%016llx\n",pop(0x11100ull));
    printf("%016llx\n",rev(0x1ull));
    printf("%016llx\n",lg2(0x5ull));
    return 0;
}

