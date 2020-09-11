//
// Created by Administrator on 2020/9/12.有向图的测试类
//


#include "graph/digraph.cpp"
#include <iostream>
using namespace SmartDongLib;
using namespace std;
int main() {
    Digraph<char,int> digraph;
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
    digraph.setEdge('A','L').setEdge('A','F').setEdge('A','C').setEdge('A','B');
    digraph.setEdge('B','M').setEdge('B','A');
    digraph.setEdge('C','A');
    digraph.setEdge('D','E');
    digraph.setEdge('E','D');
    digraph.setEdge('F','A');
    digraph.setEdge('G','K').setEdge('G','I').setEdge('G','H');
    digraph.setEdge('H','K').setEdge('H','G');
    digraph.setEdge('I','G');
    digraph.setEdge('J','M').setEdge('J','L');
    digraph.setEdge('K','H').setEdge('K','G');
    digraph.setEdge('L','M').setEdge('L','J').setEdge('L','A');
    digraph.setEdge('M','L').setEdge('M','J').setEdge('M','B');
    digraph.deleteNodeByKey('B');
    digraph.deleteEdge('M','L').deleteEdge('M','J').deleteEdge('M','B');

    cout<<"<<<<<finish>>>>>>>"<<endl;

}