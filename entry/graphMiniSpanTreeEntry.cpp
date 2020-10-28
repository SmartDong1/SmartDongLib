//
// Created by Administrator on 2020/9/19.
//

#include "graph/graph.cpp"
#include <iostream>
using namespace SmartDongLib;
using namespace std;
Size main() {
    Graph<char,Size> digraph(true);
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

    cout<<sizeof(Size) <<" "<<sizeof(char);

    Graph<char,Size> miniTree= digraph.miniSpanTreePrimOnIndex(0);
    miniTree.connectedComponent('A');
    Graph<char,Size> digraph2;
    digraph2.addNode('A',1)
            .addNode('B',1)
            .addNode('C',1)
            .addNode('D',1)
            .addNode('E',1)
            .addNode('F',1);
    digraph2.setEdge('A','C',10)
            .setEdge('A','E',30)
            .setEdge('A','F',100);
    digraph2.setEdge('B','C',5);
    digraph2.setEdge('C','D',50);
    digraph2.setEdge('D','F',10);
    digraph2.setEdge('E','D',20)
             .setEdge('E','F',60);
    digraph2.initialAdjacencyMatrix();
    std::vector<LowestPath> loestpath=digraph2.shortPathOnKey('A', false);
    cout<<"\n\n\n";
    for (auto & i : loestpath) {
        for (Size j : i.pathIndex_) {
            cout << j <<",";
        }
        cout <<"\t";
        cout<<i.lowcost_<<endl;

    }

    Graph<char,Size> digraph3(false);
    digraph3.addNode('1',1)
            .addNode('2',1)
            .addNode('3',1)
            .addNode('4',1)
            .addNode('5',1)
            .addNode('6',1)
            .addNode('7',1)
            .addNode('8',1)
            .addNode('9',1);
    digraph3.setEdge('1','4',5)
            .setEdge('1','2',6)
            .setEdge('1','3',4);
    digraph3.setEdge('2','5',1);
    digraph3.setEdge('3','5',1);
    digraph3.setEdge('4','6',2);
    digraph3.setEdge('5','7',9)
            .setEdge('5','8',7);
    digraph3.setEdge('6','8',4);
    digraph3.setEdge('7','9',2);
    digraph3.setEdge('8','9',4);

    cout<<"\n\n\n";
    LongestPath  maxValue = digraph2.longPathOnIndex(0,3, true);
    cout<<maxValue.lowcost_<<endl;
    for (Size k : maxValue.pathIndex_) {
        cout<<"V"<<k+1<<",";
    }
}