//
// Created by hu on 2020/8/26.
//
#include "tree/binaryTree.cpp"
#include "tree/forest.h"
#include <iostream>
using namespace SmartDongLib;
using namespace std;
Size main() {
    boost::shared_ptr<BinaryTree<Size,char>> root(new BinaryTree<Size,char>(1,'-'));
    boost::shared_ptr<BinaryTree<Size,char>> leftchild=boost::shared_ptr<BinaryTree<Size,char>>(new BinaryTree<Size,char>(1,2));
//    boost::shared_ptr<BinaryTree<Size,char>> rightchild;
//    root->initTree(2);
//    root->setChildPoSizeer(0, leftChild);
//    root->setChildPoSizeer(1, rightChild);
//    BinaryTree<Size,char> node1(2,'+');
    BinaryTree<Size,char> node2(2,'+');
    BinaryTree<Size,char> node3(3,'/');
    BinaryTree<Size,char> node4(4,'a');
    BinaryTree<Size,char> node5(5,'*');
    BinaryTree<Size,char> node6(6,'e');
    BinaryTree<Size,char> node7(7,'f');
    BinaryTree<Size,char> node8(8,'b');
    BinaryTree<Size,char> node9(9,'-');
    BinaryTree<Size,char> node10(10,'c');
    BinaryTree<Size,char> node11(11,'d');
    root->leftChild(node2)->leftChild(node4)->parent()->rightChild(node5)->leftChild(node8)->parent()->rightChild(node9)->leftChild(node10)->parent()->rightChild(node11);
    root->rightChild(node3)->leftChild(node6)->parent()->rightChild(node7);
//    boost::shared_ptr<BinaryTree<Size,char>> nodeptr1=boost::shared_ptr<BinaryTree<Size,char>>(new BinaryTree<Size,char>(1,89));
//    root->leftChild(leftchild);
//    root->rightChild(nodeptr1);
//    cout<<root->leftChild()->leftChild(node1).elem()<<endl;
//    cout<<root->leftChild()->rightChild(node2).elem()<<endl;
//
//    cout<<root->getChild(1)->elem()<<endl;
//    cout << root->rightChild()->parent()->rightChild()->elem(3) << endl;
//    cout << root->leftChild()->parent()->getChild(0)->elem() << endl;
    cout << root->nodeCount() << endl;;
    cout << root->treeDeep() << endl;
    cout << root->getTreeType() << endl;
    root->deleteNodeByElem('*');
    cout<<"------------postOrderTraversal------------------"<<endl;
    root->postOrderTraversal();
    cout<<"------------preOrderTraversal------------------"<<endl;
    root->preOrderTraversal();
    cout<<"------------inOrderTraversal------------------"<<endl;
    root->inOrderTraversal();
    boost::shared_ptr<TreeNode<Size,char>> root_=boost::static_pointer_cast<TreeNode<Size,char>>(root);
    boost::shared_ptr<Forest<Size ,char >>forest(new Forest<Size ,char>());
    cout<<"------------Forest:postOrderTraversal------------------"<<endl;
    forest->insertTree(root_);
    forest->getTree(0)->postOrderTraversal();
    root->getAllnode();
    cout<<"<<<<<finish>>>>>>>"<<endl;

}