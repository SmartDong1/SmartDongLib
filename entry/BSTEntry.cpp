//
// Created by Administrator on 2020/9/4.
//

#include "tree/binarySearchTree.cpp"
#include <iostream>
using namespace SmartDongLib;
using namespace std;
Size main() {
    boost::shared_ptr<BinarySearchTree<Size,char>> root(new BinarySearchTree<Size,char>(12,'-'));
    BinarySearchTree<Size,char> node2(5,'+');
    BinarySearchTree<Size,char> node3(18,'/');
    BinarySearchTree<Size,char> node4(15,'a');
    BinarySearchTree<Size,char> node5(19,'*');
    BinarySearchTree<Size,char> node6(2,'e');
    BinarySearchTree<Size,char> node7(9,'f');
    BinarySearchTree<Size,char> node8(17,'b');
    BinarySearchTree<Size,char> node9(16,'-');
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