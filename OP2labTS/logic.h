#ifndef LOGIC_H
#define LOGIC_H

#include <string.h>
#include "error.h"
#include "memory.h"
#include "workWithFile.h"

#define HEADERS "year,region,npg,birth_rate,death_rate,gdw,urbanization"

void loadingData(AppContext* context);
void loadingDataByRegion(AppContext* context);
void freeContext(AppContext* context);
void calculatingMetrics(AppContext* context);


char** strSplit(char* crudeData, size_t* box, const char sign);
char*** createAndFillData(char** crudeData, size_t lines, size_t* box);
char*** deleteInvalid(char*** data, AppContext* context);
void sortArray (double* array, AppContext* context);
void getMediana (double* array, AppContext* context);

#endif // LOGIC_H
