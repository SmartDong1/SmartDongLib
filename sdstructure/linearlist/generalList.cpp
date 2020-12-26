//
// Created by hu on 2020/8/21.
//

#include "generalList.h"
namespace SmartDongLib {
    template<class AtomType>
    GeneralListNodeType generalList<AtomType>::getHead(AtomType &outAtom, generalList<AtomType> *outHead) {
        std::string retString = "";
        AtomType tempatom;
        if (tag_ == ATOM){
            outAtom=elem.atom_;
            outHead =NULL;
        }
        if (tag_ == LIST ) {
            outHead = elem.head_;
        }
        return tag_;
    }

    template<class AtomType>
    boost::shared_ptr<generalList<AtomType>> generalList<AtomType>::getTail() {
        return this->tail;
    }

    template<class AtomType>
    Size generalList<AtomType>:: getDepth() {
        if (tag_ == ATOM){
            return  0 ;
        }
        if (tag_ == LIST && elem.head_ ==NULL && !tail_){
            return  0 ;
        }else if (elem.head_ ==NULL && tail_){
            return  tail_->getDepth();
        }else if (elem.head_ !=NULL && !tail_){
            return  1+ elem.head_->getDepth();
        } else{
            return  std::max(tail_->getDepth(),1+ elem.head_->getDepth());
        }
    }

    template<class AtomType>
    std::string generalList<AtomType>::prSize() {
        std::string ret;
        if (tag_==ATOM){

            ret.append(std::string(sizeof(AtomType),elem.atom_));
        }else {
            ret="(";
            if (elem.head_!=NULL){
                ret.append(elem.head_->prSize());
            }
            ret.append(")");
        }
        if (tail_){
            ret.append(",");
            ret.append(tail_->prSize());
        }

        return ret;

    }



    template<class AtomType>
    Size generalList<AtomType>::getElemCount() {
        if (tag_==ATOM && !tail_){
            return 1;
        } else if(tag_==ATOM && tail_){
            return 1+ tail_->getElemCount();
        }else{
            if (elem.head_ == NULL && tail_){
                return tail_->getElemCount();
            }else if (elem.head_ != NULL && tail_){
                return elem.head_->getElemCount() + tail_->getElemCount();
            } else if (elem.head_ != NULL && !tail_){
                return 0;
            }else {
                //elem.head_ = NULL && !tail_
                return elem.head_->getElemCount();
            }

        }
    }

    template<class AtomType>
    Size generalList<AtomType>::getLength() {
        if (!tail_){
            return 1;
        }
        return 1+tail_->getLength();
    }

    template<class AtomType>
    void generalList<AtomType>::insertFirst(AtomType e) {
        if (tag_==ATOM){
            throw GeneralListException("原子无法进行表插入");
        }
        if (elem.head_ == NULL){
            elem.head_ = new generalList<AtomType>(e);
        } else{
            //头指针不为空，那么头指针的内容要移到尾指针
            boost::shared_ptr<generalList<AtomType>> temptail = tail_;  //原来的尾指针
            tail_ = boost::shared_ptr<generalList<AtomType>> (elem.head_); //原来的头指针变成尾指针第一个元素
            boost::shared_ptr<generalList<AtomType>> nexttail = tail_;
            while (nexttail->tail_){
                nexttail = nexttail->tail_;
            }
            nexttail->tail_ = temptail;
            elem.head_ = new generalList<AtomType>(e);
        }
    }

    template<class AtomType>
    void generalList<AtomType>::insertFirst(boost::shared_ptr<generalList<AtomType>> e) {
        if (tag_==ATOM){
            throw GeneralListException("原子无法进行表插入");
        }
        if (elem.head_ == NULL){
            elem.head_ = e;
        } else{
            //头指针不为空，那么头指针的内容要移到尾指针
            boost::shared_ptr<generalList<AtomType>> temptail = tail_;  //原来的尾指针
            tail_ = boost::shared_ptr<generalList<AtomType>> (elem.head_); //原来的头指针变成尾指针第一个元素
            boost::shared_ptr<generalList<AtomType>> nexttail = tail_;
            while (nexttail->tail_){
                nexttail = nexttail->tail_;
            }
            nexttail->tail_ = temptail;
            elem.head_ = e;
        }
    }

    template<class AtomType>
    void generalList<AtomType>::deleteFirst() {
        if (tag_==ATOM){
            throw GeneralListException("原子无法进行表删除");
        }
        elem.head_ = tail_;
        if (tail_){
            tail_=tail_->tail_;

        }
        elem.head_->tail_=NULL;

    };

}