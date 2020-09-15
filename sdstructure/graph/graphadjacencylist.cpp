//
// Created by Administrator on 2020/9/11.
//

#include "graphadjacencylist.h"
namespace SmartDongLib {
    /**
     * <p>图结点的出度
     * @tparam KeyType
     * @tparam ElemType
     * @return
     */
    template<class KeyType, class ElemType>
    int GraphAdjacencyList<KeyType, ElemType>::outDegree() {
        return  linkListUtil_.listLenth(edge_);
    }
    /**
     * <p>删除边的代码值
     * @tparam KeyType
     * @tparam ElemType
     * @param edgeIndex 边 在邻接表的下标
     * @return
     */
    template<class KeyType, class ElemType>
    GraphAdjacencyList<KeyType, ElemType> &GraphAdjacencyList<KeyType, ElemType>::deleteEdge(int edgeIndex) {
        linkListUtil_.listDeleteByData(edge_, edgeIndex);
    }
    /**
     * <p>新增边的代码值
     * @tparam KeyType
     * @tparam ElemType
     * @param edgeIndex  边 在邻接表的下标
     * @return
     */
    template<class KeyType, class ElemType>
    GraphAdjacencyList<KeyType, ElemType>  &GraphAdjacencyList<KeyType, ElemType>::insertEdge(int edgeIndex,double weight ) {
        GraphAdjacencyEdge newedge(edgeIndex,weight);
        linkListUtil_.listAppend(edge_, newedge);
        return  *this;
    }
    /**
     * <p>是否已经关联了对应的边
     * @tparam KeyType
     * @tparam ElemType
     * @param edgeIndex
     * @return
     */
    template<class KeyType, class ElemType>
    bool GraphAdjacencyList<KeyType, ElemType>::isExistEdge(int edgeIndex) {
        int index=linkListUtil_.listGet(edge_,edgeIndex).nodeIndex_;
        return index != -1;
    }

    template<class KeyType, class ElemType>
    KeyType GraphAdjacencyList<KeyType, ElemType>::key() const {
        return key_;
    }

    template<class KeyType, class ElemType>
    GraphAdjacencyList<KeyType, ElemType>  & GraphAdjacencyList<KeyType, ElemType>::key(KeyType key) {
        key_ = key;
        return *this;
    }

    template<class KeyType, class ElemType>
    ElemType GraphAdjacencyList<KeyType, ElemType>::elem() const {
        return elem_;
    }

    template<class KeyType, class ElemType>
    GraphAdjacencyList<KeyType, ElemType>  & GraphAdjacencyList<KeyType, ElemType>::elem(ElemType elem) {
        elem_ = elem;
        return *this;
    }

    template<class KeyType, class ElemType>
    const boost::shared_ptr<LinkList<GraphAdjacencyEdge> > &GraphAdjacencyList<KeyType, ElemType>::edge() const {
        return edge_;
    }

    template<class KeyType, class ElemType>
    GraphAdjacencyList<KeyType, ElemType>  & GraphAdjacencyList<KeyType, ElemType>::edge(const boost::shared_ptr<LinkList<GraphAdjacencyEdge> > &edge) {
        edge_ = edge;
        return *this;
    }
}