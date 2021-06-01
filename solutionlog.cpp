#include "solutionlog.h"
#include "ui_solutionlog.h"
#include "Matrix.h"
SolutionLog::SolutionLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SolutionLog)
{
    ui->setupUi(this);
}
void SolutionLog::setTableLog(Matrix Log){
    int row = Log.getRowNum();
    int column = Log.getColumnNum();

    ui->tableLog->clear();
    ui->tableLog->setColumnCount(column);
    ui->tableLog->setRowCount(row);
    QStringList ListElements;
    QStringList ListIteration;
    for(int i =0;i<row;i++){
        ListIteration<<"Iter. "+QString::number(i);
        for(int j =0;j<column;j++)
        {
            double el = Log.getElementByRowColumn(i,j);
            QTableWidgetItem *itm = new QTableWidgetItem(QString::number(el));
            ui->tableLog->setItem(i,j,itm);
        }

    }
    for(int i =0;i<column/2;i++)
        ListElements<<"X"+QString::number(i+1);
    for(int i =0;i<column/2;i++)
        ListElements<<"e"+QString::number(i+1);
    ListElements<<"e";
    ui->tableLog->setHorizontalHeaderLabels(ListElements);
    ui->tableLog->setVerticalHeaderLabels(ListIteration);
}
SolutionLog::~SolutionLog()
{
    delete ui;
}
