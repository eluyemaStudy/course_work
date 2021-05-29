#include "vector"
#include "GaussSeidel.h"

Gauss_Seidel::Gauss_Seidel(Matrix a, Matrix b, long double E) : Method(a, b, E) {};

Matrix Gauss_Seidel::getSolve() {
    clearLog();
    vector<vector<long double>> Log;
    Matrix L_star_inverse = A.getLowerTriangleMatrix().getAdditionMatrix(A.getDiagonalMatrix()).getInverseMatrix();
    Matrix U = A.getUpperTriangleMatrix();
    Matrix X = getX0();
    Log.push_back(getLogRow(X, X));
    Matrix Xbefore;
    do {
        Xbefore = X;
        X = L_star_inverse.getMultiplyMatrix(B.getSubtractMatrix(U.getMultiplyMatrix(X)));
        Log.push_back(getLogRow(Xbefore, X));
    } while (!accuracyСheck(Xbefore, X));
    log.changeMainMatrix(Log);
    return X;
}
