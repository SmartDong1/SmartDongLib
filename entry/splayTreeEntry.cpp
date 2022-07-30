//
// Created by Administrator on 2021/1/9.
//
#include <iostream>
#include "tree/splayTree.cpp"
using namespace SmartDongLib;
using namespace std;
Size main() {
    boost::shared_ptr<SplayTree<Size,char>> root(new SplayTree<Size,char>(12,'-'));
    SplayTree<Size,char> node2(5,'+');
    SplayTree<Size,char> node3(18,'/');
    SplayTree<Size,char> node4(15,'a');
    SplayTree<Size,char> node5(19,'*');
    SplayTree<Size,char> node6(2,'e');
    SplayTree<Size,char> node7(9,'f');
    SplayTree<Size,char> node8(17,'b');
    SplayTree<Size,char> node9(16,'-');
    root->insertNode(node2)->insertNode(node3)->insertNode(node4)->insertNode(node5)
            ->insertNode(node6)->insertNode(node7)->insertNode(node8)->insertNode(node9)->getNodeByElem('/');
//    root->deleteNodeByKey(17);
    root = root->findroot();
    boost::shared_ptr<SplayTree<Size,char>> findKeyNode= root->getNodeByKey(16);
    root = root->findroot();
    findKeyNode=root->getNodeByKey(16);
    root = root->findroot();
    findKeyNode=root->deleteNodeByKey(16);
    findKeyNode=root->deleteNodeByElem('/');
    root = root->findroot();
    cout<<"------------postOrderTraversal------------------"<<endl;
    root->postOrderTraversal();
    cout<<"------------preOrderTraversal------------------"<<endl;
    root->preOrderTraversal();
    cout<<"------------inOrderTraversal------------------"<<endl;
    root->inOrderTraversal();
    cout<<"<<<<<finish>>>>>>>"<<endl;

}
