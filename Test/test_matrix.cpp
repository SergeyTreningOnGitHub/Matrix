#include "matrix.h"
#include <sstream>
#include <gtest/gtest.h>

using namespace std;

/*!
    This is test for matrix
*/

TEST(Matrix, TestSizeMatrix){
    ostringstream out;    
    Matrix<int, -1, 3> cube_mat;
    
    ASSERT_EQ(cube_mat.Size(), 0);
    auto val = cube_mat[0][100][200];
    out << val;
    ASSERT_EQ(cube_mat.Size(), 0);
    val = 3;    
    ASSERT_EQ(cube_mat.Size(), 1);
}

TEST(Matrix, TestDefault){
    Matrix<int, -1, 3> cube_mat;
        

    ASSERT_EQ(cube_mat[300][12][13], -1);
    cube_mat[300][12][13] = 2;
    ASSERT_EQ(cube_mat[300][12][13], 2);    
}

TEST(Matrix, TestIterator){
    ostringstream out;
    Matrix<int, -1, 3> cube_mat;
    for(int i = 0;i < 3;i++){
        cube_mat[i][i][i] = i;
    }

    cube_mat[300][400][500];
    for(auto& [indexes, val] : cube_mat){
        for(size_t idx : indexes){
            out << idx << " ";
        }

        out << val << endl;
    }


    ASSERT_EQ("0 0 0 0\n1 1 1 1\n2 2 2 2\n", out.str());
}