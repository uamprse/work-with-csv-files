#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardItemModel>
#include <iostream>
#include <QStringList>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonSelectFile, &QPushButton::clicked, this, &MainWindow::onSelectFileClicked);
    connect(ui->loadData, &QPushButton::clicked, this, &MainWindow::onLoadDataClicked);
    connect(ui->calculateMetrics, &QPushButton::clicked, this, &MainWindow::onCalculateMetricsClicked);

    ui->loadData->setDisabled(true);
    ui->chooseRegion->setEditable(false);
    ui->chooseRegion->setDisabled(true);
    ui->calculateMetrics->setDisabled(true);
}

MainWindow::~MainWindow()
{
    doOperation(FreeContext, &context);
    delete ui;
}

void MainWindow::onSelectFileClicked()
{
    clearUI();
    doOperation(FreeContext, &context);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"),"C://", tr("CSV files (*.csv)"));
    ui->fileName->setText(fileName);
    context.fileName = QStringToCharArray(fileName);
    doOperation(LoadData, &context);
    showNumberOfStrings();
    showTable();
    loadNamesOfRegions();
    updateLabel();
}

void MainWindow::onLoadDataClicked()
{
    QString regionName = ui->chooseRegion->currentText();
    context.regionName = QStringToCharArray(regionName);
    doOperation(LoadDataByRegion, &context);
    showTable();
//    ui->loadData->setDisabled(true);
    ui->calculateMetrics->setEnabled(true);
    updateLabel();
}

void MainWindow::onCalculateMetricsClicked()
{
    context.numberOfColumn = ui->chooseNumber->text().toInt() - 1;
    doOperation(CalculateMetrics, &context);
    ui->maxValue->setText(QString::number(context.metrics.max));
    ui->minValue->setText(QString::number(context.metrics.min));
    ui->mediana->setText(QString::number(context.metrics.mediana));
    updateLabel();
    showGraph();
}

void MainWindow::showNumberOfStrings()
{
    if (context.error.isCorrect == true)
    {
        ui->invalidStrings->setText(QString::number(context.countOfInvalidStrings));
        ui->validStrings->setText(QString::number(context.lines));
    }
}

char* QStringToCharArray (QString str)
{
    char* newStr = (char*)malloc(sizeof(char) * (str.size() + 1));
    if (newStr != NULL)
    {
        for(qsizetype i = 0; i < str.size(); i++)
            newStr[i] = str.at(i).unicode();
        newStr[str.size()] = 0;
    }
    return newStr;
}

void MainWindow::updateLabel()
{
    if (context.error.isCorrect == false)
    {
        ui->errorString->setText(context.error.errorString);
        ui->loadData->setDisabled(true);
        ui->chooseRegion->setDisabled(true);
        ui->calculateMetrics->setDisabled(true);
    }
}

void MainWindow::showGraph()
{
    QPixmap *pix = new QPixmap(SIZE_OF_GRAPH, SIZE_OF_GRAPH);
    QPainter paint(pix);
    coordinatePlane (paint);
    drawText(paint, &context);
    drawGraph(paint, &context);
    ui->graph->setPixmap(*pix);
    return;
}

void MainWindow::loadNamesOfRegions()
{
    ui->chooseRegion->setEnabled(true);
    if (context.table != NULL)
    {
        QStringList nstr;
        for (size_t i = 0; i < context.lines; i++)
            if (!nstr.contains(context.table[i][1]))
                nstr.append(context.table[i][1]);
        ui->chooseRegion->addItems(nstr);
    }
    ui->loadData->setEnabled(true);
}

void MainWindow::clearUI()
{
    ui->chooseRegion->setEnabled(false);
    ui->chooseRegion->clear();
    ui->graph->clear();
    ui->validStrings->clear();
    ui->invalidStrings->clear();
    ui->minValue->clear();
    ui->maxValue->clear();
    ui->fileName->clear();
    ui->mediana->clear();
    ui->table->clear();
    ui->table->setRowCount(0);
    ui->table->setColumnCount(0);
    ui->errorString->clear();
}

void MainWindow::showTable()
{
    if (context.table == NULL)
        return;
    ui->table->setColumnCount(context.columnscpy);
    QStringList QColumns = ConvertRowToQTFormat(context.tableHeaders, context.columnscpy);
    ui->table->setHorizontalHeaderLabels(QColumns);
    ui->table->setRowCount(context.lines);
    for (size_t i = 0; i < context.lines; i++)
    {
        QStringList currentRow = ConvertRowToQTFormat(context.cpyTable[i], context.columnscpy);
        for (int j = 0; j < currentRow.count(); j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            item->setData(Qt::EditRole, currentRow.at(j));
            item->setText(currentRow.at(j));
            ui->table->setItem(i, j, item);
        }
    }
}

QStringList ConvertRowToQTFormat(char** row, size_t size)
{
    QStringList nstr;
    for(size_t i = 0; i < size; i++)
    {
        nstr.append(row[i]);
    }
    return nstr;
}
