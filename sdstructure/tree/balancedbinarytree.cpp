//
// Created by Administrator on 2020/9/5.
//

#include "balancedbinarytree.h"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
namespace SmartDongLib {
    /**
     * <p> 利用二叉搜索树原理插入节点，对节点开始重新平衡
     * @tparam KeyType
     * @tparam ElemType
     * @param a
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> BalancedBinaryTree<KeyType, ElemType>::insertNode(BalancedBinaryTree &a) {
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> aa(new BalancedBinaryTree<KeyType, ElemType>(a));
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> ret =insertNode(aa);
        return ret;
    }
    /**
     * <p>利用二叉搜索树原理插入节点，对节点开始重新平衡
     * @tparam KeyType
     * @tparam ElemType
     * @param a
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>
    BalancedBinaryTree<KeyType, ElemType>::insertNode(boost::shared_ptr<BalancedBinaryTree> a) {
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> aa=BinarySearchTree<KeyType, ElemType>::insertNode(a);
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> ret =
                boost::static_pointer_cast<BalancedBinaryTree<KeyType, ElemType>>(aa);
        ret=ret->resetBalance(a->key());
        return ret;
    }
    /**
     * <p> 利用二叉树删除节点法删除节点
     * @tparam KeyType
     * @tparam ElemType
     * @param key
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>
    BalancedBinaryTree<KeyType, ElemType>::deleteNodeByKey(KeyType key) {
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> delnode=getNodeByKey(key);
        if (delnode == NULL){
            //未找到对应的节点,直接返回
            return  getThis();
        }
        return deleteNodeptr(delnode);
    }



    /**
     * <p>根据elem删除节点,TODO：未测
     * @tparam KeyType
     * @tparam ElemType
     * @param elem
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>
    BalancedBinaryTree<KeyType, ElemType>::deleteNodeByElem(ElemType elem)  {
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> delnode=getNodeByElem(elem);
        if (delnode == NULL){
            //未找到对应的节点,直接返回
            return  getThis();
        }
        return  deleteNodeptr(elem);
    }
    /**
     * <p>根据 Key值查询节点
     * @tparam KeyType
     * @tparam ElemType
     * @param key
     * @param mustleaf 是否要求是叶子节点
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>
    BalancedBinaryTree<KeyType, ElemType>::getNodeByKey(KeyType key, bool mustleaf) {
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> aa=BinarySearchTree<KeyType, ElemType>::getNodeByKey(key,mustleaf);
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> ret =
                boost::static_pointer_cast<BalancedBinaryTree<KeyType, ElemType>>(aa);
        return ret;
    }
    /**
     * <p> 根据elem查询节点,TODO：未测
     * @tparam KeyType
     * @tparam ElemType
     * @param elem
     * @param mustleaf 是否要求是叶子节点
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>
    BalancedBinaryTree<KeyType, ElemType>::getNodeByElem(ElemType elem, bool mustleaf) {
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> aa=BinarySearchTree<KeyType, ElemType>::getNodeByElem(elem,mustleaf);
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> ret =
                boost::static_pointer_cast<BalancedBinaryTree<KeyType, ElemType>>(aa);
        return ret;
    }
    /**
    * <p>返回所有树节点.
    * @tparam KeyType
    * @tparam ElemType
    * @return BinarySearchTree智能指针集合
    */
    template<class KeyType, class ElemType>
    vector<boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>> BalancedBinaryTree<KeyType, ElemType>::getAllnode() {
        vector<boost::shared_ptr<TreeNode<KeyType, ElemType>> >temp;
        TreeNode<KeyType, ElemType>::getAllTreeNode(temp);
        vector<boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>> ret;
        for (int i = 0; i < temp.size(); ++i) {
            boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> a = boost::static_pointer_cast<BalancedBinaryTree<KeyType, ElemType>>(temp.at(i));
            ret.push_back(a);
        }
        return ret;
    }

    /**
     * <p>左旋 ：右子作父，原父为左子，原子节点左子树变原父节点右子树
     * @tparam KeyType
     * @tparam ElemType
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>
    BalancedBinaryTree<KeyType, ElemType>::leftRotationTransform() {
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> orginRoot=getThis();
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> newRoot=orginRoot->rightChild();
        if (newRoot == NULL)
            return orginRoot;
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> parenttemp=orginRoot->parent();
        int findIndexOnParent = orginRoot->findIndexOnParent();
        if (findIndexOnParent ==0){
            orginRoot->parent()->leftChild(newRoot);
        } else if(findIndexOnParent ==1){
            orginRoot->parent()->rightChild(newRoot);
        }
        //原子节点左子树变原父节点右子树
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> leftchildtemp=newRoot->leftChild();
        orginRoot->rightChild(leftchildtemp);
        newRoot->parent(parenttemp);
        //原父为左子
        newRoot->leftChild(orginRoot);
        return newRoot;
    }
    /**
     * <p>右旋 ：左子作父，原父为右子，原子节点右子树变原父节点左子树
     * @tparam KeyType
     * @tparam ElemType
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>
    BalancedBinaryTree<KeyType, ElemType>::rightRotationTransform() {
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> orginRoot=getThis();
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> newRoot=orginRoot->leftChild();
        if (newRoot == NULL)
            return orginRoot;
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> parenttemp=orginRoot->parent();
        int findIndexOnParent = orginRoot->findIndexOnParent();
        if (findIndexOnParent ==0){
            orginRoot->parent()->leftChild(newRoot);
        } else if(findIndexOnParent ==1){
            orginRoot->parent()->rightChild(newRoot);
        }

        //原 子节点右子树变原父节点左子树
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> rightchildtemp=newRoot->rightChild();
        newRoot->parent(parenttemp);
        orginRoot->leftChild(rightchildtemp);
        //原父为右子
        newRoot->rightChild(orginRoot);
        return newRoot;
    }

    /**
     * <p>根据Key值重新平衡到根节点的所有节点
     * @tparam KeyType
     * @tparam ElemType
     * @param findKey
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> BalancedBinaryTree<KeyType, ElemType>::resetBalance(KeyType findKey) {
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> root=getThis();
        int childBalanceFactor;
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> lossBalanceChild =
                findLossBalanceChild(childBalanceFactor,findKey);
        if (lossBalanceChild ==NULL){
            //没有失配的节点
            return root;
        }
        int findIndexOnParent =lossBalanceChild->findIndexOnParent();
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> lossBalanceNode=lossBalanceChild->parent();
        if (findIndexOnParent ==0 && childBalanceFactor >=1){
            //左孩子的左孩子高了 ,用LL 转化
            lossBalanceNode->rightRotationTransform();
        }else if(findIndexOnParent ==0 && childBalanceFactor <=-1){
            //左孩子的右孩子高了 ,用LR 转化
            lossBalanceChild->leftRotationTransform();
            lossBalanceNode->rightRotationTransform();
        }else if(findIndexOnParent ==0 ){
            //删除时失衡了 ,用LR 转化
            lossBalanceChild->leftRotationTransform();
            lossBalanceNode->rightRotationTransform();
        }else if(findIndexOnParent ==1 && childBalanceFactor <=-1){
            //右孩子的右孩子高了 ,用RR 转化
            lossBalanceNode->leftRotationTransform();
        }else if(findIndexOnParent ==1 && childBalanceFactor >=1){
            //右孩子的左孩子高了 ,用RL 转化
            lossBalanceChild->rightRotationTransform();
            lossBalanceNode->leftRotationTransform();
        }else if(findIndexOnParent ==1 ){
            //删除时失衡了 ,用RL 转化
            lossBalanceChild->rightRotationTransform();
            lossBalanceNode->leftRotationTransform();
        }
        while (lossBalanceNode->parent()){
            lossBalanceNode= lossBalanceNode->parent();
        }
        return lossBalanceNode;
    }
    /**
   * <p>寻找最小失衡树的孩子节点
   * @tparam KeyType
   * @tparam ElemType
   * @param childBalanceFactor 失衡节点的孩子节点的位置(左孩子1    或   右孩子-1)
   * @return    失衡节点的孩子节点
   */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>
    BalancedBinaryTree<KeyType, ElemType>::findLossBalanceChild(int & childBalanceFactor, KeyType key) {
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> root=
                getNodeByKey(key);
        int leftDeep=0,rightDeep=0;
        childBalanceFactor=0;
        //往父节点的方向开始找为平衡的节点和他的孩子节点和失衡位置
        while (root){
            leftDeep=0,rightDeep=0;
            if (root->leftChild()){
                leftDeep=root->leftChild()->treeDeep();
            }
            if (root->rightChild()){
                rightDeep=root->rightChild()->treeDeep();
            }
            int rootbalanceFactor = leftDeep - rightDeep;
            if(rootbalanceFactor >= 2){
                return root->leftChild();
            }else if (rootbalanceFactor <= -2){
                return root->rightChild();
            }
            childBalanceFactor =rootbalanceFactor;
            root= root->parent();
        }
        return NULL;
    }




    /**
     * <p>根据Key删除节点,并且重新平衡节点
     * @tparam KeyType
     * @tparam ElemType
     * @param delnode
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> BalancedBinaryTree<KeyType, ElemType>::deleteNodeptr(
            boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> delnode) {
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> ret;
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> targetNode = delnode;
        int notnullChildIndex=-1; //最右孩子的位置
        if (delnode ->leftChild()!=NULL){
            targetNode = delnode ->leftChild();
            //左子树不空,拿左子树的最深右子树替代
            while (targetNode->rightChild() !=NULL){
                targetNode = targetNode->rightChild();
            }
            delnode->key(targetNode->key());
            delnode->elem(targetNode->elem());
            ret=targetNode->deleteNodeByKey(targetNode->key());
        }
        else if(delnode ->rightChild() !=NULL){
            targetNode = delnode ->rightChild();
            //右子树不空,拿右子树的最深左子树替代
            while (targetNode->leftChild() !=NULL){
                targetNode = targetNode->leftChild();
            }
            delnode->key(targetNode->key());
            delnode->elem(targetNode->elem());
            ret=targetNode->deleteNodeByKey(targetNode->key());
        }
        else{
            //叶子节点
            if(delnode->parent() == NULL){
                //如果删除唯一根节点
                return  NULL;
            }
            KeyType parentKey= delnode->parent()->key();

            int parentChildIndex=delnode->findIndexOnParent();
            if (parentChildIndex == 0){
                delnode->parent()->leftchild_=NULL;
            }else if(parentChildIndex == 1){
                delnode->parent()->rightchild_=NULL;
            }
            //**************************
            return delnode->parent()->resetBalance(parentKey);
            //*************************
        }

        return ret ;
    }

}
#pragma clang diagnostic pop