//
// Created by hu on 2020/8/21.
//  广义表

#ifndef SMARTDONGLIB_GENERALLIST_H
#define SMARTDONGLIB_GENERALLIST_H
#include <boost/shared_ptr.hpp>
#include <algorithm>
#include "const.h"
namespace SmartDongLib {
    enum GeneralListNodeType{ATOM=0,LIST};
    class GeneralListException: public std::runtime_error{
    public:
        GeneralListException():std::runtime_error("GeneralListException"){}
        GeneralListException(const std::string& __arg):std::runtime_error("GeneralListException"+__arg){}

    };
    template <class AtomType>
    class generalList {
    public:
        generalList(){tag_=LIST;elem.head_=NULL;tail_=NULL;}
        generalList(AtomType a, boost::shared_ptr<generalList<AtomType>> t=NULL){
            tag_=ATOM;
            elem.atom_=a;
            tail_=t;
        }
        generalList(boost::shared_ptr<generalList<AtomType>> ha, boost::shared_ptr<generalList<AtomType>> t=NULL){
            tag_=LIST;
            elem.head_=ha;
            tail_=t;
        }
        GeneralListNodeType getHead(AtomType & outAtom, generalList<AtomType>* outHead);
        boost::shared_ptr<generalList<AtomType>>  getTail();
        Size getDepth();
        std::string prSize();
        Size getElemCount();
        Size getLength();
        void insertFirst(AtomType e);
        void insertFirst(boost::shared_ptr<generalList<AtomType>> e);
        void deleteFirst();
    public:
        GeneralListNodeType tag_;    //表明是原子还是广义子表
        //广义子表的头指针 和元素类型
        union U{
            U(){
                new (&this->head_)  boost::shared_ptr<generalList<AtomType>>;
            }
            ~U(){
                //if (head_)
                head_.~shared_ptr();
            }
            AtomType atom_;
            boost::shared_ptr<generalList<AtomType>> head_;
        }elem;
        boost::shared_ptr<generalList<AtomType>> tail_; //尾指针

    };


}

#endif //SMARTDONGLIB_GENERALLIST_H
