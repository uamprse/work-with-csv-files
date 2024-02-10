#include "error.h"

void openFileError (AppContext* context)
{
    context->error.isCorrect = false;
    strcpy (context->error.errorString, ERROR_OPEN_FILE);
}

void memoryAllocationError (AppContext* context)
{
    context->error.isCorrect = false;
    strcpy (context->error.errorString, MEMORY_ALLOCATION_ERROR);
}

