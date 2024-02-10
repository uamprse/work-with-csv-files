#include "entrypoint.h"

void doOperation(Operation operation, AppContext* context)
{
    switch(operation)
    {
    case LoadData:
        loadingData(context);
        break;
    case LoadDataByRegion:
        loadingDataByRegion(context);
        break;
    case CalculateMetrics:
        calculatingMetrics(context);
        break;
    case FreeContext:
        freeContext(context);
        break;
    }
}
