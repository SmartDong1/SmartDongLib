//
// Created by hu on 2020/8/2.
//

#include "linkList.h"
namespace SmartDongLib {
//    /**
//     * <p>对链表L的第 i-1 个点之后进行插入，头结点算第0个点
//     * @tparam ElemType  数据类型
//     * @param L  链表
//     * @param i  位置
//     * @param e  要插入的数据
//     * @return   是否插入成功
//     */
//    template<class ElemType>
//    STATUS LinkListUtil<ElemType>::listInsert(LinkList<ElemType> &L, Size i, ElemType e) {
//        LinkList<ElemType> *p = &L;
//        if ( i ==0){
//            LinkList<ElemType> *s =new LinkList<ElemType>;
//            s ->data  =L.data ;
//            s ->next=L.next;
//            L.data=e;
//            L.next = s;
//            return SD_CONST::SD_SUCCESS;
//        }
//
//        Size j = 0 ;
//        while ( p && j< i -1 ){
//            //寻找第i-1个点
//            p =  p->next;
//            j++;
//        }
//        if (!p ||  j>i-1){
//            return listInsert(L,listLenth(L)+1,e);
//        }
//        LinkList<ElemType> *s =new LinkList<ElemType>;
//        s ->data  =e ;
//        s ->next=p->next;
//        p->next=s;
//        return SD_CONST::SD_SUCCESS;
//    }
//    /**
//     * <p> 在链表L尾部追加数据 e
//     * @tparam ElemType 数据类型
//     * @param L  链表
//     * @param e  数据
//     * @return   是否追加成功
//     */
//    template<class ElemType>
//    STATUS LinkListUtil<ElemType>::listAppend(LinkList<ElemType> &L, ElemType e) {
//        return listInsert(L,listLenth(L)+1,e);
//    }
//    /**
//     * <p>计算出 L 的长度，只有头结点算第 0 个
//     * @tparam ElemType  数据类型
//     * @param L          链表
//     * @return           链表长度
//     */
//    template<class ElemType>
//    Size LinkListUtil<ElemType>::listLenth(LinkList<ElemType> &L) {
//        LinkList<ElemType> *p = &L;
//        Size len=0;
//        while (p->next){
//            len++;
//            p=p->next;
//        }
//        return  len;
//    }
//    /**
//     * <p> 删除链表L中的第i个元素,头结点为第0个元素
//     * @tparam ElemType
//     * @param L 链表
//     * @param i 位置
//     * @return  是否成功删除
//     */
//    template<class ElemType>
//    STATUS LinkListUtil<ElemType>::listDelete(LinkList<ElemType> &L, Size i) {
//        LinkList<ElemType> *p = &L;
//        if (i== 0 && p->next){
//            p=p->next;
//            L.data=p->data;
//            L.next = p->next;
//            delete p;
//        }
//        Size j = 0 ;
//        while ( p->next && j< i -1 ){
//            //寻找第i-1个点
//            p =  p->next;
//            j++;
//        }
//        //如果 p->next 为空,或者 i 比L的长度大则删除位置错误
//        if ( !(p->next) || j > i -1)
//            return SD_CONST::SD_FAIL;
//        LinkList<ElemType> *q = p->next;
//        p->next=q->next;
//        delete q;
//        return SD_CONST::SD_SUCCESS;
//    }
//    /**
//        * <p> 删除链表L中的第i个元素,头结点为第0个元素
//        * @tparam ElemType
//        * @param L 链表
//        * @return  是否成功删除
//        */
//    template<class ElemType>
//    STATUS LinkListUtil<ElemType>::listPop(LinkList<ElemType> &L) {
//        return listDelete(L,listLenth(L));
//    }
//
//    /**
//     * <p> 获取链表L第 i 个元素的值,头结点为第0个位置
//     * @tparam ElemType 数据类型
//     * @param L 链表
//     * @param i 位置
//     * @return 第i个值
//     */
//    template<class ElemType>
//    ElemType LinkListUtil<ElemType>::listGet(LinkList<ElemType> &L, Size i) {
//        LinkList<ElemType> *p = &L;
//        Size j=0;
//        while(p && j<i){
//            p=p->next;
//            j++;
//        }
//        //如果数据为空,或者遍历完全部都比i小
//        if ( !p || j > i)
//            return SD_CONST::SD_FAIL;
//        return p->data;
//    }
//    /**
//     * <p>两个链表合并到L1上
//     * @tparam ElemType 数据类型
//     * @param L1 链表1
//     * @param L2 链表2
//     * @param isMergeHead 是否合并L2头结点到L1
//     * @return  是否合并成功
//     */
//    template<class ElemType>
//    STATUS LinkListUtil<ElemType>::listMerge(LinkList<ElemType> &L1, LinkList<ElemType>& L2,bool isMergeHead) {
//        LinkList<ElemType> *p1 = &L1; LinkList<ElemType> *p2 = &L2;
//        //如果两个都为空则合并失败
//        if(!p1 || !p2){
//            return SD_CONST::SD_FAIL;
//        }
//
//        //确定L1的最后一个结点
//        while(p1->next){
//            p1=p1->next;
//        }
//        //如果不要合并头结点，直接关联到L2—>next
//        if (!isMergeHead){
//            p2=p2->next;
//        }
//        p1->next=p2;
//        return SD_CONST::SD_SUCCESS;
//    }

    //---------------------------------------BOOST---------------------
    /**
    * <p>对链表L的第 i-1 个点之后进行插入，头结点算第0个点
    * @tparam ElemType  数据类型
    * @param L  链表
    * @param i  位置
    * @param e  要插入的数据
    * @return   是否插入成功
    */
    template<class ElemType>
    STATUS LinkListUtil<ElemType>::listInsert(boost::shared_ptr  < LinkList<ElemType>>L, Size i, ElemType e) {
        boost::shared_ptr  < LinkList<ElemType>> p =L;
        if ( i ==0){
            boost::shared_ptr  < LinkList<ElemType>> s(new LinkList<ElemType>);
            s ->data  =L->data ;
            s ->next=L->next;
            L->data=e;
            L->next = s;
            return SD_CONST::SD_SUCCESS;
        }

        Size j = 0 ;
        while ( p && j< i -1 ){
            //寻找第i-1个点
            p =  p->next;
            j++;
        }
        if (!p ||  j>i-1){
            return listInsert(L,listLenth(L)+1,e);
        }
        boost::shared_ptr  < LinkList<ElemType>> s(new LinkList<ElemType>);
        s ->data  =e ;
        s ->next=p->next;
        p->next=s;
        return SD_CONST::SD_SUCCESS;
    }
    /**
     * <p> 在链表L尾部追加数据 e
     * @tparam ElemType 数据类型
     * @param L  链表
     * @param e  数据
     * @return   是否追加成功
     */
    template<class ElemType>
    STATUS LinkListUtil<ElemType>::listAppend(boost::shared_ptr  < LinkList<ElemType>>L, ElemType e) {
        return listInsert(L,listLenth(L)+1,e);
    }
    /**
     * <p>计算出 L 的长度，只有头结点算第 0 个
     * @tparam ElemType  数据类型
     * @param L          链表
     * @return           链表长度
     */
    template<class ElemType>
    Size LinkListUtil<ElemType>::listLenth(boost::shared_ptr  < LinkList<ElemType>>L) {
        boost::shared_ptr  < LinkList<ElemType>> p =L;
        Size len=0;
        while (p->next){
            len++;
            p=p->next;
        }
        return  len;
    }
    /**
     * <p> 删除链表L中的第i个元素,头结点为第0个元素
     * @tparam ElemType
     * @param L 链表
     * @param i 位置
     * @return  是否成功删除
     */
    template<class ElemType>
    STATUS LinkListUtil<ElemType>::listDelete(boost::shared_ptr  < LinkList<ElemType>>L, Size i) {
        boost::shared_ptr  < LinkList<ElemType>> p =L;
        if (i== 0 && p->next){
            p=p->next;
            L->data=p->data;
            L->next = p->next;
        }
        Size j = 0 ;
        while ( p->next && j< i -1 ){
            //寻找第i-1个点
            p =  p->next;
            j++;
        }
        //如果 p->next 为空,或者 i 比L的长度大则删除位置错误
        if ( !(p->next) || j > i -1)
            return SD_CONST::SD_FAIL;
        boost::shared_ptr  < LinkList<ElemType>> q (p->next);
        p->next=q->next;
        return SD_CONST::SD_SUCCESS;
    }
    /**
        * <p> 删除链表L中的第i个元素,头结点为第0个元素
        * @tparam ElemType
        * @param L 链表
        * @return  是否成功删除
        */
    template<class ElemType>
    STATUS LinkListUtil<ElemType>::listPop(boost::shared_ptr  < LinkList<ElemType>>L) {
        return listDelete(L,listLenth(L));
    }

    /**
     * <p> 获取链表L第 i 个元素的值,头结点为第0个位置
     * @tparam ElemType 数据类型
     * @param L 链表
     * @param i 位置
     * @return 第i个值
     */
    template<class ElemType>
    ElemType LinkListUtil<ElemType>::listGet(boost::shared_ptr  < LinkList<ElemType>>L, Size i) {
        boost::shared_ptr  < LinkList<ElemType>> p =L;
        Size j=0;
        while(p && j<i){
            p=p->next;
            j++;
        }
        //如果数据为空,或者遍历完全部都比i小
        if ( !p || j > i)
            return SD_CONST::SD_FAIL;
        return p->data;
    }
    /**
     * <p>两个链表合并到L1上
     * @tparam ElemType 数据类型
     * @param L1 链表1
     * @param L2 链表2
     * @param isMergeHead 是否合并L2头结点到L1
     * @return  是否合并成功
     */
    template<class ElemType>
    STATUS LinkListUtil<ElemType>::listMerge(boost::shared_ptr  < LinkList<ElemType>>L1, boost::shared_ptr  < LinkList<ElemType>> L2, bool isMergeHead) {
        boost::shared_ptr  < LinkList<ElemType>> p1 =L1;
        boost::shared_ptr  < LinkList<ElemType>> p2 =L2;
        //如果两个都为空则合并失败
        if(!p1 || !p2){
            return SD_CONST::SD_FAIL;
        }

        //确定L1的最后一个结点
        while(p1->next){
            p1=p1->next;
        }
        //如果不要合并头结点，直接关联到L2—>next
        if (!isMergeHead){
            p2=p2->next;
        }
        p1->next=p2;
        return SD_CONST::SD_SUCCESS;
    }
    /**
     * <p>根据值返回在链表中的位置，循环链表可用
     * @tparam ElemType
     * @param L1
     * @param elem
     * @return
     */
    template<class ElemType>
    Size LinkListUtil<ElemType>::listGetIndex(boost::shared_ptr<LinkList<ElemType>> L1, ElemType elem) {
        boost::shared_ptr  < LinkList<ElemType>> p1 =L1;
        Size ret=-1;
        if (p1->data==elem){
            ret++;
            return ret;
        }
        ret++;
        p1= p1->next;
        while(p1 && p1 !=L1){
            ret++;
            if (p1->data == elem){
                return ret;
            }
            p1= p1->next;
        }
        return -1;
    }

    template<class ElemType>
    STATUS LinkListUtil<ElemType>::listDeleteByData(boost::shared_ptr<LinkList<ElemType>> L, ElemType e) {
       Size index =listGetIndex(L,e);
       return listDelete(L,index);
    }


}