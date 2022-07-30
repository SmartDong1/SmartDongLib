//
// Created by Administrator on 2020/9/1.
//

#include "commontree.h"
#include <stack>
namespace SmartDongLib {
    /**
     * <p> 普通树转二叉树 :最左孩子为左子树，兄弟节点为最左节点的右子树，
     * @tparam KeyType
     * @tparam ElemType
     * @param treeRoot 普通树
     * @return  转化后的二叉树
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BinaryTree<KeyType, ElemType>>
    CommonTree<KeyType, ElemType>::treeNode2BinartTree(boost::shared_ptr<TreeNode<KeyType, ElemType>> treeRoot) {
        //左子树依然是左子树,兄弟节点为最左兄弟的右子树。
        KeyType key = treeRoot->key();
        ElemType elem = treeRoot->elem();
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> rootbinode(new BinaryTree<KeyType,ElemType> (key,elem));
        //访问根节点,访问第一个孩子建立左子树链接,根节点孩子依次入栈，入栈过程中建立右子树链接。
        //孩子全入栈后,然后弹出栈，出栈元素当作根节点。
        std:stack<boost::shared_ptr<TreeNode<KeyType, ElemType>>> sta;
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> binode =rootbinode;
        sta.push(treeRoot);
        while (treeRoot && !sta.empty() &&binode){
            treeRoot = sta.top();
            sta.pop();
            //如果没孩子 新结点回溯
            if (treeRoot->getChildnum()==0 || treeRoot->getChildEx(0) == NULL){
                binode = binode->parent();
            }
            //遍历节点的所有孩子,重新建立关联关系，孩子依次入栈
            for (Size i = 0; i < treeRoot->getChildnum(); ++i) {
                if(treeRoot->getChildEx(i) == NULL){
                    break;
                }
                boost::shared_ptr<TreeNode<KeyType, ElemType>> temptree= treeRoot->getChild(i);
                BinaryTree<KeyType,ElemType> newnode(temptree->key(),temptree->elem());
                if(i==0){
                    binode->leftChild(newnode);
                    binode = binode->leftChild();
                }else{
                    binode->rightChild(newnode);
                    binode = binode->rightChild();
                }
                sta.push(temptree);
            }

        }
        
        return rootbinode;
    }
    /**
     * <p>  森林转二叉树 :最左孩子为左子树，兄弟节点为最左节点的右子树，
     * @tparam KeyType
     * @tparam ElemType
     * @param forestRoot  森林
     * @return 新二叉树
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BinaryTree<KeyType, ElemType>>
    CommonTree<KeyType, ElemType>::forest2BinartTree(boost::shared_ptr<Forest<KeyType, ElemType>> forestRoot) {
        Size size = forestRoot-> getTreenum();
        if(size==0)
            return  NULL;
        std::vector<boost::shared_ptr<BinaryTree<KeyType, ElemType>>> roots;
        for (Size i = 0; i < size; ++i) {
            boost::shared_ptr<BinaryTree<KeyType, ElemType>> tempBiroot = treeNode2BinartTree(forestRoot->getTree(i));
            roots.push_back(tempBiroot);
        }
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> ret=roots.at(0);
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> retTemp=ret;
        for (Size j = 1; j < roots.size(); ++j) {
            retTemp->rightChild(roots.at(j));
            retTemp=retTemp->rightChild();
        }
        return ret;
    }
    /**
     * <p> 叶子节点集转哈夫曼树
     * @tparam KeyType
     * @tparam ElemType
     * @param leaves_ 叶子节点集合
     * @return 哈夫曼树
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<HuffmanTree<KeyType, ElemType>> CommonTree<KeyType, ElemType>::leaves2HuffmanTree(
            vector<boost::shared_ptr<HuffmanTree<KeyType, ElemType>>> leaves_) {
        if (leaves_.empty()) {
            return NULL;
        }
        std::vector <boost::shared_ptr<HuffmanTree<KeyType, ElemType>>> vecElem = leaves_;
        boost::shared_ptr <HuffmanTree<KeyType, ElemType>> minElem = vecElem.at(0);
        boost::shared_ptr <HuffmanTree<KeyType, ElemType>> secElem = minElem;
        while (vecElem.size() > 1) {
            Size minindex,secindex;
            findLeast(vecElem,minindex,secindex);
            minElem=vecElem.at(minindex);
            secElem=vecElem.at(secindex);
            boost::shared_ptr <HuffmanTree<KeyType, ElemType>> newNode(
                    new HuffmanTree<KeyType, ElemType>(secElem->key() + minElem->key(), -1));

            if (minindex<secindex){
                vecElem.erase(secindex+vecElem.begin());
                vecElem.erase(minindex+vecElem.begin());
            }
            else{
                vecElem.erase(minindex+vecElem.begin());
                vecElem.erase(secindex+vecElem.begin());
            }

            vecElem.push_back(newNode);
        }
        return vecElem.at(0);
    }
    /**
     * <p>找到最小key和此小key的节点，哈夫曼树构建私有
     * @tparam KeyType
     * @tparam ElemType
     * @param vec   叶子节点集
     * @param nIdx1 返回最小值的位置下标
     * @param nIdx2 返回次小值的位置下标
     */
    template<class KeyType, class ElemType>
    void
    CommonTree<KeyType, ElemType>::findLeast(vector<boost::shared_ptr<HuffmanTree<KeyType, ElemType>>> vec, Size &nIdx1,
                                             Size &nIdx2) {
        Size nSize = (Size)vec.size();
        boost::shared_ptr<HuffmanTree<KeyType, ElemType>> d1;
        boost::shared_ptr<HuffmanTree<KeyType, ElemType>> d2;
        for (Size i = 0; i < nSize; i++)
        {
            if ( d1 ==NULL ||vec[i]->key() < d1->key() )
            {
                nIdx1 = i;
                d1 = vec[i];
            }

            if ( (d2 ==NULL ||vec[i]->key() < d2->key() )&& vec[i]->key() > d1->key() )
            {
                nIdx2 = i;
                d2 = vec[i];
            }
        }

    }


}