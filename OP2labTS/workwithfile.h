#ifndef WORKWITHFILE_H
#define WORKWITHFILE_H

#include <fstream>
#include "appContext.h"
#include "memory.h"
#include <string.h>
#include "error.h"

void getNumberOfStrings (FILE *file, AppContext* context);
void getMaxLengthOfString (int *length, FILE* file);
char** readFromFile(FILE* file, AppContext* context);

#endif // WORKWITHFILE_H
