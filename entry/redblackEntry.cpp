//
// Created by Administrator on 2020/9/8.红黑树测试
//


#include "tree/redblacktree.cpp"
#include <iostream>
using namespace SmartDongLib;
using namespace std;

void prSizeData(boost::shared_ptr<TreeNode<Size, char>> c) {
    boost::shared_ptr<RedBlackTree<Size,char>> cc =boost::static_pointer_cast<RedBlackTree<Size,char>>(c);
    std::cout<<cc->key() << "->" <<cc->getColor()<<"\n";
}
Size main() {
    // 5 3 6 2 4 1
    boost::shared_ptr<RedBlackTree<Size,char>> root(new RedBlackTree<Size,char>(16,'-'));
    RedBlackTree<Size,char> node2(2,'+');
    RedBlackTree<Size,char> node3(3,'/');
    RedBlackTree<Size,char> node4(4,'a');
    RedBlackTree<Size,char> node1(1,'*');
    RedBlackTree<Size,char> node6(6,'e');
    RedBlackTree<Size,char> node16(16,'e');
    RedBlackTree<Size,char> node7(7,'e');
    RedBlackTree<Size,char> node11(11,'e');
    RedBlackTree<Size,char> node9(9,'e');
    RedBlackTree<Size,char> node26(26,'e');
    RedBlackTree<Size,char> node18(18,'k');
    RedBlackTree<Size,char> node27(27,'k');

//    root->insertNode(node3)->insertNode(node6)->insertNode(node2)->insertNode(node4);
//    root=root->insertNode(node1);
    root=root->insertNode(node3);
    root=root ->insertNode(node7);
    root=root->insertNode(node11);
    root=root->insertNode(node9);
    root=root->insertNode(node26);
    root=root->insertNode(node18);
    root=root->insertNode(node27);

//    root=root->deleteNodeByElem('e');
//    root=root->deleteNodeByKey(16);
    root=root->deleteNodeByKey(3);
    root=root->deleteNodeByKey(9);
    root=root->deleteNodeByKey(7);
    root=root->deleteNodeByKey(16);
    root=root->deleteNodeByKey(11);

//    root=root->insertNode(node4);
    cout << root->nodeCount() << endl;;
    cout << root->treeDeep() << endl;
    cout << root->getTreeType() << endl;
    cout<<"------------postOrderTraversal------------------"<<endl;
    root->postOrderTraversal(prSizeData);
    cout<<"------------preOrderTraversal------------------"<<endl;
    root->preOrderTraversal(prSizeData);
    cout<<"------------inOrderTraversal------------------"<<endl;
    root->inOrderTraversal(prSizeData);
    cout<<"<<<<<finish>>>>>>>"<<endl;

}