//
// Created by Administrator on 2020/9/4.
//

#include "binarySearchTree.h"
namespace SmartDongLib {
    template<class KeyType, class ElemType>
    boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> BinarySearchTree<KeyType, ElemType>::insertNode(BinarySearchTree & a) {
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> aa(new BinarySearchTree<KeyType, ElemType>(a));
        return this->insertNode(aa);
    }
    template<class KeyType, class ElemType>
    boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> BinarySearchTree<KeyType, ElemType>::insertNode( boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> node) {
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> root = boost::dynamic_pointer_cast<BinarySearchTree<KeyType,ElemType>>(this->getThis());
        Size childpos=-1;
        while (root !=NULL){
            if (node->key() <= root->key() ){
                //小的往左子樹走,
                if (root->leftChild() != NULL){
                    root = root->leftChild();
                }else {
                    childpos = 0;
                    break;
                }
            }else{
                //大的往右子樹走
                if (root->rightChild() != NULL){
                    root = root->rightChild();
                }else {
                    childpos = 1;
                    break;
                }
            }
        }
        if (childpos ==0){
            root ->leftChild(node);
        } else if(childpos == 1){
            root ->rightChild(node);
        }
        return this->getThis();
    }

    /**
  * <p>返回所有树节点.
  * @tparam KeyType
  * @tparam ElemType
  * @return BinarySearchTree智能指针集合
  */
    template<class KeyType, class ElemType>
    vector<boost::shared_ptr<BinarySearchTree<KeyType, ElemType>>> BinarySearchTree<KeyType, ElemType>::getAllnode() {
        vector<boost::shared_ptr<TreeNode<KeyType, ElemType>> >temp;
        TreeNode<KeyType, ElemType>::getAllTreeNode(temp);
        vector<boost::shared_ptr<BinarySearchTree<KeyType, ElemType>>> ret;
        for (Size i = 0; i < temp.size(); ++i) {
            boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> a = boost::static_pointer_cast<BinarySearchTree<KeyType, ElemType>>(temp.at(i));
            ret.push_back(a);
        }
        return ret;
    }

    template<class KeyType, class ElemType>
    boost::shared_ptr<BinarySearchTree<KeyType, ElemType>>
    BinarySearchTree<KeyType, ElemType>::getNodeByElem(ElemType elem, bool mustleaf) {
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> ret = boost::static_pointer_cast<BinarySearchTree<KeyType, ElemType>>
                (TreeNode<KeyType, ElemType>::getNodeByElem(elem, mustleaf) );
        return ret;
    }

    /**
     * <p>用于覆盖,二叉排序树专有查询.
     * @tparam KeyType
     * @tparam ElemType
     * @param key
     * @param mustleaf
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BinarySearchTree<KeyType, ElemType>>
    BinarySearchTree<KeyType, ElemType>::getNodeByKey(KeyType key, bool mustleaf) {
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> root =this->getThis() ;
        Size childpos=-1;
        while (root !=NULL){
            if (root->key()== key){
                boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> ret = boost::static_pointer_cast<BinarySearchTree<KeyType, ElemType>>(root);
                return ret;
            }
            if (key <= root->key() ){
                //小的往左子樹走,
                if (root->leftChild() != NULL){
                    root = root->leftChild();
                }else {
                    return NULL;
                }
            }else{
                //大的往右子樹走
                if (root->rightChild() != NULL){
                    root = root->rightChild();
                }else {
                    return NULL;
                }
            } //if ..elseif
        }//while
        return NULL;
    }



    /**
    * <p>根据Key删除节点,最先匹配原理是先序遍历,二叉搜索树删除方法,利用左子树的最右叶子，或者右子树的最左叶子替代。
    * @tparam KeyType
    * @tparam ElemType
    * @param key
    * @return
    */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> BinarySearchTree<KeyType, ElemType>::deleteNodeByKey(KeyType key) {
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> delnode=getNodeByKey(key);
        if (delnode == NULL){
            //未找到对应的节点,直接返回
            return  getThis();
        }
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> targetNode = delnode;
        Size notnullChildIndex=-1; //最右孩子的位置
        if (delnode ->leftChild()!=NULL){
            targetNode = delnode ->leftChild();
            //左子树不空,拿左子树的最深右子树替代
            while (targetNode->rightChild() !=NULL){
                targetNode = targetNode->rightChild();
            }
            delnode->key(targetNode->key());
            delnode->elem(targetNode->elem());
            targetNode->deleteNodeByKey(targetNode->key());
        }
        else if(delnode ->rightChild() !=NULL){
            targetNode = delnode ->rightChild();
            //右子树不空,拿右子树的最深左子树替代
            while (targetNode->leftChild() !=NULL){
                targetNode = targetNode->leftChild();
            }
            delnode->key(targetNode->key());
            delnode->elem(targetNode->elem());
            targetNode->deleteNodeByKey(targetNode->key());
        }
        else{
            //叶子节点
            if(delnode->parent() == NULL){
                //如果删除唯一根节点
                return  NULL;
            }
            Size parentChildIndex=delnode->findIndexOnParent();
            if (parentChildIndex == 0){
                delnode->parent()->leftchild_=NULL;
            }else if(parentChildIndex == 1){
                delnode->parent()->rightchild_=NULL;
            }

        }

        return getThis();
    }
    /**
   * <p>根据elem删除节点,最先匹配原理是先序遍历,二叉搜索树删除方法,利用左子树的最右叶子，或者右子树的最左叶子替代。
   * @tparam KeyType
   * @tparam ElemType
   * @param elem
   * @return
   */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> BinarySearchTree<KeyType, ElemType>::deleteNodeByElem(ElemType elem) {
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> delnode=getNodeByElem(elem);
        if (delnode == NULL){
            //未找到对应的节点,直接返回
            return  getThis();
        }
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> targetNode = delnode;
        Size notnullChildIndex=-1; //最右孩子的位置
        if (delnode ->leftChild()!=NULL){
            targetNode = delnode ->leftChild();
            //左子树不空,拿左子树的最深右子树替代
            while (targetNode->rightChild() !=NULL){
                targetNode = targetNode->rightChild();
            }
            delnode->key(targetNode->key());
            delnode->elem(targetNode->elem());
            targetNode->deleteNodeByKey(targetNode->key());
        }
        else if(delnode ->rightChild() !=NULL){
            targetNode = delnode ->rightChild();
            //右子树不空,拿右子树的最深左子树替代
            while (targetNode->leftChild() !=NULL){
                targetNode = targetNode->leftChild();
            }
            delnode->key(targetNode->key());
            delnode->elem(targetNode->elem());
            targetNode->deleteNodeByKey(targetNode->key());
        }
        else{
            //叶子节点
            if(delnode->parent() == NULL){
                //如果删除唯一根节点
                return  NULL;
            }
            Size parentChildIndex=delnode->findIndexOnParent();
            if (parentChildIndex == 0){
                delnode->parent()->leftchild_=NULL;
            }else if(parentChildIndex == 1){
                delnode->parent()->rightchild_=NULL;
            }

        }

        return getThis();
    }

}