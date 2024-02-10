#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include "appContext.h"
char **memoryAllocationArray (size_t length);
char *memoryAllocationString (size_t length);
char ***memoryAllocation3DArray (size_t length);
double *memoryAllocationArrayOdDouble (size_t length);
void freeString (char **str);
void clean2DArray(char **arr, size_t size);
void clean3DArray(char ***arr, size_t sizeX, size_t sizeY);

void copyTable(AppContext *context);
#endif // MEMORY_H
