#include "Jacoby.h"
#include "vector"
Jacoby::Jacoby(Matrix a,Matrix b,long double E):Method(a,b,E){};
Matrix Jacoby::getSolve(){
    clearLog();
    vector<vector<long double>> Log;
    Matrix D_inverse = A.getDiagonalMatrix().getInverseMatrix();
    Matrix L_U = A.getLowerTriangleMatrix().getAdditionMatrix(A.getUpperTriangleMatrix());
    Matrix X = getX0();
    Log.push_back(getLogRow(X,X));
    Matrix Xbefore;
    do{
        Xbefore = X;
        X = D_inverse.getMultiplyMatrix(B.getSubtractMatrix(L_U.getMultiplyMatrix(X)));
        Log.push_back(getLogRow(Xbefore,X));
    }while(!accuracyСheck(Xbefore,X));
    log.changeMainMatrix(Log);
    return X;
}