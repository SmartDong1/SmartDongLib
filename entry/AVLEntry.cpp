//
// Created by Administrator on 2020/9/5.
//


#include "tree/balancedbinarytree.cpp"
#include <iostream>
using namespace SmartDongLib;
using namespace std;
Size main() {
    // 5 3 6 2 4 1
    boost::shared_ptr<BalancedBinaryTree<Size,char>> root(new BalancedBinaryTree<Size,char>(16,'-'));
    BalancedBinaryTree<Size,char> node2(2,'+');
    BalancedBinaryTree<Size,char> node3(3,'/');
    BalancedBinaryTree<Size,char> node4(4,'a');
    BalancedBinaryTree<Size,char> node1(1,'*');
    BalancedBinaryTree<Size,char> node6(6,'e');
    BalancedBinaryTree<Size,char> node16(16,'e');
    BalancedBinaryTree<Size,char> node7(7,'e');
    BalancedBinaryTree<Size,char> node11(11,'e');
    BalancedBinaryTree<Size,char> node9(9,'e');
    BalancedBinaryTree<Size,char> node26(26,'e');
    BalancedBinaryTree<Size,char> node18(18,'k');
//    root->insertNode(node3)->insertNode(node6)->insertNode(node2)->insertNode(node4);
//    root=root->insertNode(node1);
    root=root->insertNode(node3)->insertNode(node7);
    root=root->insertNode(node11)->insertNode(node9);
    root=root->insertNode(node26);
    root=root->insertNode(node18);
    root=root->deleteNodeByElem('k');
    root=root->deleteNodeByKey(16);
    root=root->deleteNodeByKey(26);

//    root=root->insertNode(node4);
    cout << root->nodeCount() << endl;;
    cout << root->treeDeep() << endl;
    cout << root->getTreeType() << endl;
    cout<<"------------postOrderTraversal------------------"<<endl;
    root->postOrderTraversal();
    cout<<"------------preOrderTraversal------------------"<<endl;
    root->preOrderTraversal();
    cout<<"------------inOrderTraversal------------------"<<endl;
    root->inOrderTraversal();
    cout<<"<<<<<finish>>>>>>>"<<endl;

}