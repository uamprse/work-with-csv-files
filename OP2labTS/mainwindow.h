#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appContext.h"
#include "entryPoint.h"
#include "workwithgraph.h"

#define SIZE_OF_GRAPH 561

char* QStringToCharArray (QString str);
QStringList ConvertRowToQTFormat(char **row, size_t size);

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    AppContext context;
    void onSelectFileClicked();
    void onLoadDataClicked();
    void onCalculateMetricsClicked();
    void showTable();
    void loadNamesOfRegions();
    void updateLabel();
    void showGraph();
    void showNumberOfStrings();
    void clearUI();
};
#endif // MAINWINDOW_H
