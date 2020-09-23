//
// Created by Administrator on 2020/9/11.有向图
//

#ifndef SMARTDONGLIB_GRAPH_H
#define SMARTDONGLIB_GRAPH_H


#include <vector>
#include "graphadjacencylist.cpp"
#include <iostream>
#include <queue>
#include <const.h>
namespace SmartDongLib {
    class LowestCost{
    public:
        LowestCost(){lowcost_=SD_CONST::SD_MAXDOUBLE;}
        LowestCost(int nodeIndex, double lowcost) : nodeIndex_(nodeIndex), lowcost_(lowcost) {}
        int nodeIndex_;
        double lowcost_;
        bool  operator <(LowestCost& l1){ return  lowcost_>l1.lowcost_;}
    };
    class LowestPath{
    public:
        LowestPath(){lowcost_=SD_CONST::SD_MAXDOUBLE;hasVisit_= false;}
        LowestPath(double lowcost): lowcost_(lowcost), hasVisit_(false){}

        std::vector<int> pathIndex_;
        double lowcost_;
        bool hasVisit_;
        static int getMincost(std::vector<LowestPath> vec){
            int minIndex=-1;
            for (int i = 0; i <vec.size() ; ++i) {
                if (!(vec[i].hasVisit_)){
                    minIndex = i;
                    break;
                }
            }
            for (int i = 0; i <vec.size() ; ++i) {
                if (vec[i] < vec[minIndex] && !(vec[i].hasVisit_)){
                    minIndex = i;
                }
            }
            return minIndex;
        }
        bool  operator <(LowestPath& l1) const{ return  this->lowcost_<l1.lowcost_;}
        double operator +(double lowcosttemp) const{
            return lowcost_+lowcosttemp;
        }
    };
    template<class KeyType,class ElemType >
    class Graph {
    public:
        Graph(bool isUndirectedgraph= false): isUndirectedgraph_(isUndirectedgraph){}
        Graph& addNode(GraphAdjacencyList<KeyType,ElemType> n);
        Graph& addNode(KeyType, ElemType);
        Graph& deleteNodeByKey(KeyType key);
        Graph& setEdge(KeyType src, KeyType target,double weight = 1.0);
        Graph& setEdgeByIndex(int src, int target,double weight = 1.0);

        Graph& deleteEdge(KeyType src, KeyType target);
        std::vector<int> depthFirstSearch(KeyType visitIndex ,bool isSearchAllNode=false,int (*Visit)(Graph& g, int v)=printKey );
        std::vector<int> depthFirstSearch(bool isSearchAllNode=false,int visitIndex =0,int (*Visit)(Graph& g, int v)=printKey );
        int vexnum(){return nodes_.size();}
        int findKeyOnIndex(KeyType k);
        std::vector<int> breadthFirstSearch(bool isSearchAllNode=false,int visitIndex =0,int (*Visit)(Graph& g, int v)=printKey );
        std::vector<int> breadthFirstSearch(KeyType visitIndex ,bool isSearchAllNode=false,int (*Visit)(Graph& g, int v)=printKey );
        std::vector<int> connectedComponent(KeyType visitIndex);
        std::vector<int> simpleCircuitOnIndex(int visitIndex = 0, int (*Visit)(Graph& g, int v)= printKey);

        std::vector<int> simpleCircuitOnKey(KeyType visitIndex, int (*Visit)(Graph& g, int v)= printKey);
        void initialAdjacencyMatrix();

        //图的最小路径,图的最小生成树
        Graph miniSpanTreePrimOnIndex(int nodeIndex);
        Graph miniSpanTreePrimOnKey(KeyType nodeIndex);
        //最短路径和最长路径
        std::vector<LowestPath> shortPathOnIndex(int srcIndex,bool isInitAdjacencyMatrix= true);
        std::vector<LowestPath> shortPathOnKey(KeyType srcKey,bool isInitAdjacencyMatrix= true);
        const std::vector<GraphAdjacencyList<KeyType, ElemType>> &getNodes() const;

        const std::vector<std::vector<double>> &getAdjacencyMatrix() const;


    protected:

    private:
        static int getMinCostnodeIndex(std::vector<LowestCost> &closedge);
        bool circuitJudge(int visitIndex,bool visit[],std::vector<int> & output, int (*Visit)(Graph& , int v));
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
        /**
         * 邻接矩阵
         */
        std::vector<std::vector<double>> adjacencyMatrix_;
    };


}


#endif //SMARTDONGLIB_GRAPH_H
