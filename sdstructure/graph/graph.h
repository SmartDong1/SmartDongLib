//
// Created by Administrator on 2020/9/11.有向图
//

#ifndef SMARTDONGLIB_GRAPH_H
#define SMARTDONGLIB_GRAPH_H


#include <vector>
#include "graphadjacencylist.cpp"
#include <iostream>
#include <queue>
namespace SmartDongLib {
    template<class KeyType,class ElemType >
    class Graph {
    public:
        Graph(bool isUndirectedgraph= false): isUndirectedgraph_(isUndirectedgraph){}
        Graph& addNode(GraphAdjacencyList<KeyType,ElemType> n);
        Graph& addNode(KeyType, ElemType);
        Graph& deleteNodeByKey(KeyType key);
        Graph& setEdge(KeyType src, KeyType target);
        Graph& deleteEdge(KeyType src, KeyType target);
        std::vector<int> depthFirstSearch(KeyType visitIndex ,bool isSearchAllNode=false,int (*Visit)(Graph& g, int v)=printKey );
        std::vector<int> depthFirstSearch(bool isSearchAllNode=false,int visitIndex =0,int (*Visit)(Graph& g, int v)=printKey );
        int vexnum(){return nodes_.size();}
        int findKeyOnIndex(KeyType k);
        std::vector<int> breadthFirstSearch(bool isSearchAllNode=false,int visitIndex =0,int (*Visit)(Graph& g, int v)=printKey );
        std::vector<int> breadthFirstSearch(KeyType visitIndex ,bool isSearchAllNode=false,int (*Visit)(Graph& g, int v)=printKey );

    protected:
    private:
        static int printKey(Graph& g, int i){
            std::cout<<g.nodes_[i].key();
            return 0;
        }
        void DFS(int visitIndex,bool visit[],std::vector<int> & output, int (*Visit)(Graph& , int v));
        std::vector<GraphAdjacencyList<KeyType,ElemType>> nodes_;
        /**
         * 是否是无向图
         */
        const bool isUndirectedgraph_;
    };


}


#endif //SMARTDONGLIB_GRAPH_H
