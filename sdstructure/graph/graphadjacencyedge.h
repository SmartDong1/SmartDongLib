//
// Created by Administrator on 2020/9/15.
//

#ifndef SMARTDONGLIB_GRAPHADJACENCYEDGE_H
#define SMARTDONGLIB_GRAPHADJACENCYEDGE_H

namespace SmartDongLib {

    class GraphAdjacencyEdge {
    public:
        GraphAdjacencyEdge(){ weight_ =1.0;};
        GraphAdjacencyEdge(Size nodeIndex, Real weight=1.0) : nodeIndex_(nodeIndex),
                                                           weight_(weight) {}
        bool operator ==(GraphAdjacencyEdge & ge){
            return nodeIndex_ == ge.nodeIndex_ ;
        }
        bool operator ==(Size index){
            return nodeIndex_ == index;
        }
        Size nodeIndex_;
        Real  weight_;
    };
}

#endif //SMARTDONGLIB_GRAPHADJACENCYEDGE_H
