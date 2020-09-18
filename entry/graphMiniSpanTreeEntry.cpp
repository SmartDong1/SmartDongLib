//
// Created by Administrator on 2020/9/19.
//

#include "graph/graph.cpp"
#include <iostream>
using namespace SmartDongLib;
using namespace std;
int main() {
    Graph<char,int> digraph(true);
    digraph.addNode('A',1)
            .addNode('B',1)
            .addNode('C',1)
            .addNode('D',1)
            .addNode('E',1)
            .addNode('F',1);
    digraph.setEdge('A','B',6.0)
            .setEdge('A','C',1.0)
            .setEdge('A','D',5.0);
    digraph.setEdge('B','C',5.0)
            .setEdge('B','E',3.0);
    digraph.setEdge('C','D',5.0)
            .setEdge('C','E',6.0)
            .setEdge('C','F',4.0);
    digraph.setEdge('F','D',2.0)
            .setEdge('F','E',6.0);
    digraph.simpleCircuitOnKey('A');

    cout<<sizeof(int) <<" "<<sizeof(char);

    Graph<char,int> miniTree= digraph.miniSpanTreePrimOnIndex(0);
    miniTree.connectedComponent('A');
}