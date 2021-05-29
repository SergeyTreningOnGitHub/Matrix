/*!
    \file main.cpp
*/
#include "matrix.h"

using namespace std;

/*!
    Пример исаользования matrix
*/

int main(){
    Matrix<int, 0> mat;
    for(int i = 0;i < 10;i++){
        mat[i][i] = i;
        mat[i][9 - i] = 9 - i;
    }    

    for(int i = 0;i < 10;i++){
        for(int j = 0;j < 10;j++){
            cout << mat[i][j] << " ";
        }

        cout << endl;
    }

    cout << "Size matrix is " << mat.Size() << endl;    
}