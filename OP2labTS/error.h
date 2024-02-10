#ifndef ERROR_H
#define ERROR_H

#include <string.h>
#include "appContext.h"

#define ERROR_OPEN_FILE "Can't open the file"
#define MEMORY_ALLOCATION_ERROR "MemoryAllocationError"


void openFileError (AppContext* context);
void memoryAllocationError (AppContext* context);


#endif // ERROR_H

