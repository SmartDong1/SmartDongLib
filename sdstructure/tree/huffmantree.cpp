//
// Created by Administrator on 2020/9/2.
//

#include <boost/shared_ptr.hpp>
#include "huffmantree.h"
namespace SmartDongLib {
    /**
        * <p>根据元素key来获取哈夫曼编码
        * @tparam KeyType
        * @tparam ElemType
        * @param key 元素key
        * @return  哈夫曼编码
        */
    template<class KeyType, class ElemType>
    std::string HuffmanTree<KeyType, ElemType>::getHuffmanCodeByKey(KeyType key) {
        std::string ret="";
        boost::shared_ptr<TreeNode<KeyType,ElemType>> nodetemp = this->getNodeByKey(key, true);
        if (!nodetemp)
            return ret;
        boost::shared_ptr<HuffmanTree<KeyType,ElemType>> node = boost::static_pointer_cast<HuffmanTree<KeyType,ElemType>>(nodetemp);
        while (node->parent()!=NULL){
            if (node->parent()->leftChild() == node){
                ret.insert(0,"0");
            } else{
                ret.insert(0,"1");
            }
            node=node->parent();
        }
        return ret;
    }
    /**
     * <p> 跟据Elem來获取哈夫曼编码
     * @tparam KeyType
     * @tparam ElemType
     * @param e  节点的elem
     * @return  哈夫曼编码
     */
    template<class KeyType, class ElemType>
    std::string HuffmanTree<KeyType, ElemType>::getHuffmanCodeByElem(ElemType e) {
        std::string ret="";
        boost::shared_ptr<TreeNode<KeyType,ElemType>> nodetemp = this->getNodeByElem(e, true);
        if (!nodetemp)
            return ret;
        boost::shared_ptr<HuffmanTree<KeyType,ElemType>> node = boost::static_pointer_cast<HuffmanTree<KeyType,ElemType>>(nodetemp);
        while (node->parent()!=NULL){
            if (node->parent()->leftChild() == node){
                ret.insert(0,"0");
            } else{
                ret.insert(0,"1");
            }
            node=node->parent();
        }
        return ret;
    }




}