//
// Created by hu on 2020/8/3.
//

#include <iostream>
#include "circularLinkedlist.h"
namespace SmartDongLib{
//    template<class ElemType>
//    int circularLinklistUtil<ElemType>::listLenth(LinkList<ElemType> &L) {
//        LinkList<ElemType> *p = &L;
//        int len=0;
//        while (p->next && p->next != &L){
//            len++;
//            p=p->next;
//        }
//        return  len;
//    }
//
//    template<class ElemType>
//    STATUS circularLinklistUtil<ElemType>::listMerge(LinkList<ElemType> &L1, LinkList<ElemType> &L2, bool isMergeHead) {
//        LinkList<ElemType> *p1 = &L1;
//        LinkList<ElemType> *p2 = &L2;
//        //如果两个都为空则合并失败
//        if(!p1 || !p2){
//            return SD_CONST::SD_FAIL;
//        }
//
//        //确定L1的最后一个结点
//        while(p1->next && p1->next != &L1){
//            p1=p1->next;
//        }
//        //如果不要合并头结点，直接关联到L2—>next
//        if (!isMergeHead){
//            p2=p2->next;
//        }
//        p1->next=p2;
//        while(p2->next && p2->next != &L2){
//            p2=p2->next;
//        }
//        p2->next=&L1;
//        return SD_CONST::SD_SUCCESS;
//    }
    template<class ElemType>
    int circularLinklistUtil<ElemType>::listLenth(shared_ptr<LinkList<ElemType>> L) {
        boost::shared_ptr  < LinkList<ElemType>> p =L;
        int len=0;
        while (p->next && p->next != L){
            len++;
            p=p->next;
        }
        return  len;
    }

    template<class ElemType>
    STATUS circularLinklistUtil<ElemType>::listMerge(shared_ptr<LinkList<ElemType>> L1,
                                                     shared_ptr<LinkList<ElemType>> L2, bool isMergeHead) {
        boost::shared_ptr  < LinkList<ElemType>> p1 =L1;
        boost::shared_ptr  < LinkList<ElemType>> p2 =L2;
        //如果两个都为空则合并失败
        if(!p1 || !p2){
            return SD_CONST::SD_FAIL;
        }

        //确定L1的最后一个结点
        while(p1->next && p1->next !=L1){
            p1=p1->next;
        }
        //如果不要合并头结点，直接关联到L2—>next
        if (!isMergeHead){
            p2=p2->next;
        }
        p1->next=p2;
        while(p2->next && p2->next != L2){
            p2=p2->next;
        }
        p2->next=L1;
        return SD_CONST::SD_SUCCESS;
    }
}