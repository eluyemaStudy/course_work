#include "Method.h"
#include "Matrix.h"
#include "vector"
using namespace std;
bool Method::accuracyСheck(Matrix before, Matrix after) {
    if (before.getRowNum() == after.getRowNum() && before.getColumnNum() == after.getColumnNum()) {
        for (int i = 0; i < before.getRowNum(); i++)
            if (abs(after.getElementByRowColumn(i, 0) - before.getElementByRowColumn(i, 0)) > e)
                return false;
        return true;
    }
    return false;
}

Matrix Method::getX0() {
    Matrix X;
    vector <vector<long double>> X0;
    for (int i = 0; i < B.getRowNum(); i++) {
        vector<long double> element;
        element.push_back(B.getElementByRowColumn(i, 0) / A.getElementByRowColumn(i, i));
        X0.push_back(element);
    }
    X.changeMainMatrix(X0);
    return X;
}

void Method::clearLog() {
    Matrix Log;
    log = Log;
}

void Method::setLog(vector <vector<long double>> Log) {
    log.changeMainMatrix(Log);
}

vector<long double> Method::getLogRow(Matrix before, Matrix after) {
    before = before.getTranspMatrix();
    after = after.getTranspMatrix();
    vector<long double> logRow;
    for (int i = 0; i < after.getColumnNum(); i++)
        logRow.push_back(after.getElementByRowColumn(0, i));
    for (int i = 0; i < after.getColumnNum(); i++)
        logRow.push_back(abs(after.getElementByRowColumn(0, i) - before.getElementByRowColumn(0, i)));
    logRow.push_back(e);
    return logRow;
}

Method::Method(Matrix a,
               Matrix b,
               long double E) {
    A = a;
    B = b;
    e = E;
};

Matrix Method::getA() const {
    return A;
};

Matrix Method::getB() const {
    return B;
};

Matrix Method::getLog() const {
    return log;
};

void Method::setSystem(Matrix a, Matrix b, long double E ) {
    A = a;
    B = b;
    e = E;
}
