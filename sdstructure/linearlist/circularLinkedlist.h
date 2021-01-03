//
// Created by hu on 2020/8/3.
// 循环链表和循环链表工具类
//
#ifndef SMARTDONGLIB_CIRCULARLINKEDLIST_H
#define SMARTDONGLIB_CIRCULARLINKEDLIST_H
#include <boost/enable_shared_from_this.hpp>
#include "linkList.cpp"


using namespace  boost;
namespace SmartDongLib {
//    template<class ElemType>
//    class circularLinkedlist: public LinkList<ElemType> {
//    public:
//        circularLinkedlist(){ this->next=this;}
//        circularLinkedlist(ElemType data){ this->data=data; this->next=this;}
//    };
//    template<class ElemType>
//    class  circularLinklistUtil: public LinkListUtil<ElemType>{
//    public:
//         Size listLenth(LinkList<ElemType> &L);
//         STATUS listMerge(LinkList<ElemType> & L1,LinkList<ElemType>&  L2,bool isMergeHead= true);
//    };


    template<class ElemType>
    class circularLinkedlist: public LinkList<ElemType>, public enable_shared_from_this<circularLinkedlist <ElemType>> {
    public:
        circularLinkedlist(){}
        circularLinkedlist(ElemType data){ this->data=data;}
        shared_ptr<circularLinkedlist> getThis()
        {
            return this->shared_from_this();
        }
        void tocircularLinkedlist(){this->next = getThis();}

    };
    template<class ElemType>
    class  circularLinklistUtil: public LinkListUtil<ElemType>{
    public:
        STATUS listMerge(boost::shared_ptr  < LinkList<ElemType>> L1, boost::shared_ptr  < LinkList<ElemType>>  L2, bool isMergeHead= true);
        Size listLenth( boost::shared_ptr  < LinkList<ElemType>> L);
    };



}

#endif //SMARTDONGLIB_CIRCULARLINKEDLIST_H
