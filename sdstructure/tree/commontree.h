//
// Created by Administrator on 2020/9/1.
//

#ifndef SMARTDONGLIB_COMMONTREE_H
#define SMARTDONGLIB_COMMONTREE_H
#include "huffmantree.cpp"
#include "forest.h"
namespace SmartDongLib {
    template<class KeyType,class ElemType >
    class CommonTree {
    public:
        static boost::shared_ptr<BinaryTree<KeyType, ElemType>>   treeNode2BinartTree(boost::shared_ptr<TreeNode<KeyType,ElemType>> treeRoot);
        static boost::shared_ptr<BinaryTree<KeyType, ElemType>>   forest2BinartTree(boost::shared_ptr<Forest<KeyType,ElemType>> forestRoot);
        static boost::shared_ptr <HuffmanTree<KeyType, ElemType>>  leaves2HuffmanTree(
                std::vector<boost::shared_ptr<HuffmanTree<KeyType,ElemType>>> leaves_
                );

    private:
        static void findLeast( std::vector <boost::shared_ptr<HuffmanTree<KeyType, ElemType>>> vec,int& nidx1,int& nidx2);
    };


}

#endif //SMARTDONGLIB_COMMONTREE_H
