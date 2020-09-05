//
// Created by hu on 2020/8/16.
//

#ifndef SMARTDONGLIB_TSMATRIX_H
#define SMARTDONGLIB_TSMATRIX_H
#include "Array.cpp"

namespace SmartDongLib {
    template<class ElemType>
    class triple{
    public:
        triple(){}
        triple(int row,int col , ElemType e){ rowindex=row;colindex=col;elem=e;}
        triple(const triple &t){ rowindex=t.rowindex;colindex=t.colindex;elem=t.elem;}
        int rowindex;
        int colindex;
        ElemType elem;
        bool operator <(triple t2){
            return  elem<t2.elem;
        }
    };
    class MatrixIndexInvalidBoundsException: public std::logic_error{
        public:
        MatrixIndexInvalidBoundsException():std::logic_error("Matrix Index or bounds Invalid Exception"){}
        MatrixIndexInvalidBoundsException(const std::string& __arg):std::logic_error("Matrix Index or bounds Invalid Exception:"+__arg){}

    };
    template<class ElemType>
    class tsMatrix {
    public:
        tsMatrix(){rownum_ = 0;colnum_=0;tnum_=0; }
        tsMatrix(int rownum,int colnum,int tnum, Array<triple<ElemType>> & array){
//            Array<triple<ElemType>> temp(array);
            data_ = array;
            rownum_ = rownum;
            colnum_=colnum;
            tnum_=tnum;
            setRowPos();
        }
        tsMatrix<ElemType>& operator =(const tsMatrix<ElemType> & a);   //拷贝赋值运算符
        tsMatrix<ElemType> operator *( tsMatrix<ElemType> & a);
        tsMatrix<ElemType> operator *( int a);
        tsMatrix<ElemType> operator +( tsMatrix<ElemType> & a);
        tsMatrix(const tsMatrix & t){
            //拷贝构造函数
            data_ = t.data_;
            rownum_ = t.rownum_;
            colnum_=t.colnum_;
            tnum_=t.tnum_;
            rowPos_=t.rowPos_;
        }
        bool isUnitMatrix();
        tsMatrix<ElemType> transpose();

    public:
        void setRowPos();
        Array <triple<ElemType>> data_;
       // int * rowPos_;   //
        boost::shared_ptr<int[]> rowPos_;
        int rownum_;
        int colnum_;
        int tnum_;   //非零元个数
    };


}

#endif //SMARTDONGLIB_TSMATRIX_H
