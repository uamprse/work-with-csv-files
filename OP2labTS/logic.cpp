#include "logic.h"
#include <iostream>


void loadingData(AppContext* context)
{
    FILE *file = fopen (context->fileName, "r");
    if (file == NULL)
    {
        openFileError(context);
        return;
    }
    char** arrayOfStrings = readFromFile(file, context);
    fclose(file);
    if (arrayOfStrings == NULL)
    {
        memoryAllocationError(context);
        return;
    }
    size_t linesInBeginning = context->lines;
    char** tableHeaders = strSplit(*arrayOfStrings, &context->columns, ',');
    context->lines = context->lines - 1;
    char ***data = createAndFillData(arrayOfStrings, context->lines, &context->columns);
    data = deleteInvalid(data, context);
    if ((tableHeaders == NULL) || (data == NULL))
    {
        memoryAllocationError(context);
        clean3DArray(data, context->lines, context->columns);
        clean2DArray (tableHeaders, context->lines);
    }
    else
    {
        context->tableHeaders = tableHeaders;
        context->table = data;
    }
    clean2DArray(arrayOfStrings, linesInBeginning);
    copyTable(context);
    return;
}

char** strSplit(char* array, size_t* columns, const char sign)
{
    char** result;
    size_t countOfColumns = 0;
    char* tmp = array;
    while(*tmp)
    {
        if(sign == *tmp)
            countOfColumns++;
        tmp++;
    }
    countOfColumns++;
    *columns = countOfColumns;
    result = memoryAllocationArray(countOfColumns);
    size_t indx = 0;
    char *token = array;
    for (char *ending = (char*) strchr(token, sign); ending; token = ending + 1, ending = (char*)strchr(token, sign), indx++)
    {
        *(result + indx) = memoryAllocationString(ending - token + 1);
        if (*(result + indx) != NULL)
            snprintf(*(result + indx), ending - token + 1, "%s", token);
        else
        {
            for (size_t a = 0; a < indx; a++)
                free(*(result + a));
            free (result);
            result = NULL;
            break;
        }
    }
    if (result == NULL)
        return result;
    *(result + indx++) = strdup(token);//strdup() – дублирование строк с выделением памяти под новую строку.
    return result;
}

char*** createAndFillData(char** crudeData, size_t lines, size_t* box)
{
    char ***data;
    data = memoryAllocation3DArray(lines);
    if (data == NULL)
        return NULL;
    for (size_t i = 0; i < lines; i++)
    {
        data[i] = strSplit(crudeData[(i + 1)], box, ',');
        if (data[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
                clean2DArray(data[j], lines);
            free(data);
            data = NULL;
            break;
        }
    }
    return data;
}

void freeContext (AppContext* context)
{
    if (context->tableHeaders != NULL)
    {
        clean2DArray(context->tableHeaders, context->columns);
        context->tableHeaders = 0;
    }
    if (context->table != NULL)
    {
        clean3DArray(context->table, context->lines, context->columns);
        context->table = NULL;
    }
    if (context->fileName != NULL)
    {
        free(context->fileName);
        context->fileName = NULL;
    }
    if (context->regionName != NULL)
    {
        free(context->regionName);
        context->regionName = NULL;
    }
    strcpy(context->error.errorString, "\0");
    context->error.isCorrect = true;
    context->countOfInvalidStrings = 0;
    context->columns = 0;
    context->lines = 0;
}

char*** deleteInvalid(char*** data, AppContext* context)
{
    for (size_t i = 0; i < context->lines; i++)
    {
        for (size_t j = 0; j < context->columns; j++)
            if (strcmp(data[i][j], "") == 0)
            {
                clean2DArray(data[i], context->columns);
                for (size_t k = i; k < context->lines - 1; k++)
                    data[k] = data[k + 1];
                context->lines = context->lines - 1;
                context->countOfInvalidStrings = context->countOfInvalidStrings + 1;
                i--;
            }
    }
    return data;
}

void loadingDataByRegion(AppContext* context)
{
    copyTable(context);
    for (int i = 0; i < context->linescpy; i++)
    {
        if (!(strcmp(context->cpyTable[i][1], context->regionName) == 0))
        {
            clean2DArray(context->cpyTable[i], context->columnscpy);
            for (int k = i; k < context->linescpy - 1; k++)
                context->cpyTable[k] = context->cpyTable[k + 1];
            context->linescpy = context->linescpy - 1;
            i--;
        }
    }
    return;
}

void calculatingMetrics(AppContext* context)
{
    double* array = memoryAllocationArrayOdDouble(context->linescpy);
    if (array == NULL)
    {
        memoryAllocationError(context);
        return;
    }
    for (size_t i = 0; i < context->linescpy; i++)
        array[i] = atof(context->cpyTable[i][context->numberOfColumn]);
    sortArray(array,context);
    context->metrics.min = array[0];
    context->metrics.max = array[context->linescpy - 1];
    getMediana(array, context);
    free(array);
    return;
}

void sortArray (double* array, AppContext* context)
{
    for (size_t i = 0; i < context->linescpy - 1; i++)
    {
        for (size_t j = 0; j < context->linescpy - 1 - i; j++)
            if (array[j] > array[j+1])
            {
                double t = array[j];
                array[j] = array[j+1];
                array[j+1] = t;
            }
    }
}

void getMediana (double* array, AppContext* context)
{
    if (context->lines % 2 == 0)
        context->metrics.mediana = (array[context->linescpy / 2] + array[context->linescpy / 2 - 1]) / 2;
    else
        context->metrics.mediana = array[context->linescpy / 2];
}
