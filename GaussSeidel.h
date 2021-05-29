#pragma once
#ifndef GAUSSSEIDEL_H
#define GAUSSSEIDEL_H
#include "Method.h"
class Gauss_Seidel: public Method{
public:
    Gauss_Seidel(Matrix a,
                 Matrix b,
                 long double E);
    Matrix getSolve();
};
#endif
