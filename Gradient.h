#pragma once
#ifndef GRADIENT_H
#define GRADIENT_H
#include "Method.h"
class Gradient: public Method{
protected:
    bool accuracyCheck(Matrix R);
public:
    Gradient(Matrix a,
             Matrix b,
             long double E);
    std::vector<long double> getLogRow(Matrix X, Matrix r);
    Matrix getSolve();
};
void print(Matrix m);
#endif
