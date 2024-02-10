#include "workWithFile.h"
#include <iostream>

char** readFromFile(FILE* file, AppContext* context)
{
    int maxLength = 0;
    getNumberOfStrings(file, context);
    getMaxLengthOfString(&maxLength, file);
    char line[maxLength + 1];
    char **arrayOfStrings = memoryAllocationArray (context->lines);
    if (arrayOfStrings == NULL)
        return NULL;
    int i = 0;
    while (fgets (line, maxLength + 1, file))
    {
        size_t a = strlen(line);
        size_t b;
        if (i == int(context->lines - 1))
            b = 1;
        else
            b = 0;
        arrayOfStrings[i] = memoryAllocationString (a + b);
        if (arrayOfStrings[i] == NULL)
        {
            clean2DArray (arrayOfStrings, i);
            break;
        }
        snprintf(arrayOfStrings[i], a + b, "%s", line);
        i++;
    }
    context->lines = i;
    return arrayOfStrings;
}

void getNumberOfStrings (FILE *file, AppContext* context)
{
    int lineCount = 0;
    int c;
    do
    {
        c = fgetc(file);
        if (c == '\n')
            lineCount++;
    }
    while (c != EOF);
    context->lines = lineCount + 1;
    rewind(file);
}

void getMaxLengthOfString (int *length, FILE* file)
{
    int currentLength = 0, maxLength = 0;
    int c;
    while ((c = fgetc (file)) != EOF)
    {
        currentLength++;
        if (c == '\n')
        {
            if (currentLength > maxLength)
                maxLength = currentLength;
            currentLength = 0;
        }
    }
    if (currentLength > maxLength)
        maxLength = currentLength;
    *length = maxLength;
    rewind(file);
}

