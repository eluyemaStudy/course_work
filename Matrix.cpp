#include "Matrix.h"
#include "iostream"
#include <vector>
#include "fstream"
#include "iomanip"
#include "math.h"
#include <algorithm>

using namespace std;





Matrix::Matrix() {}

Matrix::Matrix(vector<vector<long double>> matrix) {
    changeMainMatrix(matrix);
}

vector<long double> Matrix::readRow(string line) {
    vector<long double> row;
    while (line.empty() != 1)
        if (line[0] == ' ')
            line = line.substr(1);
        else {
            int pos = line.find(" ");
            string numberStr = line.substr(0, pos);
            if (numberStr.find('-') != -1)
                if (count(numberStr.begin(), numberStr.end(), '-') != 1 || numberStr[0] != '-' ||
                    numberStr.size() == 1) {
                    row.clear();
                    return row;
                }
            if (numberStr.find('.') != -1)
                if (count(numberStr.begin(), numberStr.end(), '.') != 1 || numberStr[0] == '.' ||
                    numberStr[numberStr.size() - 1] == '.' ||
                    numberStr[0] == '-' && numberStr[1] == '.') {
                    row.clear();
                    return row;
                }
            row.push_back(stod(numberStr));
            if (pos == -1)
                break;
            line = line.substr(pos);
        }
    return row;
}

bool Matrix::isMatrixValid(vector<vector<long double>> matrix) {
    if (matrix.size() == 0)
        return false;
    int m = matrix[0].size();
    for (int i = 1; i < matrix.size(); i++) {
        if (m != matrix[i].size())
            return false;
    }
    return true;
}

bool Matrix::isMatrixQuadr(vector<vector<long double>> matrix) {
    int n = matrix.size();
    for (int i = 0; i < matrix.size(); i++)
        if (n != matrix[i].size())
            return false;
    return true;
}
//void printTT(Matrix m){
//    int c = m.getColumnNum();
//    cout<<"\nColumn = "<<c;
//    int r = m.getRowNum();
//    cout<<"\nRow = "<<r<<endl;
//    cout<<endl;
//    for(int i = 0;i<r;i++) {
//        for (int j = 0; j < c; j++)
//            cout<<m.getElementByRowColumn(i,j)<<' ';
//        cout<<endl;
//    }
//    cout<<endl;
//}
vector<vector<long double>> Matrix::transpositionMatrix() {
    vector<vector<long double>> transpMatr;
    for (int j = 0; j < mainMatrix[0].size(); j++) {
        vector<long double> row;
        for (int i = 0; i < mainMatrix.size(); i++)
            row.push_back(mainMatrix[i][j]);
        transpMatr.push_back(row);
    }
    return transpMatr;
}

void Matrix::multiplyRowDigit(vector<long double> &row, long double k) {
    for (int i = 0; i < row.size(); i++) {
        row[i] *= k;
        if (row[i] == -0)
            row[i] = 0;
    }
}

long double Matrix::getMultiplyRowRow(vector<long double> row1, vector<long double> row2) {
    long double sum = 0;
    for (int i = 0; i < row1.size(); i++) {

        sum += row2[i] * row1[i];
    }

    return sum;
}

void Matrix::subtractRowRow(vector<long double> &row1, vector<long double> &row2) {

    for (int i = 0; i < row1.size(); i++) {
        row1[i] -= row2[i];
        if (row1[i] == -0)
            row1[i] = 0;
    }
}

long double Matrix::determ() {
    vector<vector<long double>> copyMain = mainMatrix;
    vector<long double> multipliers;
    for (int i = 0; i < copyMain[0].size() - 1; i++) {
        if (copyMain[i][i] == 0) {
            for (int k = i; k < copyMain.size(); k++) {
                if (copyMain[k][i] != 0) {
                    subtractRowRow(copyMain[i], copyMain[k]);
                    if (i != 0)
                        i -= 1;
                    break;
                } else if (k == copyMain.size() - 1)
                    return 0;
            }
        }
        long double diagonalElement = copyMain[i][i];
        for (int j = i + 1; j < copyMain.size(); j++) {

            if (copyMain[j][i] != 0 && copyMain[j][i] != diagonalElement) {
                multipliers.push_back(copyMain[j][i] / diagonalElement);
                multiplyRowDigit(copyMain[j], diagonalElement / copyMain[j][i]);
            }
            if (copyMain[j][i] != 0) {
                subtractRowRow(copyMain[j], copyMain[i]);
                for (int p = 0; p < copyMain[j].size(); p++)
                    if (copyMain[j][p] != 0)
                        break;
                    else if (p == copyMain[j].size() - 1)
                        return 0;
            }
        }
    }
    long double det = 1;
    for (int i = 0; i < multipliers.size(); i++)
        det *= multipliers[i];
    for (int i = 0; i < copyMain.size(); i++) {
        det *= copyMain[i][i];
    }

    return det;
}

vector<long double> Matrix::getRow(int j) const {
    vector<long double> result;
    if (getRowNum() > j)
        result = mainMatrix[j];
    return result;
}

Matrix Matrix::multiplyMatrixDigit(long double k) {
    for (int i = 0; i < mainMatrix.size(); i++)
        for (int j = 0; j < mainMatrix[i].size(); j++){
            if(mainMatrix[i][j]==0)
                continue;
            mainMatrix[i][j] *= k;
        }
    return *this;
}

Matrix Matrix::getMultiplyMatrix(Matrix matr) {
    if (getColumnNum() == matr.getRowNum() ) {
        Matrix result;
        matr = matr.getTranspMatrix();//Для удобства умножения, получения строк которые я собираюсь умножить
        vector<vector<long double>> resultMatrix;
        for (int i = 0; i < getColumnNum(); i++) {
            vector<long double> row;
            for (int j = 0; j < matr.getRowNum(); j++)
                row.push_back(getMultiplyRowRow(mainMatrix[i], matr.getRow(j)));
            resultMatrix.push_back(row);
        }
        result.changeMainMatrix(resultMatrix);
        return result;
    }
    return matr;
}

long double Matrix::getElementByRowColumn(int i, int j) {
    if (mainMatrix.size() > i)
        if (mainMatrix[i].size() > j)
            return mainMatrix[i][j];
    return INT64_MAX;
}

bool Matrix::readMatrix(string path) {
    ifstream in(path);
    vector<vector<long double>> readedMatrix;
    string line;

    if (in.is_open()) {
        while (getline(in, line)) {
            if (line.find_first_not_of("-. 1234567890") != -1) {
                return false;
            }
            vector<long double> row = readRow(line);
            if (row.size() == 0)
                return false;
            readedMatrix.push_back(readRow(line));
        }
    }
    in.close();
    if (!isMatrixValid(readedMatrix)) {
        return false;
    }
    quadrMatrix = isMatrixQuadr(readedMatrix);
    mainMatrix = readedMatrix;
    return true;
};

void Matrix::changeMainMatrix(vector<vector<long double>> changes) {
    if (isMatrixValid(changes)) {
        quadrMatrix = isMatrixQuadr(changes);
        mainMatrix = changes;
    }
}

Matrix Matrix::getTranspMatrix() {
    Matrix transpMatr;
    transpMatr.changeMainMatrix(transpositionMatrix());
    return transpMatr;
}

Matrix Matrix::getInverseMatrix() {
    Matrix transpMatr;
    transpMatr.changeMainMatrix(transpositionMatrix());
    vector<vector<long double>> result;
    long double det = transpMatr.determ();
    for (int i = 0; i < transpMatr.getRowNum(); i++) {
        vector<long double> row;
        for (int j = 0; j < transpMatr.getColumnNum(); j++) {
            long double detMinor = transpMatr.getMinor(i, j);
            row.push_back(pow(-1, i + j + 2) * detMinor);
        }
        result.push_back(row);
    }
    transpMatr.changeMainMatrix(result);
    transpMatr.multiplyMatrixDigit(1 / det);
    return transpMatr;
}

long double Matrix::getMinor(int i, int j) {
    Matrix minor;
    // PrintMatrix();
    vector<vector<long double>> minorVector;
    // cout<<"i = "<<i<<"   j = "<<j<<endl;
    for (int q = 0; q < mainMatrix.size(); q++) {
        if (q == i)
            continue;
        vector<long double> row;
        for (int k = 0; k < mainMatrix[q].size(); k++) {
            if (k == j)
                continue;
            else {
                //cout<<mainMatrix[q][k]<<' ';
                row.push_back(mainMatrix[q][k]);
            }
        }
        minorVector.push_back(row);
    }
    //  printer(minorVector);
    minor.changeMainMatrix(minorVector);
    //minor.PrintMatrix();
    long double det = minor.determ();
    return det;
}

Matrix Matrix::getIdentityMatrix(int size) {
    Matrix m;
    vector<vector<long double>> IdentityMatrix;
    for (int i = 0; i < size; i++) {
        vector<long double> row;
        for (int j = 0; j < size; j++) {
            if (i != j)
                row.push_back(0);
            else
                row.push_back(1);
        }
        IdentityMatrix.push_back(row);
    }
    m.changeMainMatrix(IdentityMatrix);
    return m;
}

Matrix Matrix::getAdditionMatrix(Matrix matr) {
    if (getColumnNum() == matr.getColumnNum()) {
        if (getRowNum() == matr.getRowNum())
            for (int i = 0; i < getRowNum(); i++)
                for (int j = 0; j < getColumnNum(); j++)
                    matr.changeElementByRowColumn(i, j, mainMatrix[i][j] + matr.getElementByRowColumn(i, j));
    }
    return matr;
}

Matrix Matrix::getSubtractMatrix(Matrix matr) {
    if (getColumnNum() == matr.getColumnNum()) {
        if (getRowNum() == matr.getRowNum())
            for (int i = 0; i < getRowNum(); i++)
                for (int j = 0; j < getColumnNum(); j++)
                    matr.changeElementByRowColumn(i, j, mainMatrix[i][j] - matr.getElementByRowColumn(i, j));
    }
    return matr;
}

void Matrix::changeElementByRowColumn(int r, int c, long double value) {
    if (mainMatrix.size() > r)
        if (mainMatrix[0].size() > c)
            mainMatrix[r][c] = value;
}

vector<vector<long double>> Matrix::getMatrix() const {
    return mainMatrix;
}

Matrix Matrix::getLowerTriangleMatrix() const {
    vector<vector<long double>> lowerTriangle = mainMatrix;
    for (int i = 0; i < lowerTriangle.size(); i++) {
        for (int j = lowerTriangle[i].size() - 1; j >= i; j--) {
            lowerTriangle[i][j] = 0;
        }
    }
    Matrix lowerTriangleMatrix(lowerTriangle);
    return lowerTriangleMatrix;
}

Matrix Matrix::getUpperTriangleMatrix() const {
    vector<vector<long double>> upperTriangle = mainMatrix;
    for (int i = 0; i < upperTriangle.size(); i++) {
        for (int j = 0; j <= i; j++) {
            upperTriangle[i][j] = 0;
        }
    }
    Matrix upperTriangleMatrix(upperTriangle);
    return upperTriangleMatrix;
}

Matrix Matrix::getDiagonalMatrix() const {
    vector<vector<long double>> diagonal = mainMatrix;
    for (int i = 0; i < diagonal.size(); i++) {
        for (int j = 0; j < diagonal[i].size(); j++) {
            if (i == j)
                continue;
            diagonal[i][j] = 0;
        }
    }
    Matrix diagonalMatrix(diagonal);
    return diagonalMatrix;
}
bool Matrix::isSymmetric(){
    if(quadrMatrix) {
        for (int i = 1; i < mainMatrix.size(); i++){
            for (int j = i; i < mainMatrix.size(); i++)
                if (i == j)
                    continue;
                else if (mainMatrix[i][j] != mainMatrix[j][i])
                    return false;
        }
        return true;
    }
    return false;
}
bool Matrix::isSylvesterСriterion(){
    if(quadrMatrix){
    for(int i =1;i<=mainMatrix.size();i++){
        cout<<endl<<"Determ  = "<<getAngleMatrix(i).determ()<<endl;
        if(getAngleMatrix(i).determ()<=0)
            return false;
        }
        return true;
    }
    return false;
}
Matrix Matrix::getAngleMatrix(int i){
    Matrix A;
    if(quadrMatrix&&mainMatrix.size()>=i){
        vector<vector<long double>> angleMatrix;
        for(int k = 0;k<i;k++){
            vector<long double> row;
            for(int p=0;p<i;p++)
                row.push_back(mainMatrix[k][p]);
            angleMatrix.push_back(row);
        }
        A.changeMainMatrix(angleMatrix);
    }
    return A;
}
bool Matrix::isStrictlyDiagonallyDominant() {
    for (int i = 0; i < mainMatrix.size(); i++) {
        long double sum = 0;
        long double diagonalElement = abs(mainMatrix[i][i]);
        for (int j = 0; j < mainMatrix[i].size(); j++) {
            if (j != i)
                sum += abs(mainMatrix[i][j]);
        }
        if (sum >= diagonalElement)
            return false;
    }
    return true;
}

void Matrix::addRow(vector<long double> row) {
    if (mainMatrix.size()==0 || row.size() == mainMatrix[0].size()) {
        mainMatrix.push_back(row);
        quadrMatrix = isMatrixQuadr(mainMatrix);
    }
}

void Matrix::addColumn(vector<long double> column) {
    if (column.size() == mainMatrix.size()) {
        for (int i = 0; i < mainMatrix.size(); i++)
            mainMatrix[i].push_back(column[i]);
        quadrMatrix = isMatrixQuadr(mainMatrix);
    }
}
Matrix Matrix::getMultiplyMatrixDigit(long double d){
    if(d==-0)
        d=0;
    vector<vector<long double>> multiplyedMatrix=mainMatrix;
    for(int i =0;i<getRowNum();i++){
        for(int j =0;j<getColumnNum();j++)
            multiplyedMatrix[i][j]*=d;
    }
    Matrix m;
    m.changeMainMatrix(multiplyedMatrix);
    return m;
}
long double Matrix::getScalarProduct(Matrix matr){
    long double sum =0;
    if(getColumnNum()==1&&matr.getColumnNum()==1&&matr.getRowNum()==getRowNum()){
        for(int i =0;i<getRowNum();i++){
            sum+=getElementByRowColumn(i,0)*matr.getElementByRowColumn(i,0);
        }
    }
    return sum;
}
int Matrix::getColumnNum() const {
    return mainMatrix[0].size();
}

int Matrix::getRowNum() const {
    return mainMatrix.size();
}














