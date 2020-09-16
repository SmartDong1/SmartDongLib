//
// Created by Administrator on 2020/9/12.有向图的测试类
//


#include "graph/graph.cpp"
#include <iostream>
using namespace SmartDongLib;
using namespace std;
int main() {
    Graph<char,int> digraph;
    digraph.addNode('A',1)
           .addNode('B',1)
           .addNode('C',1)
           .addNode('D',1)
           .addNode('E',1)
           .addNode('F',1)
           .addNode('G',1)
           .addNode('H',1)
           .addNode('I',1)
           .addNode('J',1)
           .addNode('K',1)
           .addNode('L',1)
           .addNode('M',1);
    digraph.setEdge('A','L',2.0).setEdge('A','F',2.0).setEdge('A','C',2.0).setEdge('A','B',2.0);
    digraph.setEdge('B','M',2.0).setEdge('B','A',2.0);
    digraph.setEdge('C','A',2.0);
    digraph.setEdge('D','E',2.0);
    digraph.setEdge('E','D',2.0);
    digraph.setEdge('F','A',2.0);
    digraph.setEdge('G','K',2.0).setEdge('G','I',2.0).setEdge('G','H',2.0);
    digraph.setEdge('H','K',2.0).setEdge('H','G',2.0);
    digraph.setEdge('I','G',2.0);
    digraph.setEdge('J','M',2.0).setEdge('J','L',2.0);
    digraph.setEdge('K','H',2.0).setEdge('K','G',2.0);
    digraph.setEdge('L','M',2.0).setEdge('L','J',2.0).setEdge('L','A',2.0);
    digraph.setEdge('M','L',2.0).setEdge('M','J',2.0).setEdge('M','B',2.0);
//    digraph.deleteNodeByKey('B');
//    digraph.deleteEdge('M','L').deleteEdge('M','J').deleteEdge('M','B');
    vector<int> indexes =digraph.simpleCircuit('B');
    cout<<"\n";
    for (int indexe : indexes) {
        cout<<indexe<<endl;
    }

    cout<<"<<<<<finish>>>>>>>"<<endl;

}