#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTableWidgetItem"
#include "vector"
#include "string"
#include "Matrix.h"
#include "QFileDialog"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setNewTablesOfSytem(int n);
    ~MainWindow();

private slots:
    void on_size_of_system_valueChanged(int arg1);


    void on_btnClearField_clicked();
    bool checkUncorrectInputA();
    bool checkUncorrectInputB();
    bool checkUncorrectInputElement(std::string element);
    void on_btnGetSolution_clicked();
    void setA(Matrix a);
    void setB(Matrix b);
    void setX(Matrix x);
    void setSolution();
    void on_btnGetRandom_clicked();

    void on_btnGetLog_clicked();

private:
    Matrix A;
    Matrix B;
    Matrix X;
    Matrix LOG;
    int current_size;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
