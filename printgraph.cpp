#include "printgraph.h"
#include "ui_printgraph.h"

printGraph::printGraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::printGraph)
{
    chrt =new QChart();
    ui->setupUi(this);
}

printGraph::~printGraph()
{
    delete chrt;
    delete ui;
}

void printGraph::setGraph(Matrix A,Matrix B, Matrix X){
    double intersectionX = X.getElementByRowColumn(0,0);
    double intersectionY = X.getElementByRowColumn(1,0);
    double x1=A.getElementByRowColumn(0,0);
    double y1=A.getElementByRowColumn(0,1);
    double x2=A.getElementByRowColumn(1,0);
    double y2=A.getElementByRowColumn(1,1);
    double b1=B.getElementByRowColumn(0,0);
    double b2=B.getElementByRowColumn(1,0);
    ui->vchrt->setChart(chrt);
    chrt->setTitle("Графічне рішення");
    QLineSeries* series1 = new QLineSeries();
    QLineSeries* series2 = new QLineSeries();
    series1->setName(QString::number(x1)+"X + "+QString::number(y1)+" = "+QString::number(b1));
    series2->setName(QString::number(x2)+"X + "+QString::number(y2)+" = "+QString::number(b2));
    double min = intersectionX;
    double max = intersectionX;
    for(long double i = intersectionX-abs(intersectionX);i<intersectionX + abs(intersectionX);i+=0.01){
        double point1=(b1-i*x1)/y1;
        double point2=(b2-i*x2)/y2;
        if(y1==0)
            point1 = x1;
        if(x2==0)
            point2 = y2;
        if(point1<min)
            min=point1;
        if(point2<min)
            min=point2;
        if(point1>max)
            max=point1;
        if(point2>max)
            max=point2;
        series1->append(i,point1);
        series2->append(i,point2);
    }
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(intersectionX-abs(intersectionX),intersectionX+abs(intersectionX));
    axisX->setTickCount(11);
    axisX->setLabelFormat("%.3f");

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(-0.01+min,max+0.01);
    axisY->setTickCount(11);
    axisY->setLabelFormat("%.3f");
    chrt->addSeries(series1);
    chrt->addSeries(series2);
    chrt->setAxisX(axisX,series1);
    chrt->setAxisY(axisY,series1);
    chrt->setAxisX(axisX,series2);
    chrt->setAxisY(axisY,series2);
}
