//
// Created by Administrator on 2020/9/4.
//

#include "tree/binarySearchTree.cpp"
#include <iostream>
using namespace SmartDongLib;
using namespace std;
int main() {
    boost::shared_ptr<BinarySearchTree<int,char>> root(new BinarySearchTree<int,char>(12,'-'));
    BinarySearchTree<int,char> node2(5,'+');
    BinarySearchTree<int,char> node3(18,'/');
    BinarySearchTree<int,char> node4(15,'a');
    BinarySearchTree<int,char> node5(19,'*');
    BinarySearchTree<int,char> node6(2,'e');
    BinarySearchTree<int,char> node7(9,'f');
    BinarySearchTree<int,char> node8(17,'b');
    BinarySearchTree<int,char> node9(16,'-');
    root->insertNode(node2)->insertNode(node3)->insertNode(node4)->insertNode(node5)
    ->insertNode(node6)->insertNode(node7)->insertNode(node8)->insertNode(node9)->getNodeByElem('/');
    root->deleteNodeByKey(17);
    cout<<"------------postOrderTraversal------------------"<<endl;
    root->postOrderTraversal();
    cout<<"------------preOrderTraversal------------------"<<endl;
    root->preOrderTraversal();
    cout<<"------------inOrderTraversal------------------"<<endl;
    root->inOrderTraversal();
    cout<<"<<<<<finish>>>>>>>"<<endl;

}