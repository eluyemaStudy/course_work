#include "Gradient.h"
#include "vector"
bool Gradient::accuracyСheck(Matrix R) {
    for (int i = 0; i < R.getRowNum(); i++) {
        if (abs(R.getElementByRowColumn(i, 0)) > e)
            return false;
    }
    return true;
}

Gradient::Gradient(Matrix a,
                   Matrix b,
                   long double E) : Method(a, b, E) {};

vector<long double> Gradient::getLogRow(Matrix X, Matrix R) {
    X = X.getTranspMatrix();
    R = R.getTranspMatrix();
    vector<long double> logRow;
    for (int i = 0; i < X.getColumnNum(); i++)
        logRow.push_back(X.getElementByRowColumn(0, i));
    for (int i = 0; i < R.getColumnNum(); i++)
        logRow.push_back(abs(R.getElementByRowColumn(0, i)));
    logRow.push_back(e);
    return logRow;
}
Matrix Gradient::getSolve() {
    clearLog();
    vector<vector<long double>> Log;
    Matrix X = getX0();
    Log.push_back(Method::getLogRow(X, X));
    Matrix r = A.getMultiplyMatrix(X).getSubtractMatrix(B);
    int count = 0;
    do {
        Matrix Xbefore = X;
        Matrix subScalarElement = A.getInverseMatrix().getMultiplyMatrix(r);
        Matrix scalarElement = A.getMultiplyMatrix(subScalarElement);
        long double u = r.getScalarProduct(scalarElement) / scalarElement.getScalarProduct(scalarElement);
        X = X.getSubtractMatrix(subScalarElement.getMultiplyMatrixDigit(u));
        r = A.getMultiplyMatrix(X).getSubtractMatrix(B);
        Log.push_back(getLogRow(X, r));
    } while (!accuracyСheck(r));
    log.changeMainMatrix(Log);
    return X;
}
