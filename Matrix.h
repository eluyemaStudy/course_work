#ifndef KURSACH_MATRIX_H
#define KURSACH_MATRIX_H
#include <vector>
#include "fstream"
#include "iomanip"
#include "math.h"
#include <algorithm>
using namespace std;
class Matrix{
private:
    vector<vector<long double>> mainMatrix;
    bool quadrMatrix = false;
    vector<long double> readRow(string line);
    bool isMatrixValid(vector<vector<long double>> matrix);
    bool isMatrixQuadr(vector<vector<long double>> matrix);
    vector<vector<long double>> transpositionMatrix();
    void multiplyRowDigit(vector<long double> &row,long double k);
    long double getMultiplyRowRow(vector<long double> row1,vector<long double> row2);
    void subtractRowRow(vector<long double> &row1,vector<long double> &row2);
public:
    Matrix();
    Matrix(vector<vector<long double>> matrix);
    void changeElementByRowColumn(int r, int c, long double value);
    vector<vector<long double>> getMatrix()const;
    Matrix getIdentityMatrix(int size);
    long double determ();
    vector<long double> getRow(int j)const;
    Matrix multiplyMatrixDigit(long double k);
    Matrix getMultiplyMatrix(Matrix matr);
    Matrix getAdditionMatrix(Matrix matr);
    Matrix getSubtractMatrix(Matrix matr);
    Matrix getMultiplyMatrixDigit(long double d);
    long double getScalarProduct(Matrix matr);
    bool isSylvesterСriterion();
    bool isSymmetric();
    Matrix getAngleMatrix(int i);
    long double getElementByRowColumn(int i,int j);
    bool readMatrix(string path);
    bool isStrictlyDiagonallyDominant();
    void addRow(vector<long double> row);
    void addColumn(vector<long double> column);
    void changeMainMatrix(vector<vector<long double>> changes);
    Matrix getTranspMatrix();
    Matrix getInverseMatrix();
    long double getMinor(int i,int j);
    Matrix getLowerTriangleMatrix()const;
    Matrix getUpperTriangleMatrix()const;
    Matrix getDiagonalMatrix()const;
    int getColumnNum()const;
    int getRowNum()const;
};


#endif //KURSACH_MATRIX_H
