#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <stdlib.h>
#include <string>
#define MAX_LEN_ERROR 100

struct Error
{
    char errorString[MAX_LEN_ERROR] = "\0";
    bool isCorrect = true;
};

struct Metrics
{
    double max = 0;
    double min = 0;
    double mediana = 0;
};

struct AppContext
{
    char* fileName = NULL;
    char* regionName = NULL;
    char** tableHeaders = NULL;
    char*** table = NULL;
    char*** cpyTable = NULL;
    int countOfInvalidStrings = 0;
    size_t columns = 0;
    size_t lines = 0;
    size_t columnscpy = 0;
    size_t linescpy = 0;
    size_t numberOfColumn = 0;
    Error error;
    Metrics metrics;
};

#endif // APPCONTEXT_H
