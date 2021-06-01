#ifndef PRINTGRAPH_H
#define PRINTGRAPH_H

#include <QDialog>

#include "QtCharts"
#include "Matrix.h"
namespace Ui {
class printGraph;
}

class printGraph : public QDialog
{
    Q_OBJECT

public:
    explicit printGraph(QWidget *parent = nullptr);
    ~printGraph();
    void setGraph(Matrix A,Matrix B, Matrix X);
private:
    Ui::printGraph *ui;
    QChart *chrt;
};

#endif // PRINTGRAPH_H
