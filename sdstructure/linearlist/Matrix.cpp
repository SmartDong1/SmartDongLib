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
SmartDongLib::Matrix<ElemType>  SmartDongLib::Matrix<ElemType>::operator*(SmartDongLib::Matrix<ElemType> & b)  {
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
    Matrix<ElemType> combineMatrix( *this);
    combineMatrix=combineMatrix.rightJoin(UnitMatrix<ElemType>(theCols_));
    //进行行变换成最简矩阵
    combineMatrix = combineMatrix.simplyTransform();
    //左半部分矩阵要求是单位阵时右半部分矩阵才是逆矩阵
    Matrix<ElemType> leftMatrix =combineMatrix.divideMatrix(0,theRows_,0,theCols_);
    Matrix<ElemType> rightMatrix =combineMatrix.divideMatrix(0,theRows_,theCols_,2*theCols_);
    SquareMatrix<ElemType> ret  = MatrixUtil<ElemType>::Convert2SquareMatrix(rightMatrix);
    if (! MatrixUtil<ElemType>::isUnitMatrix(leftMatrix)){
        return SquareMatrix<ElemType>(1);
    }

    return ret;
}

/**
 * 向右拼接矩阵
 * @tparam ElemType
 * @param src
 * @return
 */
template<typename ElemType>
SmartDongLib::Matrix<ElemType> SmartDongLib::Matrix<ElemType>::rightJoin(SmartDongLib::Matrix<ElemType> src) {
    if (theRows_  != src.theRows_ ){
        std::string err="matrix rightjoin fail,the row must be positive"  ;
        throw ArrayIndexOutOfBoundsException(err);
    }
    Matrix<ElemType> ret(theRows_,theCols_+src.theCols_);
    for (int i = 0; i < theRows_; ++i) {
        for (int j = 0; j < theCols_; ++j) {
            ret(i,j) = (*this)(i,j);
        }
    }
    for (int i = 0; i < src.theRows_; ++i) {
        for (int j = 0; j < src.theCols_; ++j) {
            ret(i,j+theCols_) = src(i,j);
        }
    }
    return ret;
}
/**
 * <p> 分割矩阵
 * @tparam ElemType
 * @param rowBegin 行开始位置(包含)
 * @param rowEnd   行结束位置(不包含)
 * @param colBegin 列开始位置(包含)
 * @param colEnd   列结束位置(不包含)
 * @return
 */
template<typename ElemType>
SmartDongLib::Matrix<ElemType>
SmartDongLib::Matrix<ElemType>::divideMatrix(int rowBegin, int rowEnd, int colBegin, int colEnd) {
    rowBegin = rowBegin<=0? 0 :rowBegin;
    rowEnd = rowEnd >= theRows_ ? theRows_:rowEnd;
    colBegin = colBegin<=0 ? 0 : colBegin;
    colEnd = colEnd >= theCols_ ? theCols_ : colEnd;
    Matrix<ElemType> ret(rowEnd-rowBegin,colEnd-colBegin);
    for (int i = rowBegin; i < rowEnd; ++i) {
        for (int j = colBegin; j < colEnd; ++j) {
            ret(i - rowBegin ,j-colBegin) =(*this)(i,j);
        }
    }
    return ret;
}

template<typename ElemType>
void SmartDongLib::Matrix<ElemType>::setTheRows(int theRows) {
    theRows_ = theRows;
}

template<typename ElemType>
void SmartDongLib::Matrix<ElemType>::setTheCols(int theCols) {
    theCols_ = theCols;
}

template<typename ElemType>
void SmartDongLib::Matrix<ElemType>::setMatrix(const SmartDongLib::Array<ElemType> &matrix) {
    matrix_ = matrix;
}

template<typename ElemType>
SmartDongLib::SquareMatrix<ElemType> SmartDongLib::Matrix<ElemType>::operator+(SmartDongLib::DiagonalMatrix<ElemType> & src) {
    if (theRows_  != src.theRows_  ||  theCols_  != src.theCols_  ){
        std::string err="matrix rightjoin fail,the row must be positive"  ;
        throw ArrayIndexOutOfBoundsException(err);
    }
     Matrix<ElemType> ret1(*this);
    for (int i = 0; i < theRows_; ++i) {
        ret1(i,i) += src(i,i);
    }
    SquareMatrix<ElemType> ret= MatrixUtil<ElemType>::Convert2SquareMatrix(ret1);
    return ret;
}

template<typename ElemType>
SmartDongLib::Matrix<ElemType>
SmartDongLib::Matrix<ElemType>::operator*(SmartDongLib::DiagonalMatrix<ElemType> & b) {
    if (this->theCols_ != b.theRows_){
        std::string err="Matrix multiplication requery b.col and b.rows to be equal"  ;
        throw ArrayStackOverflowException(err);
    }
    Matrix<ElemType> ret1(*this);
    for (int j = 0; j < ret1.theCols_; ++j) {
        for (int i = 0; i < ret1.theRows_; ++i) {
            ret1(i,j) *= b(j,j);
        }
    }
    return ret1;
}
template<typename ElemType>
SmartDongLib::Matrix<ElemType> SmartDongLib::DiagonalMatrix<ElemType>::operator*(Matrix<ElemType> & b) {
    if (this->getTheCols()  != b.getTheRows() ){
        std::string err="Matrix multiplication requery b.col and b.rows to be equal"  ;
        throw ArrayStackOverflowException(err);
    }
    Matrix<ElemType> ret1(b);
    for (int i = 0; i < ret1.getTheRows() ; ++i) {
        for (int j = 0; j < ret1.getTheCols() ; ++j) {
            ret1(i,j) *= (*this)(i,i);
        }
    }
    return ret1;
}


template<typename ElemType>
SmartDongLib::Matrix<ElemType> SmartDongLib::Matrix<ElemType>::operator*(SmartDongLib::UnitMatrix<ElemType> & b) {
    if (this->theCols_ != b.theRows_){
        std::string err="Matrix multiplication requery b.col and b.rows to be equal"  ;
        throw ArrayStackOverflowException(err);
    }
    return Matrix<ElemType>(*this);
}

template<typename ElemType>
SmartDongLib::Matrix<ElemType> SmartDongLib::UnitMatrix<ElemType>::operator*(Matrix<ElemType> & b) {
    if (this->getTheCols() != b.getTheRows()){
        std::string err="Matrix multiplication requery b.col and b.rows to be equal"  ;
        throw ArrayStackOverflowException(err);
    }
    return Matrix<ElemType>(b);

}
template<typename ElemType>
SmartDongLib::SquareMatrix<ElemType> SmartDongLib::MatrixUtil<ElemType>::Convert2SquareMatrix(Matrix<ElemType> src) {
    if (!isSquareMatrix(src)){
        throw ArrayIndexOutOfBoundsException("SquareMatrix init fail");
    }
    SquareMatrix<ElemType> ret(src.getTheRows());
    ret.setMatrix( src.getMatrix());
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
