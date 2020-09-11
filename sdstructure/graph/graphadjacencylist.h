//
// Created by Administrator on 2020/9/11.
//

#ifndef SMARTDONGLIB_GRAPHADJACENCYLIST_H
#define SMARTDONGLIB_GRAPHADJACENCYLIST_H

#include <sdstructure/linearlist/linkList.cpp>

namespace SmartDongLib {
    template<class KeyType,class ElemType >
    class GraphAdjacencyList {
    public:
        GraphAdjacencyList(){
            edge_=boost::shared_ptr<LinkList<int>>(new LinkList<int>());
        };
        GraphAdjacencyList(KeyType key, ElemType elem) : key_(key), elem_(elem) {
            edge_=boost::shared_ptr<LinkList<int>>(new LinkList<int>());
        }
        GraphAdjacencyList & insertEdge(int edgeIndex);
        GraphAdjacencyList & deleteEdge(int edgeIndex);
        bool  isExistEdge(int edgeIndex);
        int outDegree();

        KeyType key() const;
        GraphAdjacencyList & key(KeyType key);
        ElemType elem() const;
        GraphAdjacencyList & elem(ElemType elem);
        const boost::shared_ptr<LinkList<int>> &edge() const;
        GraphAdjacencyList & edge(const boost::shared_ptr<LinkList<int>> &edge);

    private:
        KeyType key_;
        ElemType elem_;
        boost::shared_ptr <LinkList<int>> edge_;
        LinkListUtil<int> linkListUtil_;
    };


}

#endif //SMARTDONGLIB_GRAPHADJACENCYLIST_H
