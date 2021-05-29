#pragma once
#ifndef JACOBY_H
#define JACOBY_H
#include "Method.h"
class Jacoby: public Method{
public:
    Jacoby(Matrix a,
           Matrix b,
           long double E);
    Matrix getSolve();
};
#endif