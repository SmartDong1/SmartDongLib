//
// Created by Administrator on 2020/9/7.
//

#include "redblacktree.h"
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
        Size indexOnParent= lossBalanceNode->findIndexOnParent();
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

                    Size indexOnGrandParent= lossNodeParent->findIndexOnParent();
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
     * <p>删除节点调整规则
     * @tparam KeyType
     * @tparam ElemType
     * @param delnode 要删除的结点
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<RedBlackTree<KeyType, ElemType>>
    RedBlackTree<KeyType, ElemType>::resetDelBalance(boost::shared_ptr<RedBlackTree<KeyType,ElemType>> delnode) {
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> root=getThis();
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> lossBalanceNode =delnode;
        Size indexOnParent= lossBalanceNode->findIndexOnParent();
        if (indexOnParent == -1){
            //根节点
            colorTag_ = Black;
            return getThis();
        }

        if (color(lossBalanceNode) == Red){
            //如果删除的叶子是红色,直接删除,不需要调整
            return getThis();
        }
        if (color(lossBalanceNode) == Black){
            boost::shared_ptr<RedBlackTree<KeyType, ElemType>> lossNodeParent =lossBalanceNode->parent();
            boost::shared_ptr<RedBlackTree<KeyType, ElemType>> lossNodeBrother =lossBalanceNode->brother();
            //删除叶子节点是黑色，那么兄弟树的黑色节点就会比自身多一个黑节点
            //兄弟节点必然存在,要不然不可能兄弟子树比原子树多一个黑节点
            //如果兄弟节点是黑色的那么兄弟节点的孩子再无非NIL的黑色节点
            //如果兄弟节点是红色的那么兄弟两个孩子是黑色节点
            if (color(lossNodeBrother) == Black){
                if (indexOnParent == 0){
                    //被删节点在左子树
                    if (color(lossNodeBrother->rightChild()) == Red){
                        //兄弟是黑的,远侄子是红的
                        // 把兄弟结点染为双黑结点的父亲结点的颜色，把兄弟结点的右孩子染为黑色，再把父结点染为黑色；然后针对父结点进行一次左旋转
                        lossNodeBrother->colorTag_ = color(lossNodeParent);
                        lossNodeBrother->rightChild()->colorTag_=Black;
                        lossNodeParent->colorTag_ = Black;
                        lossNodeParent->leftRotationTransform();
                        return  getThis();
                    } else if(color(lossNodeBrother->leftChild()) == Red){
                        //兄弟是黑的,近侄子是红的
                        //针对双黑结点的兄弟做一次右旋转，结果使双黑结点的近侄子成为双黑结点新的兄弟；
                        //将新兄弟结点着为双黑结点的父结点的颜色，父结点着为黑色，再针对父做一次左旋转
                        lossNodeBrother->rightRotationTransform();
                        lossBalanceNode->brother()->colorTag_ = color(lossNodeParent);
                        lossNodeParent->colorTag_ = Black;
                        lossNodeParent->leftRotationTransform();
                        return  getThis();
                    } else{
                        //兄弟没有孩子
                        //直接给兄弟上红色
                        lossNodeBrother->colorTag_ = Red;
                        if (color(lossNodeParent) == Red){
                            //如果父节点原来是红色的,设置成黑色保证父树的黑色节点数量不变
                            lossNodeParent->colorTag_ = Black;
                            return getThis();
                        } else if(color(lossNodeParent) == Black){
                            //如果父节点原来是黑色的,那么父树比叔叔树少一个黑色节点，父节点重新调整
                           return resetDelBalance(lossNodeParent);
                        }
                    }
                } else if(indexOnParent == 1){
                    //被删节点在右子树
                    if (color(lossNodeBrother->leftChild()) == Red){
                        //兄弟是黑的,远侄子是红的
                        // 把兄弟结点染为双黑结点的父亲结点的颜色，把兄弟结点的右孩子染为黑色，再把父结点染为黑色；然后针对父结点进行一次左旋转
                        lossNodeBrother->colorTag_ = color(lossNodeParent);
                        lossNodeBrother->leftChild()->colorTag_=Black;
                        lossNodeParent->colorTag_ = Black;
                        lossNodeParent->rightRotationTransform();
                        return  getThis();
                    } else if(color(lossNodeBrother->rightChild()) == Red){
                        //兄弟是黑的,近侄子是红的
                        //针对双黑结点的兄弟做一次右旋转，结果使双黑结点的近侄子成为双黑结点新的兄弟；
                        //将新兄弟结点着为双黑结点的父结点的颜色，父结点着为黑色，再针对父做一次左旋转
                        lossNodeBrother->leftRotationTransform();
                        lossBalanceNode->brother()->colorTag_ = color(lossNodeParent);
                        lossNodeParent->colorTag_ = Black;
                        lossNodeParent->rightRotationTransform();
                        return  getThis();
                    } else{
                        //兄弟没有孩子
                        //直接给兄弟上红色
                        lossNodeBrother->colorTag_ = Red;
                        if (color(lossNodeParent) == Red){
                            //如果父节点原来是红色的,设置成黑色保证父树的黑色节点数量不变
                            lossNodeParent->colorTag_ = Black;
                            return getThis();
                        } else if(color(lossNodeParent) == Black){
                            //如果父节点原来是黑色的,那么父树比叔叔树少一个黑色节点，父节点重新调整
                          return  resetDelBalance(lossNodeParent);
                        }
                    }
                }// if indexParent


            }else if (color(lossNodeBrother) == Red){
                lossNodeBrother->colorTag_=Black;
                lossNodeParent ->colorTag_=Red;
                if (indexOnParent == 0){
                    //被删节点在左子树,兄弟在右子树
                    //父节点旋转
                    lossNodeParent->leftRotationTransform();
                }else if  (indexOnParent == 1){
                    //被删节点在右子树
                    lossNodeParent->rightRotationTransform();
                }
                return resetDelBalance(lossBalanceNode);
            }

        }
        return getThis();
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
        Size findIndexOnParent = orginRoot->findIndexOnParent();
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
        Size findIndexOnParent = orginRoot->findIndexOnParent();
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
        for (Size i = 0; i < temp.size(); ++i) {
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
    /**
     * <p>删除节点,采用二叉搜索树删除原理,递归赋值前继节点,对叶子节点实行删除调整
     * @tparam KeyType
     * @tparam ElemType
     * @param delnode
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<RedBlackTree<KeyType, ElemType>>
    RedBlackTree<KeyType, ElemType>::deleteNodeptr(boost::shared_ptr<RedBlackTree<KeyType, ElemType>> delnode) {
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> ret = getThis();
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> targetNode = delnode;
        Size notnullChildIndex=-1; //最右孩子的位置
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
            boost::shared_ptr<RedBlackTree<KeyType, ElemType>> delparent = delnode->parent();
            boost::shared_ptr<RedBlackTree<KeyType, ElemType>> delbrother = delnode->brother();
            resetDelBalance(delnode);
            while (ret->parent()){
                ret= ret->parent();
            }
            Size parentChildIndex=delnode->findIndexOnParent();
            if (parentChildIndex == 0){
                delnode->parent()->leftchild_=NULL;
            }else if(parentChildIndex == 1){
                delnode->parent()->rightchild_=NULL;
            }
            //**************************
            {
//                //如果删除的叶子是红色,直接删除,如果删除的叶子是黑色，要从兄弟树中通过旋转少一个黑节点,或者自身树多一个黑节点
//                if (color(delnode) == Red) {
//                    return ROOT;
//                } else if (color(delnode) == Black) {
//                    //删除叶子节点是黑色，那么兄弟子树的黑色节点就会比自身多一个黑节点
//                    //兄弟节点必然存在,要不然不可能兄弟子树比原子树多一个黑节点
//                    //如果兄弟节点是黑色的那么兄弟节点的孩子再无非NIL的黑色节点
//                    //如果兄弟节点是红色的那么兄弟节点的孩子还有一个非NIL的黑色节点,且父亲比定是黑色的
//                    if (color(delbrother) == Black){
//                        //如果兄弟节点是黑色
//                        if (color(delparent) == Red){
//                            //如果父亲为红,兄弟必定是黑的,交换一下颜色就可以再不减少兄弟黑节点的情况下,给本身子树增加一个黑节点
//                            delparent->colorTag_ = Black;
//                            delbrother->colorTag_ = Red;
//                            if (delbrother->isLeaf()){
//                                return ROOT;
//                            }
//                            //处理红色兄弟和红色兄弟孩子
//
//                        } else if(color(delparent) == Black){
//                            //父亲是黑的兄弟是黑的，那么兄弟节点的孩子再无非NIL的黑色节点
//                            //再处理兄弟和兄弟孩子的红色冲突
//                            delbrother->colorTag_ = Red;
//                        }
//                    } else if (color(delbrother) == Red){
//                        //如果兄弟节点是红色的那么兄弟节点的孩子必定会有两个黑色的孩子,且父亲比定是黑色的
//                        //如果把兄弟从红色变成黑色,那么兄弟树就会比自身的子树多出两个黑节点
//                        delbrother->colorTag_ = Black;
//                        //直接旋转即可
//                    }


                    //如果兄弟节点是红色,那么父节点必然是黑色,通过旋转让父节点变到原有子树,兄弟的其中一个黑孩子被贡献到了

//                }
            }
            //*************************
        }

        return ret ;
    }
    /**
        * <p>根据Key删除节点,最先匹配原理是先序遍历,二叉搜索树删除方法,利用左子树的最右叶子，或者右子树的最左叶子替代。
        * @tparam KeyType
        * @tparam ElemType
        * @param key
        * @return
        */
    template<class KeyType, class ElemType>
    boost::shared_ptr<RedBlackTree<KeyType, ElemType>> RedBlackTree<KeyType, ElemType>::deleteNodeByKey(KeyType key) {
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> delnode=getNodeByKey(key);
        if (delnode == NULL){
            //未找到对应的节点,直接返回
            return  getThis();
        }
        return deleteNodeptr(delnode);
    }
    /**
     * <p>根据Elem删除节点,最先匹配原理是先序遍历,二叉搜索树删除方法,利用左子树的最右叶子，或者右子树的最左叶子替代。
     * @tparam KeyType
     * @tparam ElemType
     * @param elem
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<RedBlackTree<KeyType, ElemType>>
    RedBlackTree<KeyType, ElemType>::deleteNodeByElem(ElemType elem) {
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> delnode=getNodeByElem(elem);
        if (delnode == NULL){
            //未找到对应的节点,直接返回
            return  getThis();
        }
        return  deleteNodeptr(delnode);
    }


}
#pragma clang diagnostic pop