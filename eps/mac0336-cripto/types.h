#ifndef TYPES_H_
#define TYPES_H_

typedef unsigned char byte;
typedef unsigned long lbyte;
typedef unsigned char bool;
#define true 1
#define false 0

typedef struct Block64 {
    lbyte bytes[2];
} block64;

typedef struct Block128bits {
    block64 esquerda;
    block64 direita;
} block128;


#endif /* TYPES_H_ */
