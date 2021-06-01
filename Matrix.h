#ifndef KURSACH_MATRIX_H
#define KURSACH_MATRIX_H
#include <vector>
#include "fstream"
#include "iomanip"
#include "math.h"
#include <algorithm>
class Matrix{
private:
    std::vector<std::vector<long double>> mainMatrix;
    bool quadrMatrix = false;
    bool isMatrixValid(std::vector<std::vector<long double>> matrix);
    bool isMatrixQuadr(std::vector<std::vector<long double>> matrix);
    std::vector<std::vector<long double>> transpositionMatrix();
    void multiplyRowDigit(std::vector<long double> &row,long double k);
    long double getMultiplyRowRow(std::vector<long double> row1,std::vector<long double> row2);
    void subtractRowRow(std::vector<long double> &row1,std::vector<long double> &row2);
public:
    Matrix();
    Matrix(std::vector<std::vector<long double>> matrix);
    bool isMatrixEmpty();
    std::vector<long double> readRow(std::string line);
    void changeElementByRowColumn(int r, int c, long double value);
    std::vector<std::vector<long double>> getMatrix()const;
    Matrix getIdentityMatrix(int size);
    long double determ();
    Matrix readBandAfromFile(std::string path);//Поверне B та збереже A
    std::vector<long double> getRow(int j)const;
    Matrix multiplyMatrixDigit(long double k);
    Matrix getMultiplyMatrix(Matrix matr);
    Matrix getAdditionMatrix(Matrix matr);
    Matrix getSubtractMatrix(Matrix matr);
    Matrix getMultiplyMatrixDigit(long double d);
    long double getScalarProduct(Matrix matr);
    bool isSylvesterCriterion();
    bool isSymmetric();
    Matrix getAngleMatrix(int i);
    long double getElementByRowColumn(int i,int j);
    bool readMatrix(std::string path);
    bool isStrictlyDiagonallyDominant();
    void addRow(std::vector<long double> row);
    void addColumn(std::vector<long double> column);
    void changeMainMatrix(std::vector<std::vector<long double>> changes);
    Matrix getTranspMatrix();
    Matrix getInverseMatrix();
    long double getMinor(int i,int j);
    Matrix getLowerTriangleMatrix()const;
    Matrix getUpperTriangleMatrix()const;
    Matrix getDiagonalMatrix()const;
    Matrix getRandomVectorMatrix(int size);
    Matrix getRandomQuadMatrix(int size);
    int getColumnNum()const;
    int getRowNum()const;
};


#endif //KURSACH_MATRIX_H
