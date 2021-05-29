/*!
    \file matrix.h
*/

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

/*!
    Класс состояния матрицы. 
*/

template<class T>
class MatrixState{
    using StorageIt = typename std::map<std::vector<size_t>, T>::iterator; 
    std::map<std::vector<size_t>, T> values;
public:
    void InsertValue(const std::vector<size_t>& indexes, const T& value){
        values[indexes] = value;
    }
    
    StorageIt begin(){
        return values.begin();
    }
    
    StorageIt end(){
        return values.end();
    }
    
    StorageIt Find(const std::vector<size_t>& indexes){
        return values.find(indexes);
    }
    
    size_t Size() const{
        return values.size();
    }
};

/*!
    Обобщённый класс матрицы, хранящий индексы доступа к подматрицам 
*/

template<class T, T DEFAULT, size_t DIM = 2>
class Matrix{
    friend class Matrix<T, DEFAULT, DIM + 1>;    
        
    std::shared_ptr<MatrixState<T>> p_state;    
    std::vector<size_t> indexes;
    Matrix(std::shared_ptr<MatrixState<T>> i_p_state) : p_state(i_p_state){
        
    }
public:
    Matrix(){
        p_state = std::make_shared<MatrixState<T>>();
    }
    
    /*!
        Оператор [] возращает матрицу меньшую размером на 1, чем исходная
    */

    Matrix<T, DEFAULT, DIM - 1> operator[](size_t idx) const{
        Matrix<T, DEFAULT, DIM - 1> res(p_state);
        std::copy(indexes.begin(), indexes.end(), std::back_inserter(res.indexes));
        res.indexes.push_back(idx);
        return res;
    }
    
    size_t Size() const{
        return p_state->Size();
    }
    
    auto begin(){
        return p_state->begin();
    }
    
    auto end(){
        return p_state->end();
    }
};

/*!
    Матрица размерности 0. Необходима для записи значений типа T в объект класса MatrixState
*/

template<class T, T DEFAULT>
class Matrix<T, DEFAULT, 0>{
    friend class Matrix<T, DEFAULT, 1>;
    
    std::vector<size_t> indexes;
    std::shared_ptr<MatrixState<T>> p_state;    
    Matrix(std::shared_ptr<MatrixState<T>> i_p_state) : p_state(i_p_state){
        
    }
public:    
    
    /*!
        Оператор = помещает объект типа Т в объект класса MatrixState
    */

    Matrix<T, DEFAULT, 0>& operator = (const T& val){
        p_state->InsertValue(indexes, val);
        return *this;
    }
    
    friend bool operator == (const Matrix<T, DEFAULT, 0>& null_mat, const T& other){
        auto it = null_mat.p_state->Find(null_mat.indexes);
        T val = (it == null_mat.p_state->end() ? DEFAULT : it->second);
        return val == other;
    }

    friend bool operator == (const T& other, const Matrix<T, DEFAULT, 0>& null_mat){        
        return null_mat == other;
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix<T, DEFAULT, 0>& null_mat){
        auto it = null_mat.p_state->Find(null_mat.indexes);
        if(it == null_mat.p_state->end())
            out << DEFAULT;
        else
            out << it->second;
            
        return out;
    }
};