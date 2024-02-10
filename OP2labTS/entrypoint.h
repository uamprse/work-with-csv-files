#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <stdlib.h>
#include "appContext.h"
#include "logic.h"


enum Operation
{
    LoadData,
    CalculateMetrics,
    FreeContext,
    LoadDataByRegion
};

// Объявление точки входа
void doOperation (Operation operation, AppContext* context);

#endif // ENTRYPOINT_H
