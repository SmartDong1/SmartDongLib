//
// Created by Administrator on 2020/9/7.
//

#include "redblacktree.h"
namespace SmartDongLib {


    /**
     * <p> 利用二叉搜索树原理插入节点，对节点开始重新平衡
     * @tparam KeyType
     * @tparam ElemType
     * @param a
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<RedBlackTree<KeyType, ElemType>> RedBlackTree<KeyType, ElemType>::insertNode(boost::shared_ptr<RedBlackTree> a) {
        a->colorTag_ = Red;
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> aa=BinarySearchTree<KeyType, ElemType>::insertNode(a);
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> ret =
                boost::static_pointer_cast<RedBlackTree<KeyType, ElemType>>(aa);
        ret=ret->resetBalance(a->key());
        return  ret;
    }

    /**
     * <p>祖宗根节点必黑，允许黑连黑，不允许红连红；新增红色，爸叔通红就变色，爸红叔黑就旋转，那黑往那旋
     * @tparam KeyType
     * @tparam ElemType
     * @param findKey
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<RedBlackTree<KeyType, ElemType>> RedBlackTree<KeyType, ElemType>::resetBalance(KeyType findKey) {
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> root=getThis();
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> lossBalanceNode =getNodeByKey(findKey);
        int indexOnParent= lossBalanceNode->findIndexOnParent();
        if (indexOnParent == -1){
            //根节点
            colorTag_ = Black;
            return root;
        }

        if (color(lossBalanceNode) == Red){
            boost::shared_ptr<RedBlackTree<KeyType, ElemType>> lossNodeParent =lossBalanceNode->parent();
            boost::shared_ptr<RedBlackTree<KeyType, ElemType>> lossNodeGrandParent =lossNodeParent->parent();
            boost::shared_ptr<RedBlackTree<KeyType, ElemType>> lossNodeUncle =lossNodeParent->brother();
            if (color(lossNodeParent) == Black){
                //如果插入的时候父节点是黑的,直接返回
                return  root;
            } else{
                //父节点是红的,那就要多余处理
                if (color(lossNodeUncle) == Red){
                    //cur为红，parent为红，pParent必为为黑，uncle存在且为红
                    //则将parent,uncle改为黑，pParent改为红，然后把pParent当成cur，继续向上调整。
                    lossNodeUncle->colorTag_ = Black;
                    lossNodeParent->colorTag_ = Black;
                    lossNodeGrandParent->colorTag_ = Red;
                    return resetBalance(lossNodeGrandParent->key());

                } else{
                    //父节点是红，叔叔是黑   黑在哪边往哪旋转

                    int indexOnGrandParent= lossNodeParent->findIndexOnParent();
                    if (indexOnGrandParent == 0 ){
                        //父亲是左孩子,那么叔叔就是右孩子
                        if (indexOnParent == 1) {
                            //如果cur为父亲的右孩子
                            lossNodeParent->leftRotationTransform();
                            return resetBalance(lossNodeParent->key());
                        }
                        lossNodeGrandParent->rightRotationTransform();
                    }else if(indexOnGrandParent == 1){
                        //父亲是右孩子,那么叔叔就是左孩子
                        if (indexOnParent == 0){
                            lossNodeParent->rightRotationTransform();
                            return resetBalance(lossNodeParent->key());
                        }
                        lossNodeGrandParent->leftRotationTransform();
                    }
                    lossNodeParent->colorTag_=Black;
                    lossNodeGrandParent->colorTag_=Red;

                }
            }

        }
        while (root->parent()){
            root= root->parent();
        }
        root->colorTag_ = Black;
        return root;
    }













    /**
     * <p>左旋 ：右子作父，原父为左子，原子节点左子树变原父节点右子树
     * @tparam KeyType
     * @tparam ElemType
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<RedBlackTree<KeyType, ElemType>>
    RedBlackTree<KeyType, ElemType>::leftRotationTransform() {
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> orginRoot=getThis();
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> newRoot=orginRoot->rightChild();
        if (newRoot == NULL)
            return orginRoot;
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> parenttemp=orginRoot->parent();
        int findIndexOnParent = orginRoot->findIndexOnParent();
        if (findIndexOnParent ==0){
            orginRoot->parent()->leftChild(newRoot);
        } else if(findIndexOnParent ==1){
            orginRoot->parent()->rightChild(newRoot);
        }
        //原子节点左子树变原父节点右子树
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> leftchildtemp=newRoot->leftChild();
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
    boost::shared_ptr<RedBlackTree<KeyType, ElemType>>
    RedBlackTree<KeyType, ElemType>::rightRotationTransform() {
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> orginRoot=getThis();
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> newRoot=orginRoot->leftChild();
        if (newRoot == NULL)
            return orginRoot;
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> parenttemp=orginRoot->parent();
        int findIndexOnParent = orginRoot->findIndexOnParent();
        if (findIndexOnParent ==0){
            orginRoot->parent()->leftChild(newRoot);
        } else if(findIndexOnParent ==1){
            orginRoot->parent()->rightChild(newRoot);
        }

        //原 子节点右子树变原父节点左子树
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> rightchildtemp=newRoot->rightChild();
        newRoot->parent(parenttemp);
        orginRoot->leftChild(rightchildtemp);
        //原父为右子
        newRoot->rightChild(orginRoot);
        return newRoot;
    }
    /**
    * <p> 根据elem查询节点,
    * @tparam KeyType
    * @tparam ElemType
    * @param elem
    * @param mustleaf 是否要求是叶子节点
    * @return
    */
    template<class KeyType, class ElemType>
    boost::shared_ptr<RedBlackTree<KeyType, ElemType>>
    RedBlackTree<KeyType, ElemType>::getNodeByElem(ElemType elem, bool mustleaf) {
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> aa=BinarySearchTree<KeyType, ElemType>::getNodeByElem(elem,mustleaf);
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> ret =
                boost::static_pointer_cast<RedBlackTree<KeyType, ElemType>>(aa);
        return ret;
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
    boost::shared_ptr<RedBlackTree<KeyType, ElemType>>
    RedBlackTree<KeyType, ElemType>::getNodeByKey(KeyType key, bool mustleaf) {
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> aa=BinarySearchTree<KeyType, ElemType>::getNodeByKey(key,mustleaf);
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> ret =
                boost::static_pointer_cast<RedBlackTree<KeyType, ElemType>>(aa);
        return ret;
    }
    /**
       * <p>返回所有树节点.
       * @tparam KeyType
       * @tparam ElemType
       * @return BinarySearchTree智能指针集合
       */
    template<class KeyType, class ElemType>
    vector<boost::shared_ptr<RedBlackTree<KeyType, ElemType>>> RedBlackTree<KeyType, ElemType>::getAllnode() {
        vector<boost::shared_ptr<TreeNode<KeyType, ElemType>> >temp;
        TreeNode<KeyType, ElemType>::getAllTreeNode(temp);
        vector<boost::shared_ptr<RedBlackTree<KeyType, ElemType>>> ret;
        for (int i = 0; i < temp.size(); ++i) {
            boost::shared_ptr<RedBlackTree<KeyType, ElemType>> a = boost::static_pointer_cast<RedBlackTree<KeyType, ElemType>>(temp.at(i));
            ret.push_back(a);
        }
        return ret;
    }
    /**
        * <p> 利用二叉搜索树原理插入节点，对节点开始重新平衡
        * @tparam KeyType
        * @tparam ElemType
        * @param a
        * @return
        */
    template<class KeyType, class ElemType>
    boost::shared_ptr<RedBlackTree<KeyType, ElemType>> RedBlackTree<KeyType, ElemType>::insertNode(RedBlackTree &a) {
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> aa(new RedBlackTree<KeyType, ElemType>(a));
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> ret =insertNode(aa);
        return ret;
    }


}