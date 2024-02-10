#include "memory.h"
#include <string.h>
char *memoryAllocationString (size_t length)
{
    char *str = (char*) malloc (sizeof(char) * length);
    return str;
}

double *memoryAllocationArrayOdDouble (size_t length)
{
    double *arr = (double*) malloc (sizeof(double) * length);
    return arr;
}

char **memoryAllocationArray (size_t length)
{
    char **array = (char**) malloc (sizeof(char*) * length);
    return array;
}

char ***memoryAllocation3DArray (size_t length)
{
    char ***array = (char***) malloc (sizeof(char**) * length);
    return array;
}

void freeString (char **str)
{
    free (*str);
    *str = NULL;
}

void clean2DArray(char **arr, size_t size)
{
    if (arr == NULL)
        return;
    for (size_t i = 0; i < size; i++)
    {
        free(*(arr + i));
    }
    free(arr);
}

void clean3DArray(char ***arr, size_t sizeX, size_t sizeY)
{
    if (arr == NULL)
        return;
    for (size_t i = 0; i < sizeX; i++)
    {
        clean2DArray(*(arr + i), sizeY);
    }
    free(arr);
}

void copyTable(AppContext *context){
    context->cpyTable = memoryAllocation3DArray(context->lines);
    for (int i = 0; i < context->lines; i++){
        context->cpyTable[i] = memoryAllocationArray(context->lines);
        for (int j = 0; j < context->columns; j++){
            context->cpyTable[i][j] = strdup(context->table[i][j]);
    //        context->cpyTable[i][j] = memoryAllocationString(strlen(context->table[i][j]));
    //        strcpy(context->cpyTable[i][j], context->table[i][j]);
        }
    }
    context->columnscpy = context->columns;
    context->linescpy = context->lines;
//    size_t a = sizeof(context->cpyTable);
//    size_t b = sizeof(context->table);
    ;
}
