//
// Created by Administrator on 2020/9/11.有向图
//

#ifndef SMARTDONGLIB_DIGRAPH_H
#define SMARTDONGLIB_DIGRAPH_H


#include <vector>
#include "graphadjacencylist.cpp"
namespace SmartDongLib {
    template<class KeyType,class ElemType >
    class Digraph {
    public:
        Digraph& addNode(GraphAdjacencyList<KeyType,ElemType> n);
        Digraph& addNode(KeyType,ElemType);
        Digraph& deleteNodeByKey(KeyType key);
        Digraph& setEdge(KeyType src,KeyType target);
        Digraph& deleteEdge(KeyType src,KeyType target);

    protected:
        int findKeyOnIndex(KeyType k);
    private:
        std::vector<GraphAdjacencyList<KeyType,ElemType>> nodes_;
    };


}


#endif //SMARTDONGLIB_DIGRAPH_H
