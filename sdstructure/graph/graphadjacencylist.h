//
// Created by Administrator on 2020/9/11.
//

#ifndef SMARTDONGLIB_GRAPHADJACENCYLIST_H
#define SMARTDONGLIB_GRAPHADJACENCYLIST_H

#include <sdstructure/linearlist/linkList.cpp>
#include "graphadjacencyedge.h"
namespace SmartDongLib {
    template<class KeyType,class ElemType >
    class GraphAdjacencyList {
    public:
        GraphAdjacencyList(){
            edge_=boost::shared_ptr<LinkList<GraphAdjacencyEdge> >(new LinkList<GraphAdjacencyEdge> ());
        };
        GraphAdjacencyList(KeyType key, ElemType elem) : key_(key), elem_(elem) {
            edge_=boost::shared_ptr<LinkList<GraphAdjacencyEdge> >(new LinkList<GraphAdjacencyEdge> ());
        }
        GraphAdjacencyList & insertEdge(int edgeIndex,double weight = 1.0);
        GraphAdjacencyList & deleteEdge(int edgeIndex);
        bool  isExistEdge(int edgeIndex);
        int outDegree();

        KeyType key() const;
        GraphAdjacencyList & key(KeyType key);
        ElemType elem() const;
        GraphAdjacencyList & elem(ElemType elem);
        const boost::shared_ptr<LinkList<GraphAdjacencyEdge> > &edge() const;
        GraphAdjacencyList & edge(const boost::shared_ptr<LinkList<GraphAdjacencyEdge> > &edge);

    private:
        KeyType key_;
        ElemType elem_;
        boost::shared_ptr <LinkList<GraphAdjacencyEdge> > edge_;
        LinkListUtil<GraphAdjacencyEdge> linkListUtil_;
    };


}

#endif //SMARTDONGLIB_GRAPHADJACENCYLIST_H
