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
        bool  operator <(LowestCost& l1) const{ return  lowcost_>l1.lowcost_;}
    };

    class LowestPath{
    public:
        LowestPath(){lowcost_=SD_CONST::SD_MAXDOUBLE;hasVisit_= false;}
        explicit LowestPath(double lowcost): lowcost_(lowcost), hasVisit_(false){}

        LowestPath(std::vector<int> pathIndex, double lowcost, bool hasVisit= false);

        std::vector<int> pathIndex_;
        double lowcost_;
        bool hasVisit_;
        static int getMincost(std::vector<LowestPath> vec);

        bool  operator <(LowestPath& l1) const{ return  this->lowcost_<l1.lowcost_;}
        double operator +(double lowcosttemp) const{
            return lowcost_+lowcosttemp;
        }
    };
    typedef LowestPath LongestPath ;



    template<class KeyType,class ElemType >
    class Graph {
    public:
        explicit Graph(bool isUndirectedgraph= false): isUndirectedgraph_(isUndirectedgraph){}
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

        Graph miniSpanTreePrimOnIndex(int nodeIndex);
        Graph miniSpanTreePrimOnKey(KeyType nodeIndex);
        std::vector<LowestPath> shortPathOnIndex(int srcIndex,bool isInitAdjacencyMatrix= true);
        std::vector<LowestPath> shortPathOnKey(KeyType srcKey,bool isInitAdjacencyMatrix= true);
        const std::vector<GraphAdjacencyList<KeyType, ElemType>> &getNodes() const;
        LongestPath longPathOnIndex(int srcIndex,int target,bool isInitAdjacencyMatrix= true);
        const std::vector<std::vector<double>> &getAdjacencyMatrix() const;


    protected:
        double longPathOnIndex(int srcIndex,int target,std::vector<int>& hasVisitIndex,bool isInitAdjacencyMatrix= true);
    private:
        static int getMinCostnodeIndex(std::vector<LowestCost> &closedge);
        bool circuitJudge(int visitIndex,bool visit[],std::vector<int> & output, int (*Visit)(Graph& , int v));
        static int printKey(Graph& g, int i){
            std::cout<<g.nodes_[i].key();
            return 0;
        }
        static  bool isContain(const std::vector<int >& vec ,int i){
            bool isVisit= false;
            for (int j : vec) {
                if (j==i){
                    isVisit= true;
                    break;
                }
            }
            return isVisit;
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
