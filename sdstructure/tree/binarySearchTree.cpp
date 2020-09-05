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
        int childpos=-1;
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
  * @return BinaryTree智能指针集合
  */
    template<class KeyType, class ElemType>
    vector<boost::shared_ptr<BinarySearchTree<KeyType, ElemType>>> BinarySearchTree<KeyType, ElemType>::getAllnode() {
        vector<boost::shared_ptr<TreeNode<KeyType, ElemType>> >temp;
        TreeNode<KeyType, ElemType>::getAllTreeNode(temp);
        vector<boost::shared_ptr<BinarySearchTree<KeyType, ElemType>>> ret;
        for (int i = 0; i < temp.size(); ++i) {
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

    template<class KeyType, class ElemType>
    boost::shared_ptr<BinarySearchTree<KeyType, ElemType>>
    BinarySearchTree<KeyType, ElemType>::getBSTNodeByKey(KeyType key, bool mustleaf) {
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> temp=  getNodeByKey(key,mustleaf);
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> ret=boost::static_pointer_cast<BinarySearchTree<KeyType, ElemType>>>(temp);
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
    boost::shared_ptr<BinaryTree<KeyType, ElemType>>
    BinarySearchTree<KeyType, ElemType>::getNodeByKey(KeyType key, bool mustleaf) {
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> root =this->getThis() ;
        int childpos=-1;
        while (root !=NULL){
            if (root->key()== key){
                boost::shared_ptr<BinaryTree<KeyType, ElemType>> ret = boost::static_pointer_cast<BinaryTree<KeyType, ElemType>>(root);
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

}