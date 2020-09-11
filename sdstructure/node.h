//
// Created by Administrator on 2020/9/11.
//

#ifndef SMARTDONGLIB_NODE_H
#define SMARTDONGLIB_NODE_H

#endif //SMARTDONGLIB_NODE_H

namespace SmartDongLib{
    template<class KeyType,class ElemType >
    class Node{
    public:
        Node()=default;
        Node(KeyType k ,ElemType e){key_=k;elem_=e;}
        KeyType key() const {
            return key_;
        }

        Node& key(KeyType key) {
            Node::key_ = key;
            return *this;
        }

        ElemType elem() const {
            return elem_;
        }

        Node&  elem(ElemType elemType) {
            Node::elem_ = elemType;
            return *this;
        }
        bool  operator <(Node & a){
            return  key_ < a.key_;
        }
        bool  operator ==(Node & a){
            return  key_ == a.key_;
        }
        bool  operator <=(Node & a){
            return  key_ <= a.key_;
        }bool  operator >=(Node & a){
            return  key_ >= a.key_;
        }bool  operator >(Node & a){
            return  key_ > a.key_;
        }bool  operator !=(Node & a){
            return  key_ != a.key_;
        }
    private:
        KeyType key_;
        ElemType elem_;
    };
}