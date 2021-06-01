#pragma once
#ifndef METHOD_H
#define METHOD_H
#include "vector"
#include "Matrix.h"
class Method{
protected:
    Matrix log;
    Matrix A;
    Matrix B;
    long double e;
    bool accuracyCheck(Matrix before, Matrix after);
    Matrix getX0();
    void clearLog();
    void setLog(std::vector<std::vector <long double>> Log);
    std::vector<long double> getLogRow(Matrix before,Matrix after);
public:
    Method( Matrix a, Matrix b,long double E);
    Matrix getA() const;
    Matrix getB() const;
    Matrix getLog() const;
    void setSystem(Matrix a,Matrix b,long double E );
};
#endif
