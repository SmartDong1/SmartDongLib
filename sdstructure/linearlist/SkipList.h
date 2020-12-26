//
// Created by Administrator on 2020/12/22.
// 跳表：在有序链表的基础上再加上索引链表。效率同平衡二叉树，链表头数据不放任何数据
//

#ifndef SMARTDONGLIB_SKIPLIST_H
#define SMARTDONGLIB_SKIPLIST_H

#include <boost/shared_ptr.hpp>
#include "linkList.cpp"
#include <math.h>
namespace SmartDongLib {
    template<class ElemType>
    class SkipList {
    public:
        class IndexStruct{
        public:
            ElemType position() const;
            void position(ElemType position);
//            void pointer(const boost::shared_ptr<LinkList<ElemType>> &pointer);
//            const boost::shared_ptr<LinkList<ElemType>>& pointer() const{ return pointer_;};
            bool operator <(IndexStruct a);
            bool operator ==(IndexStruct a);
            bool operator >(IndexStruct a);
            IndexStruct& operator =(const IndexStruct & a);
            IndexStruct(ElemType position, const boost::shared_ptr<LinkList<ElemType>> &pointer);
            IndexStruct(){}
            boost::shared_ptr<LinkList<ElemType>>& nextPointer() { return pointer_->next;};
            enum IndexStructNodeType{pointToData=0,pointToIndex};

            struct U{
//                U(){
//                    new (&this->dataPointer)  boost::shared_ptr<LinkList<ElemType>>;
//                    new (&this->indexPointer)  boost::shared_ptr<LinkList<IndexStruct>>;
//                }
//                ~U(){
//                    //if (head_)
//                    dataPointer.~shared_ptr();
//                    indexPointer.~shared_ptr();
//                }
                boost::shared_ptr<LinkList<IndexStruct>> indexPointer;
                boost::shared_ptr<LinkList<ElemType>> dataPointer;
            }pointer_;
            const U &pointer() const;

            void pointer(const U &pointer);

        public:
            ElemType position_;      //datalist的索引位
//            U pointer_;             //datalist或indexlist的指针
        };
        explicit SkipList(Integer skipstep = 3):skipstep_(skipstep){}
        boost::shared_ptr<LinkList<ElemType>> findDataNode(int i);

    public:
        int findIndexListPosition(int indexlevel,ElemType dataPos);
        void rebuildIndex(ElemType startIndex );
        void removeByPos(Size e);
        void removeByElem(ElemType e);
        void insertElem(ElemType e);

        const std::vector<boost::shared_ptr<LinkList<IndexStruct>>> &indexLinklist() const{
            return indexLinklist_;
        };
        void indexLinklist(const std::vector<boost::shared_ptr<LinkList<IndexStruct>>> &indexLinklist){
            indexLinklist_=indexLinklist;
        };
        const boost::shared_ptr<LinkList<ElemType>> &dataLinklist() const{
            return  dataLinklist_;
        };
        void dataLinklist(const boost::shared_ptr<LinkList<ElemType>> &dataLinklist){
            dataLinklist_=dataLinklist;
            if (dataLinklist_ ->next){
                rebuildIndex(dataLinklist_->next->data);
            }else{
                indexLinklist_.clear();
            }
        };

    private:
        std::vector< boost::shared_ptr<LinkList<IndexStruct>>> indexLinklist_;//索引链表,数据是地址
        boost::shared_ptr<LinkList<ElemType>> dataLinklist_; //有序数据链表
        LinkListUtil<ElemType> dataListUtil_;
        LinkListUtil<IndexStruct> indexListUtil_;

        const Integer  skipstep_;
    };


}

#endif //SMARTDONGLIB_SKIPLIST_H
