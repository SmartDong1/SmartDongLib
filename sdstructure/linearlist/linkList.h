//
// Created by hu on 2020/8/2.
// 链表类和链表工具类,头节点不装数据,模板元素需要重载 小于 和 等于号
//

#ifndef SMARTDONGLIB_LINKLIST_H
#define SMARTDONGLIB_LINKLIST_H
#include <boost/shared_ptr.hpp>
#include <const.h>

namespace SmartDongLib {
//    template<class ElemType>
//    class LinkList {
//    public:
//        ElemType data;
//        LinkList *next;
//        LinkList(ElemType d){data=d;next = 0;}
//        LinkList(){next = 0;}
//    };
//    template<class ElemType>
//    class LinkListUtil{
//    public:
//        virtual STATUS listInsert(LinkList<ElemType> & L,Size i ,ElemType e);
//        virtual STATUS listAppend(LinkList<ElemType> & L,ElemType e);
//        virtual Size listLenth(LinkList<ElemType> & L);
//        virtual STATUS listDelete(LinkList<ElemType> & L,Size i );
//        virtual STATUS listPop(LinkList<ElemType> & L);
//        virtual ElemType listGet(LinkList<ElemType> & L,Size i );
//        virtual STATUS listMerge(LinkList<ElemType> & L1,LinkList<ElemType> & L2,bool isMegerHead= true);
//    };

    template<class ElemType>
    class LinkList {
    public:
        ElemType data;
        boost::shared_ptr <LinkList<ElemType>> next;
        LinkList(ElemType d){ data=d;}
        LinkList(){}
    };
    template<class ElemType>
    class LinkListUtil{
    public:
        virtual  STATUS listInsert(boost::shared_ptr  < LinkList<ElemType>> L, Size i , ElemType e);
        virtual  STATUS listOrderInsert(boost::shared_ptr  < LinkList<ElemType>> L, ElemType e);
        virtual  STATUS listAppend(boost::shared_ptr  < LinkList<ElemType>> L, ElemType e);
        virtual  Size listLenth(boost::shared_ptr  < LinkList<ElemType>> L);
        virtual  STATUS listDelete(boost::shared_ptr  < LinkList<ElemType>> L, Size i );
        virtual  STATUS listDeleteByData(boost::shared_ptr  < LinkList<ElemType>> L, ElemType e );
        virtual  STATUS listPop( boost::shared_ptr  < LinkList<ElemType>> L);
        virtual  boost::shared_ptr  < LinkList<ElemType>> listGetNode(boost::shared_ptr  < LinkList<ElemType>> L, Size i );
        virtual  ElemType listGet(boost::shared_ptr  < LinkList<ElemType>> L, Size i );
        virtual  STATUS listMerge(boost::shared_ptr  < LinkList<ElemType>> L1, boost::shared_ptr  < LinkList<ElemType>>  L2, bool isMegerHead= true);
        virtual  Size listGetIndex(boost::shared_ptr  < LinkList<ElemType>> L1, ElemType elem);

    };
}


#endif //SMARTDONGLIB_LINKLIST_H
