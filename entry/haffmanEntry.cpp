//
// Created by Administrator on 2020/9/2.
//


#include "tree/huffmantree.h"
#include "tree/commontree.cpp"
#include <iostream>
using namespace  std;
using namespace SmartDongLib;
Size main(){
    boost::shared_ptr<HuffmanTree<Size,char>> leaf0(new HuffmanTree<Size,char>(7,'A'));
    boost::shared_ptr<HuffmanTree<Size,char>> leaf1(new HuffmanTree<Size,char>(5,'B'));
    boost::shared_ptr<HuffmanTree<Size,char>> leaf2(new HuffmanTree<Size,char>(2,'C'));
    boost::shared_ptr<HuffmanTree<Size,char>> leaf3(new HuffmanTree<Size,char>(4,'D'));
    std::vector<boost::shared_ptr<HuffmanTree<Size,char>>> leaves_={leaf0,leaf1,leaf2,leaf3};
//    leaves_.push_back(leaf0);
//    leaves_.push_back(leaf1);
//    leaves_.push_back(leaf2);
//    leaves_.push_back(leaf3);
    boost::shared_ptr<HuffmanTree<Size,char>> root = CommonTree<Size,char>::leaves2HuffmanTree(leaves_);
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