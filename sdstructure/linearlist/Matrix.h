//
// Created by Administrator on 2020/12/5.
// 矩阵 二维数组

#ifndef SMARTDONGLIB_MATRIX_H
#define SMARTDONGLIB_MATRIX_H
#include "tsMatrix.cpp"
namespace SmartDongLib {
    template<typename ElemType>
    class Matrix;
    template<typename ElemType>
    class SquareMatrix;
    template<typename ElemType>
    class UnitMatrix;
    template<typename ElemType>
    class DiagonalMatrix;
    template<typename ElemType>
    class MatrixUtil;

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

        virtual Matrix<ElemType> operator *(Matrix<ElemType> &) ;
        Matrix<ElemType>& operator +=(ElemType) ;
        Matrix<ElemType>& operator +=(Matrix<ElemType> &) ;

        SquareMatrix<ElemType> operator +(DiagonalMatrix<ElemType> &) ;
        Matrix<ElemType> operator *(DiagonalMatrix<ElemType> &);
        Matrix<ElemType> operator *(UnitMatrix<ElemType> &);
        Matrix<ElemType>   transposition();
        Integer getTheRows() const;
        Integer getTheCols() const;
        Matrix<ElemType> rightJoin(Matrix<ElemType>);
        Matrix<ElemType> divideMatrix(int rowBegin,int rowEnd,int colBegin,int colEnd);
        const Array<ElemType> &getMatrix() const;
        Matrix<ElemType> simplyTransform();
        SquareMatrix<ElemType> inverse();
        void rowSwap(int row1 ,int row2);
        virtual void initMatrixBy2DArray( Array<ElemType> array,int theRow, int thecol);

        void setTheRows(Integer theRows);

        void setTheCols(Integer theCols);

        void setMatrix(const Array<ElemType> &matrix);

    protected:
        Integer theRows_;
        Integer theCols_;
        Array<ElemType> matrix_;
    };
    /**
     * 方阵
     * @tparam ElemType
     */
    template<typename ElemType>
    class SquareMatrix: public Matrix<ElemType>{
    public:
        explicit SquareMatrix(int i):Matrix<ElemType>(i,i){}
        void initMatrixBy2DArray(Array<ElemType> array,int i){
            Matrix<ElemType>::initMatrixBy2DArray(array,i,i);
        }

    };

    /**
     * 对角矩阵
     * @tparam ElemType
     */
    template<typename ElemType>
    class DiagonalMatrix: public SquareMatrix<ElemType>{
    public:
        explicit DiagonalMatrix(int i):SquareMatrix<ElemType>(i){}
        Matrix<ElemType> operator *(Matrix<ElemType> &);

    };




    /**
     * 单位矩阵
     * @tparam ElemType
     */
    template<typename ElemType>
    class UnitMatrix: public DiagonalMatrix<ElemType>{
    public:
        explicit UnitMatrix(int i):DiagonalMatrix<ElemType>(i){
            for (int row = 0; row < this->theRows_ ; ++row) {
                this->matrix_[row * this->theCols_ + row] = 1;
            }
        }
        Matrix<ElemType> operator *(Matrix<ElemType> &);

    };



    template<typename ElemType>
    class MatrixUtil{
    public:
        static SquareMatrix<ElemType> convert2SquareMatrix(Matrix<ElemType>&);
        static tsMatrix<ElemType> convert2TsMatrix(Matrix<ElemType>&);
        static Matrix<ElemType> convertTsMatrix2Matrix(tsMatrix<ElemType>&);
        static bool isSquareMatrix(Matrix<ElemType>);
        static bool isUnitMatrix(Matrix<ElemType>);
        static bool isZeroMatrix(Matrix<ElemType>);
        static void printMatrix(Matrix<ElemType> a);
    };




}

#endif //SMARTDONGLIB_MATRIX_H
