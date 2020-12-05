//
// Created by Administrator on 2020/12/5.
//

#include "Matrix.h"
template<class ElemType>
SmartDongLib::Matrix<ElemType>::Matrix(int therow, int thecol)
{
    if (therow<=0 || thecol <=0){
        std::string err="matrix init fail,the row&col must be positive"  ;
        throw ArrayIndexOutOfBoundsException(err);
     }
    theRows_=therow;
    theCols_=thecol;
    matrix_.initArray(2, therow, thecol);
}

template<class ElemType>
SmartDongLib::Matrix<ElemType>::Matrix(const SmartDongLib::Matrix<ElemType> &a)
{
    theRows_=a.theRows_;
    theCols_=a.theCols_;
    matrix_=a.matrix_;
}


template<class ElemType>
ElemType &SmartDongLib::Matrix<ElemType>::operator()(int i, int j)  {
    return matrix_ [ i*theCols_ + j];
}

template<class ElemType>
SmartDongLib::Matrix<ElemType> &SmartDongLib::Matrix<ElemType>::operator=(const SmartDongLib::Matrix<ElemType> &a) {
    theRows_=a.theRows_;
    theCols_=a.theCols_;
    matrix_=a.matrix_;
    return  *this;
}


//region Getter
template<class ElemType>
SmartDongLib::Integer SmartDongLib::Matrix<ElemType>::getTheRows() const {
    return theRows_;
}

template<class ElemType>
SmartDongLib::Integer SmartDongLib::Matrix<ElemType>::getTheCols() const {
    return theCols_;
}

template<class ElemType>
const SmartDongLib::Array<ElemType> &SmartDongLib::Matrix<ElemType>::getMatrix() const {
    return matrix_;
}
//endregion
template<class ElemType>
SmartDongLib::Matrix<ElemType> SmartDongLib::Matrix<ElemType>::operator+( ElemType a )  {
    Matrix<ElemType> ret(theRows_,theCols_);
    for ( int i=0 ; i < matrix_.getElemtotal();i++){
        ret.matrix_[i]= matrix_[i] +a ;
    }
    return  ret;
}
template<class ElemType>
SmartDongLib::Matrix<ElemType> &SmartDongLib::Matrix<ElemType>::operator+=( ElemType a) {
    for ( int i=0 ; i < matrix_.getElemtotal();i++){
        matrix_[i] += a ;
    }
    return *this;
}
template<class ElemType>
SmartDongLib::Matrix<ElemType> SmartDongLib::Matrix<ElemType>::operator-( ElemType a)  {
    Matrix<ElemType> ret(theRows_,theCols_);
    for ( int i=0 ; i < matrix_.getElemtotal();i++){
        ret.matrix_[i]= matrix_[i] -a ;
    }
    return  ret;
}

template<class ElemType>
SmartDongLib::Matrix<ElemType> SmartDongLib::Matrix<ElemType>::operator+(SmartDongLib::Matrix<ElemType> & a)  {
    if (matrix_.getElemtotal() != a.matrix_.getElemtotal()){
        std::string err="The number of elements should be equal,this:" ;
        throw ArrayStackOverflowException(err);
    }
    Matrix<ElemType> ret(theRows_,theCols_);
    for ( int i =0; i < matrix_.getElemtotal();i++){
        ret.matrix_[i]=matrix_[i] +a.matrix_[i] ;
    }
    return ret;
}

template<class ElemType>
SmartDongLib::Matrix<ElemType> SmartDongLib::Matrix<ElemType>::operator-(SmartDongLib::Matrix<ElemType> &a)  {
    if (matrix_.getElemtotal() != a.matrix_.getElemtotal()){
        std::string err="The number of elements should be equal,this:";
        throw ArrayStackOverflowException(err);
    }
    Matrix<ElemType> ret(theRows_,theCols_);
    for ( int i=0 ; i < matrix_.getElemtotal();i++){
        ret.matrix_[i]=matrix_[i] -a.matrix_[i] ;
    }
    return ret;
}

template<class ElemType>
SmartDongLib::Matrix<ElemType> &SmartDongLib::Matrix<ElemType>::operator+=(SmartDongLib::Matrix<ElemType> & a)  {
    if (matrix_.getElemtotal() != a.matrix_.getElemtotal()){
        std::string err="The number of elements should be equal";
        throw ArrayStackOverflowException(err);
    }
    for ( int i=0 ; i < matrix_.getElemtotal();i++){
        matrix_[i] +=a.matrix_[i] ;
    }
    return *this;
}

template<class ElemType>
SmartDongLib::Matrix<ElemType> SmartDongLib::Matrix<ElemType>::operator*(SmartDongLib::Matrix<ElemType> & b)  {
    if (this->theCols_ != b.theRows_){
        std::string err="Matrix multiplication requery b.col and b.rows to be equal"  ;
        throw ArrayStackOverflowException(err);
    }
    Size retRows= theRows_;
    Size retCols= b.theCols_;
    Matrix<ElemType> ret(retRows, retCols);
    for (int elemIndex = 0; elemIndex < ret.matrix_.getElemtotal(); ++elemIndex) {
        ret.matrix_[elemIndex] = 0;
    }
    // ret[i,j] = a[i,k] * b[k,j]   k belong to 0....thecols
    for (int i = 0; i < retRows ; ++i) {
        for (int k = 0; k < theCols_; ++k) {
            for (int j = 0; j < retCols; ++j) {
//                ElemType temp1,temp2;
//                matrix_.value(temp1,i,k);
//                b.matrix_.value(temp2,k,j);
                ElemType temp = ( (*this)(i,k) * b( k,j) );
                ret(i,j) += temp;
            }
        }
    }
    return ret;
}

template<class ElemType>
SmartDongLib::Matrix<ElemType>  SmartDongLib::Matrix<ElemType>::transposition() {
    Size retRows=theCols_ ;
    Size retCols=theRows_ ;
    Matrix<ElemType> ret(retRows, retCols);
    for (int i = 0; i < retRows; ++i) {
        for (int j = 0; j < retCols; ++j) {
            ret(i,j) = (*this)(j,i);
        }
    }
    return ret;
}


