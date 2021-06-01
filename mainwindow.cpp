#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"
#include "solutionlog.h"
#include "iostream"
#include "Matrix.h"
#include "QMessageBox"
#include "vector"
#include "Jacoby.h"
#include "Gradient.h"
#include "GaussSeidel.h"
#include "qmath.h"
#include "printgraph.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->chooseMethod->addItem("Метод простої ітерації");
    ui->chooseMethod->addItem("Метод Гауса — Зейделя");
    ui->chooseMethod->addItem("Метод найшвидшого спуску");

    current_size = 2;
    setNewTablesOfSytem(current_size);
}
void MainWindow::setA(Matrix a ){
    bool f = false;
    if(!a.isMatrixEmpty())
        f=true;
    ui->tableA->clear();
    ui->tableA->setColumnCount(current_size);
    ui->tableA->setRowCount(current_size);
    QStringList List;
    for(int i =0;i<current_size;i++){
        List<<"A"+QString::number(i+1);
        for(int j =0;j<current_size;j++)
        {
            double el = 0;
            if(f)
                el = a.getElementByRowColumn(i,j);
            QTableWidgetItem *itm = new QTableWidgetItem(QString::number(el));
            ui->tableA->setItem(i,j,itm);
        }
    }
    ui->tableA->setHorizontalHeaderLabels(List);
    ui->tableA->setVerticalHeaderLabels(List);
}
void MainWindow::setB(Matrix b){
    bool f = false;
    if(!b.isMatrixEmpty())
        f=true;
    ui->tableB->clear();
    ui->tableB->setColumnCount(1);
    ui->tableB->setRowCount(current_size);
    QStringList List;
    for(int i =0;i<current_size;i++)
    {
        List<<"B"+QString::number(i+1);
        double el = 0;
        if(f)
            el = b.getElementByRowColumn(i,0);
        QTableWidgetItem *itm = new QTableWidgetItem(QString::number(el));
        ui->tableB->setItem(i,0,itm);
    }
    ui->tableB->setHorizontalHeaderLabels(QStringList() <<"B");
    ui->tableB->setVerticalHeaderLabels(List);
}
void MainWindow::setX(Matrix x){
    bool f = false;
    if(!x.isMatrixEmpty())
        f=true;
    ui->tableX->clear();
    ui->tableX->setColumnCount(1);
    ui->tableX->setRowCount(current_size);
    QStringList List;
    for(int i =0;i<current_size;i++)
    {
        List<<"X"+QString::number(i+1);
        double el = 0;
        if(f)
            el = x.getElementByRowColumn(i,0);
        QTableWidgetItem *itm = new QTableWidgetItem(QString::number(el));
        ui->tableX->setItem(i,0,itm);
    }
    ui->tableX->setHorizontalHeaderLabels(QStringList() <<"X");
    ui->tableX->setVerticalHeaderLabels(List);
}
void MainWindow::setNewTablesOfSytem(int n){
    current_size = n;
    setA(Matrix());
    setB(Matrix());
    setX(Matrix());
    ui->line_accuracy->setText("0.05");

}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_size_of_system_valueChanged(int n)
{
    setNewTablesOfSytem(n);
}







void MainWindow::on_btnClearField_clicked()
{
     setNewTablesOfSytem(current_size);
}

bool MainWindow::checkUncorrectInputB(){
    std::vector<std::vector <long double>> matrix;
    for(int i =0;i<current_size;i++){
        std::string row = "";
        for(int j =0;j<1;j++){
           std::string element =(ui->tableB->item(i,j)->data(0).toString().toLocal8Bit().constData());
           if(!checkUncorrectInputElement(element))
               return false;
           row+=element;
           row+=" ";
        }
        std::vector<long double> test= Matrix().readRow(row);
        matrix.push_back(test);
    };
    B.changeMainMatrix(matrix);
    return true;
}
bool MainWindow::checkUncorrectInputElement(std::string element){
//    string accuracy = ui->line_accuracy->text().toLocal8Bit().constData();
    if(element.size()==0){
        QMessageBox::critical(this,"Некоректне введення","Присутній пустий елемент!\nПеревірте чи всі елементи заповнені");
        return false;
    }
    if((element.find_last_of(" ")!=std::string::npos)){
        QMessageBox::critical(this,"Некоректне введення","Введений пробіл!\nВведеня пробілу заборонено");
        return false;
    }
    if (element.find_first_not_of("-.1234567890") != std::string::npos)
    {

       QMessageBox::critical(this,"Некоректне введення","Введені зайві символи!\nСписок дозволених символів: \"-.1234567890\"");
        return false;
    }
    if((element.find_last_of(".")==std::string::npos&&(element.size()>6))||(element.find_last_of(".")>7&&element.find_last_of(".")!=std::string::npos))

    {
        QMessageBox::critical(this,"Некоректне введення","Ціла частина завелика!\nМаксимальний розмір цілої частини 6 цифр");
        return false;
    }
    if((element.find_last_of(".")!=std::string::npos&&(element.size()-element.find_last_of("."))>9&&element.find_last_of(".")!=std::string::npos)){
        QMessageBox::critical(this,"Некоректне введення","Дробна частина завелика!\nМаксимальний розмір дробної частини 8 цифр");
        return false;
    }
    if(Matrix().readRow(element).size()==0){
            QMessageBox::critical(this,"Некоректне введення","Некоректно розташування коми або мінуса!\nПеревірте чи усі мінуси та коми розташовані коректно");
            return false;
    }
    return true;

}
bool MainWindow::checkUncorrectInputA(){
   std:: vector<std::vector <long double>> matrix;
    for(int i =0;i<current_size;i++){
        std::string row = "";
        for(int j =0;j<current_size;j++){
           std::string element =(ui->tableA->item(i,j)->data(0).toString().toLocal8Bit().constData());
           if(!checkUncorrectInputElement(element))
               return false;
           row+=element;
           row+=" ";
        }
        std::vector<long double> test= Matrix().readRow(row);
        matrix.push_back(test);
    };
    Matrix matrixPropertiesTest(matrix);
    if(!matrixPropertiesTest.isStrictlyDiagonallyDominant()){
        if(ui->chooseMethod->currentText()=="Метод Гауса — Зейделя"&&(!matrixPropertiesTest.isSylvesterCriterion()||!matrixPropertiesTest.isSymmetric())){
             QMessageBox::critical(this,"Введена розбіжна система","Матриця НЕ є додатньовизначеною або симетрична!");
             return false;
        }
        else if(ui->chooseMethod->currentText()=="Метод Гауса — Зейделя"&& matrixPropertiesTest.isSylvesterCriterion()&&matrixPropertiesTest.isSymmetric())
        {
            A.changeMainMatrix(matrix);
            return true;
        }
         QMessageBox::critical(this,"Введена розбіжна система","Строгий діагональний перевіс матриці відсутній!");
         return false;
    }
    A.changeMainMatrix(matrix);
    return true;
};
void MainWindow::setSolution(){
    ui->tableX->clear();
    ui->tableX->setColumnCount(1);
    QStringList List;
    for(int i =0;i<current_size;i++)
    {
        List<<"X"+QString::number(i+1);
        double el = X.getElementByRowColumn(i,0);
        QTableWidgetItem *itm = new QTableWidgetItem(QString::number(el));
        ui->tableX->setItem(i,0,itm);
    }
    ui->tableX->setVerticalHeaderLabels(List);
    ui->tableX->setHorizontalHeaderLabels(QStringList() <<"X");
}

void MainWindow::on_btnGetSolution_clicked()
{
    std::string accuracyStr = ui->line_accuracy->text().toLocal8Bit().constData();
    if(checkUncorrectInputA()&&checkUncorrectInputB()&&checkUncorrectInputElement(accuracyStr)){
        long double accuracy= Matrix().readRow(accuracyStr)[0];
        if(ui->chooseMethod->currentText()=="Метод простої ітерації"){
           Jacoby *calc = new Jacoby(A,B,accuracy);
           X = calc->getSolve();
           setSolution();
           LOG= calc->getLog();
           delete calc;
        }
        else if(ui->chooseMethod->currentText()=="Метод Гауса — Зейделя"){
            Gauss_Seidel *calc = new Gauss_Seidel(A,B,accuracy);
            X = calc->getSolve();
            setSolution();
            LOG= calc->getLog();
            delete calc;
        }
        else if(ui->chooseMethod->currentText()=="Метод найшвидшого спуску"){
            Gradient *calc = new Gradient(A,B,accuracy);
            X = calc->getSolve();
            setSolution();
            LOG= calc->getLog();
            delete calc;
        }
        if(current_size==2){
        printGraph window;
        window.setModal(true);
        window.setGraph(A,B,X);
        window.exec();
        }
    ui->btnGetLog->setEnabled(true);
    }
}


void MainWindow::on_btnGetRandom_clicked()
{
    setA(Matrix().getRandomQuadMatrix(current_size));
    setB(Matrix().getRandomVectorMatrix(current_size));
    setX(Matrix());
}


void MainWindow::on_btnGetLog_clicked()
{
    SolutionLog window_log;
    window_log.setModal(true);
    window_log.setTableLog(LOG);
    window_log.exec();
}

