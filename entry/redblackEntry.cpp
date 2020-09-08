//
// Created by Administrator on 2020/9/8.
//


#include "tree/redblacktree.cpp"
#include <iostream>
using namespace SmartDongLib;
using namespace std;

void printData(boost::shared_ptr<TreeNode<int, char>> c) {
    boost::shared_ptr<RedBlackTree<int,char>> cc =boost::static_pointer_cast<RedBlackTree<int,char>>(c);
    std::cout<<cc->key() << "->" <<cc->getColor()<<"\n";
}
int main() {
    // 5 3 6 2 4 1
    boost::shared_ptr<RedBlackTree<int,char>> root(new RedBlackTree<int,char>(16,'-'));
    RedBlackTree<int,char> node2(2,'+');
    RedBlackTree<int,char> node3(3,'/');
    RedBlackTree<int,char> node4(4,'a');
    RedBlackTree<int,char> node1(1,'*');
    RedBlackTree<int,char> node6(6,'e');
    RedBlackTree<int,char> node16(16,'e');
    RedBlackTree<int,char> node7(7,'e');
    RedBlackTree<int,char> node11(11,'e');
    RedBlackTree<int,char> node9(9,'e');
    RedBlackTree<int,char> node26(26,'e');
    RedBlackTree<int,char> node18(18,'k');
    RedBlackTree<int,char> node27(27,'k');

//    root->insertNode(node3)->insertNode(node6)->insertNode(node2)->insertNode(node4);
//    root=root->insertNode(node1);
    root=root->insertNode(node3);
    root=root ->insertNode(node7);
    root=root->insertNode(node11);
    root=root->insertNode(node9);
    root=root->insertNode(node26);
    root=root->insertNode(node18);
    root=root->insertNode(node27);

//    root=root->deleteNodeByElem('k');
//    root=root->deleteNodeByKey(16);
//    root=root->deleteNodeByKey(26);

//    root=root->insertNode(node4);
    cout << root->nodeCount() << endl;;
    cout << root->treeDeep() << endl;
    cout << root->getTreeType() << endl;
    cout<<"------------postOrderTraversal------------------"<<endl;
    root->postOrderTraversal(printData);
    cout<<"------------preOrderTraversal------------------"<<endl;
    root->preOrderTraversal(printData);
    cout<<"------------inOrderTraversal------------------"<<endl;
    root->inOrderTraversal(printData);
    cout<<"<<<<<finish>>>>>>>"<<endl;

}