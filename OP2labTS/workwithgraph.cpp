#include "workwithgraph.h"

void coordinatePlane(QPainter &paint)
{
    paint.fillRect(0, 0, SIZE_OF_GRAPH, SIZE_OF_GRAPH, QBrush(QColor(Qt::GlobalColor::white)));
    paint.translate(10, SIZE_OF_GRAPH/2);
    paint.setPen(QColor(Qt::GlobalColor::black));
    paint.drawLine(20, 270, 20, -270);
    paint.drawLine(-3, 0, 541, 0);
    paint.drawLine(15, -265, 20, -270);
    paint.drawLine(20, -270, 25, -265);
    paint.drawLine(540, 0, 535, -5);
    paint.drawLine(540, 0, 535, 5);
    paint.drawText(10, 12, "0");
}

void drawText(QPainter &paint, AppContext* context)
{
    QString  result1 (context->tableHeaders[0]);
    paint.drawText(505, 12, result1);
    QString  result2 (context->tableHeaders[context->numberOfColumn]);
    paint.save();
    paint.translate(10, SIZE_OF_GRAPH/2);
    paint.rotate(-90);
    paint.drawText(477, -10, 100, 60, Qt::AlignHCenter, result2);
    paint.restore();
}

void drawGraph (QPainter &paint, AppContext* context)
{
    double c;
    if (abs(context->metrics.max) >= abs(context->metrics.min))
        c = -190 / context->metrics.max;
    else
        c = 190 / context->metrics.min;
    QString  metricsMax = QString::number(context->metrics.max);
    paint.drawText(-8, c*context->metrics.max, metricsMax);
    paint.drawLine(15, c*context->metrics.max, 25, c*context->metrics.max);
    QString  metricsMin = QString::number(context->metrics.min);
    paint.drawText(-8, c*context->metrics.min, metricsMin);
    paint.drawLine(15, c*context->metrics.min, 25, c*context->metrics.min);
    QString  metricsMed = QString::number(context->metrics.mediana);
    paint.drawText(-8, c*context->metrics.mediana, metricsMed);
    paint.drawLine(15, c*context->metrics.mediana, 25, c*context->metrics.mediana);

    double a = 450 / (context->linescpy - 1);
    for (size_t i = 0; i < context->linescpy - 1; i++)
        paint.drawLine(40 + a*i, c*atof(context->cpyTable[i][context->numberOfColumn]) , 40 + a*(i + 1), c*atof(context->cpyTable[i + 1][context->numberOfColumn]));
    paint.save();
    paint.rotate(-90);
    for (size_t i = 0; i < context->linescpy; i++)
    {
        QString  curYear (context->cpyTable[i][0]);
        paint.drawText(-35, 45 + a*i, curYear);
        paint.drawLine(-5, 40 + a*i, 5, 40 + a*i);
    }
    paint.restore();
    paint.setPen(Qt::DotLine);
    paint.drawLine(30, c*context->metrics.max, 540, c*context->metrics.max);
    paint.drawLine(30, c*context->metrics.min, 540, c*context->metrics.min);
    paint.drawLine(30, c*context->metrics.mediana, 540, c*context->metrics.mediana);
}
