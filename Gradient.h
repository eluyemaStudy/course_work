#pragma once
#ifndef GRADIENT_H
#define GRADIENT_H
#include "Method.h"
class Gradient: public Method{
protected:
    bool accuracyСheck(Matrix R);
public:
    Gradient(Matrix a,
             Matrix b,
             long double E);
    vector<long double> getLogRow(Matrix X, Matrix r);
    Matrix getSolve();
};
#endif
