#ifndef ALLOCATION_H
#define ALLOCATION_H

#include <stdlib.h>

//MDTMP Not tested yet.
// size/type safety by casting to ptr type of the type sizeof parameter
#define MALLOC(type, size) \
((type*)malloc(sizeof(type)*size));

#define MALLOC_ONE(type) \
((type*)malloc(sizeof(type)));

#endif // ALLOCATION_H

