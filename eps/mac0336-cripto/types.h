#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

typedef uint8_t byte;
typedef uint32_t lbyte;
typedef unsigned char bool;
#define true 1
#define false 0

typedef uint64_t block64;

typedef struct Block128bits {
    block64 esquerda;
    block64 direita;
} block128;


#endif /* TYPES_H_ */
