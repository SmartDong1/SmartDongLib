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
        LowestCost(Size nodeIndex, Real lowcost) : nodeIndex_(nodeIndex), lowcost_(lowcost) {}
        Size nodeIndex_;
        Real lowcost_;
        bool  operator <(LowestCost& l1) const{ return  lowcost_>l1.lowcost_;}
    };

    class LowestPath{
    public:
        LowestPath(){lowcost_=SD_CONST::SD_MAXDOUBLE;hasVisit_= false;}
        explicit LowestPath(Real lowcost): lowcost_(lowcost), hasVisit_(false){}

        LowestPath(std::vector<Size> pathIndex, Real lowcost, bool hasVisit= false);

        std::vector<Size> pathIndex_;
        Real lowcost_;
        bool hasVisit_;
        static Size getMincost(std::vector<LowestPath> vec);

        bool  operator <(LowestPath& l1) const{ return  this->lowcost_<l1.lowcost_;}
        Real operator +(Real lowcosttemp) const{
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
        Graph& setEdge(KeyType src, KeyType target,Real weight = 1.0);
        Graph& setEdgeByIndex(Size src, Size target,Real weight = 1.0);

        Graph& deleteEdge(KeyType src, KeyType target);
        std::vector<Size> depthFirstSearch(KeyType visitIndex ,bool isSearchAllNode=false,Size (*Visit)(Graph& g, Size v)=prSizeKey );
        std::vector<Size> depthFirstSearch(bool isSearchAllNode=false,Size visitIndex =0,Size (*Visit)(Graph& g, Size v)=prSizeKey );
        Size vexnum(){return nodes_.size();}
        Size findKeyOnIndex(KeyType k);
        std::vector<Size> breadthFirstSearch(bool isSearchAllNode=false,Size visitIndex =0,Size (*Visit)(Graph& g, Size v)=prSizeKey );
        std::vector<Size> breadthFirstSearch(KeyType visitIndex ,bool isSearchAllNode=false,Size (*Visit)(Graph& g, Size v)=prSizeKey );
        std::vector<Size> connectedComponent(KeyType visitIndex);
        std::vector<Size> simpleCircuitOnIndex(Size visitIndex = 0, Size (*Visit)(Graph& g, Size v)= prSizeKey);

        std::vector<Size> simpleCircuitOnKey(KeyType visitIndex, Size (*Visit)(Graph& g, Size v)= prSizeKey);
        void initialAdjacencyMatrix();

        Graph miniSpanTreePrimOnIndex(Size nodeIndex);
        Graph miniSpanTreePrimOnKey(KeyType nodeIndex);
        std::vector<LowestPath> shortPathOnIndex(Size srcIndex,bool isInitAdjacencyMatrix= true);
        std::vector<LowestPath> shortPathOnKey(KeyType srcKey,bool isInitAdjacencyMatrix= true);
        const std::vector<GraphAdjacencyList<KeyType, ElemType>> &getNodes() const;
        LongestPath longPathOnIndex(Size srcIndex,Size target,bool isInitAdjacencyMatrix= true);
        const std::vector<std::vector<Real>> &getAdjacencyMatrix() const;


    protected:
        Real longPathOnIndex(Size srcIndex,Size target,std::vector<Size>& hasVisitIndex,bool isInitAdjacencyMatrix= true);
    private:
        static Size getMinCostnodeIndex(std::vector<LowestCost> &closedge);
        bool circuitJudge(Size visitIndex,bool visit[],std::vector<Size> & output, Size (*Visit)(Graph& , Size v));
        static Size prSizeKey(Graph& g, Size i){
            std::cout<<g.nodes_[i].key();
            return 0;
        }
        static  bool isContain(const std::vector<Size >& vec ,Size i){
            bool isVisit= false;
            for (Size j : vec) {
                if (j==i){
                    isVisit= true;
                    break;
                }
            }
            return isVisit;
        }
        void DFS(Size visitIndex,bool visit[],std::vector<Size> & output, Size (*Visit)(Graph& , Size v));
        std::vector<GraphAdjacencyList<KeyType,ElemType>> nodes_;
        /**
         * 是否是无向图
         */
        const bool isUndirectedgraph_;
        /**
         * 邻接矩阵
         */
        std::vector<std::vector<Real>> adjacencyMatrix_;
    };


}


#endif //SMARTDONGLIB_GRAPH_H
