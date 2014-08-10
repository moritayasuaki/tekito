#ifndef _ARCH_H_
#define _ARCH_H_

#include <stdint.h>

typedef uintptr_t  raw_t;
typedef intptr_t   imm_t;

#define tag_mask (~-sizeof(raw_t))

#endif /* _ARCH_H_ */
