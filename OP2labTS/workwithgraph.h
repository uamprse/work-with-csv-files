#ifndef WORKWITHGRAPH_H
#define WORKWITHGRAPH_H

#define SIZE_OF_GRAPH 600

#include "appContext.h"
#include <QPainter>
#include <QPixmap>

void coordinatePlane(QPainter &paint);
void drawText(QPainter &paint, AppContext* context);
void drawGraph (QPainter &paint, AppContext* context);

#endif // WORKWITHGRAPH_H
