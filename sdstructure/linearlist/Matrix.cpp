//
// Created by Administrator on 2020/12/5.
//

#include "Matrix.h"
template<typename ElemType>
SmartDongLib::Matrix<ElemType>::Matrix(int therow, int thecol):matrix_(2, therow, thecol)
{
    if (therow<=0 || thecol <=0){
        std::string err="matrix init fail,the row&col must be positive"  ;
        throw ArrayIndexOutOfBoundsException(err);
     }
    theRows_=therow;
    theCols_=thecol;
    for (int i = 0; i < theRows_ ; ++i) {
        for (int j = 0; j <  theCols_; ++j) {
            matrix_ [ i*theCols_ + j] = 0;
        }
    }
}

template<typename ElemType>
SmartDongLib::Matrix<ElemType>::Matrix(const SmartDongLib::Matrix<ElemType> &a)
{
    theRows_=a.theRows_;
    theCols_=a.theCols_;
    matrix_=a.matrix_;
}


template<typename ElemType>
ElemType &SmartDongLib::Matrix<ElemType>::operator()(int i, int j)  {
    return matrix_ [ i*theCols_ + j];
}

template<typename ElemType>
SmartDongLib::Matrix<ElemType> &SmartDongLib::Matrix<ElemType>::operator=(const SmartDongLib::Matrix<ElemType> &a) {
    theRows_=a.theRows_;
    theCols_=a.theCols_;
    matrix_=a.matrix_;
    return  *this;
}


//region Getter
template<typename ElemType>
SmartDongLib::Integer SmartDongLib::Matrix<ElemType>::getTheRows() const {
    return theRows_;
}

template<typename ElemType>
SmartDongLib::Integer SmartDongLib::Matrix<ElemType>::getTheCols() const {
    return theCols_;
}

template<typename ElemType>
const SmartDongLib::Array<ElemType> &SmartDongLib::Matrix<ElemType>::getMatrix() const {
    return matrix_;
}
//endregion
template<typename ElemType>
SmartDongLib::Matrix<ElemType> SmartDongLib::Matrix<ElemType>::operator+( ElemType a )  {
    Matrix<ElemType> ret(theRows_,theCols_);
    for ( int i=0 ; i < matrix_.getElemtotal();i++){
        ret.matrix_[i]= matrix_[i] +a ;
    }
    return  ret;
}
template<typename ElemType>
SmartDongLib::Matrix<ElemType> &SmartDongLib::Matrix<ElemType>::operator+=( ElemType a) {
    for ( int i=0 ; i < matrix_.getElemtotal();i++){
        matrix_[i] += a ;
    }
    return *this;
}
template<typename ElemType>
SmartDongLib::Matrix<ElemType> SmartDongLib::Matrix<ElemType>::operator-( ElemType a)  {
    Matrix<ElemType> ret(theRows_,theCols_);
    for ( int i=0 ; i < matrix_.getElemtotal();i++){
        ret.matrix_[i]= matrix_[i] -a ;
    }
    return  ret;
}

template<typename ElemType>
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

template<typename ElemType>
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

template<typename ElemType>
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

template<typename ElemType>
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
/**
 * <p>矩阵转置变换
 * @tparam ElemType
 * @return
 */
template<typename ElemType>
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
/**
 * <p> 二维数组转矩阵对象
 * @tparam ElemType
 * @param array
 * @param therow
 * @param thecol
 */
template<typename ElemType>
void SmartDongLib::Matrix<ElemType>::initMatrixBy2DArray(SmartDongLib::Array<ElemType> array, int therow, int thecol) {
    if (therow<=0 || thecol <=0){
        std::string err="matrix init fail,the row&col must be positive"  ;
        throw ArrayIndexOutOfBoundsException(err);
    }
    theRows_=therow;
    theCols_=thecol;
    matrix_ = array;
}

template<typename ElemType>
ElemType SmartDongLib::Matrix<ElemType>::get(int i, int j) {
    return matrix_ [ i*theCols_ + j];
}
/**
 * 矩阵行变换成最简矩阵
 * @tparam ElemType
 * @return
 */
template<typename ElemType>
SmartDongLib::Matrix<ElemType> SmartDongLib::Matrix<ElemType>::simplyTransform() {
    Matrix<ElemType> ret(*this);

    for (int transferRow = 0; transferRow < theRows_; ++transferRow) {
        //寻找最长元素行
        int firstNotNullCol = 0;
        for (; firstNotNullCol < ret.theCols_; ++firstNotNullCol) {
            int row = transferRow;
            bool isfind= false;
            for (; row < ret.theRows_; ++row) {
                ElemType firstelem=ret(row, firstNotNullCol);
                if (!close(firstelem, (ElemType)0)) {
                    isfind = true;
                    break;
                }
            }
            if (isfind){
                ret.rowSwap(transferRow,row);
                break;
            }
        }
        if (firstNotNullCol >= ret.theCols_){
            //零矩阵或者后继行都是0
            return ret;
        }
        //当前行化1
        Real factor = ret(transferRow,firstNotNullCol);
        for (int col = firstNotNullCol; col < ret.theCols_; ++col) {
            ElemType debug = ret(transferRow,col) ;
            ret(transferRow,col) =  ret(transferRow,col) / factor;

        }
        //后继行化0
        for (int i = 0 ; i <  ret.theRows_; ++i) {
            if ( i ==transferRow )
                continue;
            Real factor2 = ret(i,firstNotNullCol);
            for (int j = firstNotNullCol; j <  ret.theCols_; ++j) {
                ret(i,j) = ret(i,j) -  ret(transferRow,j) * factor2;
            }
        }
    }
    return ret;
}
/**
 * 矩阵行交换
 * @tparam ElemType
 * @param src1
 * @param src2
 */
template<typename ElemType>
void SmartDongLib::Matrix<ElemType>::rowSwap(int src1 ,int src2) {
    if (src1 < 0 || src2 <0 || src1 >=theRows_ || src2 >=theRows_ ){
        std::string err="matrix init fail,the row&col must be positive"  ;
        throw ArrayIndexOutOfBoundsException(err);
    }
    if (src1 == src2) {
        return;
    }

    for (int i = 0; i < theCols_; ++i) {
        ElemType temp = (*this)(src1,i);
        (*this)(src1,i) = (*this)(src2,i);
        (*this)(src2,i) =temp;
    }

}

/**
 * <p>矩阵逆变换
 * @tparam ElemType
 * @return
 */
template<typename ElemType>
SmartDongLib::SquareMatrix<ElemType> SmartDongLib::Matrix<ElemType>::inverse() {
    if (!MatrixUtil<ElemType>::isSquareMatrix(*this)){
        return SquareMatrix<ElemType>(1);
    }
    //在右边接入单位矩阵
    Matrix<ElemType> combineMatrix( theRows_, 2 *theCols_);
    for (int i = 0; i < theRows_; ++i) {
        for (int j = 0; j < theCols_; ++j) {
            combineMatrix(i,j) = (*this)(i,j);
        }
    }
    for (int k = 0; k < theCols_; ++k) {
        combineMatrix(k,k+theCols_) =1;
    }
    //进行行变换成最简矩阵
    combineMatrix = combineMatrix.simplyTransform();

    SquareMatrix<ElemType> leftMatrix(theRows_);
    for (int i = 0; i < theRows_; ++i) {
        for (int j = 0; j < theCols_; ++j) {
            leftMatrix(i,j)=combineMatrix(i,j);
        }
    }
    if (! MatrixUtil<ElemType>::isUnitMatrix(leftMatrix)){
        return SquareMatrix<ElemType>(1);
    }
    SquareMatrix<ElemType> ret (theRows_);
    for (int i = 0; i < theRows_; ++i) {
        for (int j = 0; j < theCols_; ++j) {
            ret(i,j)=combineMatrix(i,j+theCols_);
        }
    }
    return ret;
}

template<typename ElemType>
SmartDongLib::SquareMatrix<ElemType> SmartDongLib::MatrixUtil<ElemType>::Convert2SquareMatrix(Matrix<ElemType> src) {
    if (!isSquareMatrix(src)){
        throw ArrayIndexOutOfBoundsException("SquareMatrix init fail");
    }
    SquareMatrix<ElemType> ret(src.theRows_);
    ret.matrix_ = src.matrix_;
    return ret;
}

template<typename ElemType>
bool SmartDongLib::MatrixUtil<ElemType>::isSquareMatrix(SmartDongLib::Matrix<ElemType> src) {
    return src.getTheRows() == src.getTheCols();
}

template<typename ElemType>
bool SmartDongLib::MatrixUtil<ElemType>::isUnitMatrix(SmartDongLib::Matrix<ElemType> src) {
    if (isSquareMatrix(src)){
        for (int i = 0; i < src.getTheRows() ; ++i) {
            for (int j = 0; j < src.getTheCols() ; ++j) {
                if (i==j && src (i,j) != 1){
                    return false;
                } else if(i!=j && src (i,j) != 0){
                    return false;
                }
            }
        }
        return true;
    } else{
        return false;
    }
}

template<typename ElemType>
bool SmartDongLib::MatrixUtil<ElemType>::isZeroMatrix(SmartDongLib::Matrix<ElemType> src) {
    for (int i = 0; i < src.getTheRows() ; ++i) {
        for (int j = 0; j < src.getTheCols() ; ++j) {
            if (src (i,j) != 0)
                return false;
        }
    }
    return true;
}

template<typename ElemType>
void SmartDongLib::MatrixUtil<ElemType>::printMatrix(SmartDongLib::Matrix<ElemType> a) {
    for (int i = 0; i < a.getTheRows(); ++i) {
        for (int j = 0; j < a.getTheCols(); ++j) {
            std::cout<< a(i,j)<<" ";
        }
        std::cout << std::endl;
    }
}
