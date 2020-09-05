//
// Created by Administrator on 2020/9/1.
//


#include "tree/commontree.cpp"
#include <iostream>
using namespace  std;
using namespace SmartDongLib;
int main(){
    boost::shared_ptr<TreeNode<int,char>> root0(new TreeNode<int,char>(1,'A',3));
    boost::shared_ptr<TreeNode<int,char>> root1(new TreeNode<int,char>(3,'E',3));
    boost::shared_ptr<TreeNode<int,char>> root2(new TreeNode<int,char>(6,'G',3));

//    boost::shared_ptr<TreeNode<int,char>> rightchild;
//    root->initTree(2);
//    root->setChildPointer(0, leftChild);
//    root->setChildPointer(1, rightChild);
//    TreeNode<int,char> node1(2,'+');
    TreeNode<int,char> node2(2,'B',3);
    TreeNode<int,char> node4(4,'C',3);
    TreeNode<int,char> node5(5,'F',3);
    TreeNode<int,char> node7(7,'D',3);
    TreeNode<int,char> node8(8,'H',3);
    TreeNode<int,char> node9(9,'I',3);
    TreeNode<int,char> node10(10,'J',3);
    root0->setChild(0,node2);
    root0->setChild(1,node4);
    root0->setChild(2,node7);
    root1->setChild(0,node5);
    root2->setChild(0,node8);
    root2->setChild(1,node9)->setChild(0,node10);
    boost::shared_ptr<Forest<int,char>> forest(new Forest<int,char>());
    forest->insertTree(root0)->insertTree(root1)->insertTree(root2);
    forest->deleteTree(2);
    boost::shared_ptr<BinaryTree<int, char>> forest2BinartTree=CommonTree<int,char>::forest2BinartTree(forest);
    cout<<"------------postOrderTraversal------------------"<<endl;
    forest2BinartTree->postOrderTraversal();
    cout<<"------------preOrderTraversal------------------"<<endl;
    forest2BinartTree->preOrderTraversal();
    cout<<"------------inOrderTraversal------------------"<<endl;
    forest2BinartTree->inOrderTraversal();

}