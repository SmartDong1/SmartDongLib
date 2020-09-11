//
// Created by Administrator on 2020/9/11.
//
#include "digraph.h"

namespace SmartDongLib {
    /**
     * <p>通过Key找到对应的结点在邻接表的下标
     * @tparam KeyType
     * @tparam ElemType
     * @param k
     * @return
     */
    template<class KeyType, class ElemType>
    int Digraph<KeyType, ElemType>::findKeyOnIndex(KeyType k) {
       for (int i=0;i< nodes_.size();i++){
           if (nodes_[i].key() == k){
               return  i ;
           }
       }
       return  -1;
    }
    /**
     * <p> 给图插入新的结点
     * @tparam KeyType
     * @tparam ElemType
     * @param n
     * @return
     */
    template<class KeyType, class ElemType>
    Digraph<KeyType, ElemType> &Digraph<KeyType, ElemType>::addNode(GraphAdjacencyList<KeyType, ElemType> n) {
        if (findKeyOnIndex(n->key()) ==-1) {
            nodes_.push_back(n);
        }
        return *this;
    }
    /**
     * <p> 给图插入新的结点
     * @tparam KeyType
     * @tparam ElemType
     * @param k 结点键值
     * @param e 结点数据
     * @return
     */
    template<class KeyType, class ElemType>
    Digraph<KeyType, ElemType> &Digraph<KeyType, ElemType>::addNode(KeyType k, ElemType e) {
        if (findKeyOnIndex(k) ==-1){
            GraphAdjacencyList<KeyType, ElemType> n(k,e);
            nodes_.push_back(n);
        }
        return *this;
    }
    /**
     * <p>根据Key值删除图的结点
     * @tparam KeyType
     * @tparam ElemType
     * @param key
     * @return
     */
    template<class KeyType, class ElemType>
    Digraph<KeyType, ElemType> &Digraph<KeyType, ElemType>::deleteNodeByKey(KeyType key) {
        int keyIndex = findKeyOnIndex(key);
        if (keyIndex ==-1){
            return *this;
        }
        // 大于keyIndex 的结点下标都要减1
        for (int i = 0; i < nodes_.size(); ++i) {
            //每个结点删除对应的边
            nodes_.at(i).deleteEdge(keyIndex);
            boost::shared_ptr<LinkList<int>> edge=nodes_[i].edge();
            while (edge){
                //大于keyIndex 的结点下标都要减1
                if (edge->data > keyIndex){
                    edge->data = edge->data -1;
                }
                edge=edge->next;
            }
        }
        //刪除结点
        typename std::vector<GraphAdjacencyList<KeyType,ElemType>>::iterator iter=nodes_.begin();
        nodes_.erase(iter + keyIndex);
        return  * this;
    }
    /**
     * <p> 建立 源节点到目标结点的单向边
     * @tparam KeyType
     * @tparam ElemType
     * @param src 源节点
     * @param target 目标结点
     * @return
     */
    template<class KeyType, class ElemType>
    Digraph<KeyType, ElemType> &Digraph<KeyType, ElemType>::setEdge(KeyType src, KeyType target) {
        int srcIndex = findKeyOnIndex(src);
        int targetIndex = findKeyOnIndex(target);
        if (srcIndex == -1 || targetIndex == -1){
            //不存在所谓的结点
            return *this;
        }
        nodes_.at(srcIndex).insertEdge(targetIndex);
        return *this;
    }
    /**
     * <p>删除 src结点到target结点的单向边
     * @tparam KeyType
     * @tparam ElemType
     * @param src   出度结点
     * @param target  入度结点
     * @return
     */
    template<class KeyType, class ElemType>
    Digraph<KeyType, ElemType> &Digraph<KeyType, ElemType>::deleteEdge(KeyType src, KeyType target) {
        int srcIndex = findKeyOnIndex(src);
        int targetIndex = findKeyOnIndex(target);
        if (srcIndex == -1 || targetIndex == -1){
            return *this;
        }
        nodes_.at(srcIndex).deleteEdge(targetIndex);
        return *this;
    }


}