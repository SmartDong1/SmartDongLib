//
// Created by Administrator on 2020/9/2.
//


#include "tree/huffmantree.h"
#include "tree/commontree.cpp"
#include <iostream>
using namespace  std;
using namespace SmartDongLib;
int main(){
    boost::shared_ptr<HuffmanTree<int,char>> leaf0(new HuffmanTree<int,char>(7,'A'));
    boost::shared_ptr<HuffmanTree<int,char>> leaf1(new HuffmanTree<int,char>(5,'B'));
    boost::shared_ptr<HuffmanTree<int,char>> leaf2(new HuffmanTree<int,char>(2,'C'));
    boost::shared_ptr<HuffmanTree<int,char>> leaf3(new HuffmanTree<int,char>(4,'D'));
    std::vector<boost::shared_ptr<HuffmanTree<int,char>>> leaves_={leaf0,leaf1,leaf2,leaf3};
//    leaves_.push_back(leaf0);
//    leaves_.push_back(leaf1);
//    leaves_.push_back(leaf2);
//    leaves_.push_back(leaf3);
    boost::shared_ptr<HuffmanTree<int,char>> root = CommonTree<int,char>::leaves2HuffmanTree(leaves_);
    cout<<"------------postOrderTraversal------------------"<<endl;
    root->postOrderTraversal();
    cout<<"------------preOrderTraversal------------------"<<endl;
    root->preOrderTraversal();
    cout<<"------------inOrderTraversal------------------"<<endl;
    root->inOrderTraversal();
    cout<<"code:"<<endl;
    cout<<root->getHuffmanCodeByKey(leaf2->key())<<endl;
    cout<<root->getHuffmanCodeByElem(leaf2->elem())<<endl;

    cout<<"<<<<<<<<<<<<<finish>>>>>>>>>>>>>>"<<endl;
}