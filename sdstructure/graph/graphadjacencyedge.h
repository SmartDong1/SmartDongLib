//
// Created by Administrator on 2020/9/15.
//

#ifndef SMARTDONGLIB_GRAPHADJACENCYEDGE_H
#define SMARTDONGLIB_GRAPHADJACENCYEDGE_H

namespace SmartDongLib {

    class GraphAdjacencyEdge {
    public:
        GraphAdjacencyEdge(){ weight_ =1.0;};
        GraphAdjacencyEdge(int nodeIndex, double weight=1.0) : nodeIndex_(nodeIndex),
                                                           weight_(weight) {}
        bool operator ==(GraphAdjacencyEdge & ge){
            return nodeIndex_ == ge.nodeIndex_ ;
        }
        bool operator ==(int index){
            return nodeIndex_ == index;
        }
        int nodeIndex_;
        double  weight_;
    };
}

#endif //SMARTDONGLIB_GRAPHADJACENCYEDGE_H
