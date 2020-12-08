//
// Created by Administrator on 2020/12/5.
// 矩阵 二维数组

#ifndef SMARTDONGLIB_MATRIX_H
#define SMARTDONGLIB_MATRIX_H
#include "Array.cpp"
namespace SmartDongLib {
    template<typename ElemType>
    class Matrix {
    public:
        Matrix(int theRow, int thecol);
        ~Matrix(){matrix_.destroyArray();}
        Matrix(const  Matrix<ElemType>& a);
        ElemType & operator()(int i, int j)  ;
        Matrix<ElemType> & operator = (const Matrix<ElemType>&);
        Matrix<ElemType> operator +(ElemType)  ;
        Matrix<ElemType> operator -(ElemType)  ;
        Matrix<ElemType> operator +(Matrix<ElemType> &) ;
        Matrix<ElemType> operator -(Matrix<ElemType> &) ;
        Matrix<ElemType> operator *(Matrix<ElemType> &) ;
        Matrix<ElemType>& operator +=(ElemType) ;
        virtual ElemType get(int i, int j);
        Matrix<ElemType>& operator +=(Matrix<ElemType> &) ;
        Matrix<ElemType>   transposition();
        Integer getTheRows() const;
        Integer getTheCols() const;
        const Array<ElemType> &getMatrix() const;
        Matrix<ElemType> rowTransform();
        void rowSwap(int row1 ,int row2);
        void initMatrixBy2DArray( Array<ElemType> array,int theRow, int thecol);
    private:
        Integer theRows_;
        Integer theCols_;
        Array<ElemType> matrix_;
    };


}

#endif //SMARTDONGLIB_MATRIX_H
