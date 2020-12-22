//
// Created by Administrator on 2020/12/22.
// 跳表：在有序链表的基础上再加上索引链表。效率同平衡二叉树，链表头数据不放任何数据
//

#ifndef SMARTDONGLIB_SKIPLIST_H
#define SMARTDONGLIB_SKIPLIST_H

#include <boost/shared_ptr.hpp>
#include "linkList.h"
namespace SmartDongLib {
    template<class ElemType>
    class SkipList {
    private:
        std::vector< boost::shared_ptr<LinkList<ElemType>*>> indexLinklist;//索引链表,数据是地址
        boost::shared_ptr<LinkList<ElemType>> dataLinklist; //有序数据链表
    };
}

#endif //SMARTDONGLIB_SKIPLIST_H
