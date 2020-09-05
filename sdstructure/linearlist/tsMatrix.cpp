//
// Created by hu on 2020/8/16.
//

#include "tsMatrix.h"
namespace SmartDongLib {
    template<class ElemType>
    tsMatrix<ElemType>  tsMatrix<ElemType>::transpose() {
        tsMatrix<ElemType> ret;
        ret.colnum_=rownum_ ; ret.rownum_=colnum_;ret.tnum_=tnum_;
        ret.data_.initArray(1,data_.elemtotal());
        int rowElemNum[ret.rownum_];
        int cpotNum[ret.rownum_];
        if (tnum_>0){
            //初始化所有转置后的各个行数;
            for (int i = 0; i < ret.rownum_; ++i) {
                rowElemNum[i] = 0;
            }
            for (int j = 0; j < tnum_ ; ++j) {
                triple<ElemType> e ;
                data_.value(e,j);
                ++rowElemNum[e.colindex];
            }
            //求转置后每一行第一个元素的应放data的位置
            cpotNum[0] = 0;
            for (int col = 1; col < ret.rownum_ ; ++col) {
                cpotNum[col] = cpotNum[col-1] +rowElemNum[col-1];
            }
            //接下来就是取元素然后 把元素放在对应的位置。
            for (int p = 0; p < tnum_ ; ++p) {
                triple<ElemType> e ;
                data_.value(e,p);
                int col = e.colindex;
                int q = cpotNum[col];
                triple<ElemType> dat ;
                dat.rowindex=e.colindex;
                dat.colindex=e.rowindex;
                dat.elem=e.elem;
                ret.data_.assign(dat,q);
                ++cpotNum[col];
            }

        }
        ret.setRowPos();
        return ret;
    }

    template<class ElemType>
    tsMatrix<ElemType>& tsMatrix<ElemType>::operator=(const tsMatrix<ElemType> &a) {
        data_ = a.data_;
        rownum_ = a.rownum_;
        colnum_=a.colnum_;
        tnum_=a.tnum_;
        rowPos_=a.rowPos_;
        //setRowPos();
        return *this;
    }

    template<class ElemType>
    bool tsMatrix<ElemType>::isUnitMatrix() {
         if (rownum_ != colnum_){
            return false;
        }
        if(rownum_ != tnum_){
            return false;
        }
        //行列非零元长度相等
        for (int i = 0; i < rownum_ ; ++i) {
            if (!(data_[i].rowindex == data_[i].colindex && data_[i].rowindex==i && data_[i].elem == 1 ))
                return false;
        }
        return true;
    }

    template<class ElemType>
    tsMatrix<ElemType> tsMatrix<ElemType>::operator*( tsMatrix<ElemType> &a) {
        if (colnum_ != a.rownum_){
            throw MatrixIndexInvalidBoundsException("矩阵维度无法做乘法");
        }
        if (tnum_ * a.tnum_ == 0){
            throw MatrixIndexInvalidBoundsException("零矩阵乘法异常");
        }

        //先把元素个数初始化成0
        int retTu=0 , retMu=rownum_,retNu=a.colnum_;
        Array <triple<ElemType>> retData;
        retData.initArray(2,retMu,retNu);
        ElemType ctemp[rownum_];

        //遍历矩阵 M中data arow行,找到N中对应的相同的N.data.row == M.data.col的位置范围:
        // M中的 rowPos_[arow] ~ tp; 相同行标   N 中的  brow ~ t 相同的行标 ,其中 M.col = brow~t=N.row
        for (int arow = 0; arow < rownum_; ++arow) {
            //按矩阵行遍历
            for (int i = 0; i < rownum_; ++i) {
               ctemp[i]=0;
            }
            //查询对于矩阵arow行的 非零元素的范围rowPos_[arow]<= x <tp
            int tp =arow < rownum_-1?rowPos_[arow+1]:tnum_;//M
            for (int p = rowPos_[arow]; p < tp; ++p) {
                //遍历arow行非零元素,对于每个data[p]元素的列值对应矩阵a的行位置范围
                //a.rowPos_[data_[p].colindex]<= x < t
                int brow = data_[p].colindex;
                int t =brow < a.rownum_ -1 ? a.rowPos_[brow+1]:a.tnum_;
                for (int q = a.rowPos_[brow]; q < t ; ++q) {
                    //此时，对于每个data[p] (arow，brow) 和a.data[q] (brow,coll) 元素相乘累加
                    int ccol = a.data_[q].colindex;
                    std::cout<< "arow"<<arow<<"ccol"<<ccol<<":"<<data_[p].elem <<"*"<<a.data_[q].elem<<"\n";
                    ctemp[ccol]  += data_[p].elem * a.data_[q].elem;
                }
            }
            //确认了第 arow 行和a矩阵的乘积后赋值后再遍历下一行
            for (int ccol = 0; ccol < retNu; ++ccol ) {
                if (ctemp[ccol]){
                    retData[retTu++] = triple<ElemType>(arow,ccol,ctemp[ccol]);
                 }
            }
        }

        return  tsMatrix<ElemType>(retMu,retNu,retTu,retData);
    }


    template<class ElemType>
    tsMatrix<ElemType> tsMatrix<ElemType>::operator+(tsMatrix<ElemType>& a) {
        if (colnum_ != a.colnum_ || rownum_!= a.rownum_){
            throw MatrixIndexInvalidBoundsException("矩阵维度无法做加法");
        }
        //先把元素个数初始化成0
        int retTu=0 , retMu=rownum_,retNu=colnum_;
        Array <triple<ElemType>> retData;
        retData.initArray(2,retMu,retNu);
        for (int tn = 0,atn =0; tn <tnum_ || atn <a.tnum_ ; ) {

            if (tn >=tnum_){
                //如果M矩阵先遍历完,把 a 矩阵剩下的赋值
                 while (atn < a.tnum_ ) {
                    retData[retTu++]=a.data_[atn++];
                }
            } else if (atn >=a.tnum_){
                //如果a矩阵先遍历完,把 M 矩阵剩下的赋值
                while (tn <tnum_ ) {
                    retData[retTu++]=data_[tn++];
                }
            } else if (data_[tn].rowindex == a.data_[atn].rowindex){
                if (data_[tn].colindex == a.data_[atn].colindex){
                    //如果行列相等，元素相加并赋值
                    retData[retTu++] = triple<ElemType>(
                            data_[tn].rowindex,
                            data_[tn].colindex,
                            data_[tn].elem+ a.data_[atn].elem);
                    tn++;atn++;
                }else{
                    //如果行相等列不相等取最小的列值
                    retData[retTu++]=data_[tn].colindex < a.data_[atn].colindex?data_[tn++]:a.data_[atn++];
                }
            } else{
                //如果行不相等
                retData[retTu++]=data_[tn].rowindex < a.data_[atn].rowindex?data_[tn++]:a.data_[atn++];
            }
        }

        return tsMatrix<ElemType>(rownum_,colnum_,retTu,retData);
    }




    template<class ElemType>
    void tsMatrix<ElemType>::setRowPos() {
        rowPos_ = boost::shared_ptr<int[]>(new int[rownum_]);
        for (int i = 0; i <rownum_ ; ++i) {
            rowPos_[i]=0;
        }

        for (int j = 0; j < tnum_; ++j) {
            int row=data_[j].rowindex;
            for (int r = row+1; r < rownum_; ++r) {
                rowPos_[r]++;
            }
        }
    }

    template<class ElemType>
    tsMatrix<ElemType> tsMatrix<ElemType>::operator*(const int a) {
        tsMatrix<ElemType> ret(*this);
        for (int i = 0; i < ret.tnum_; ++i) {
            ret.data_[i].elem *=a;
        }
        return ret;
    }


}
