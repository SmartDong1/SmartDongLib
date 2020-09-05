//
// Created by Administrator on 2020/9/5.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#ifndef SMARTDONGLIB_BALANCEDBINARYTREE_H
#define SMARTDONGLIB_BALANCEDBINARYTREE_H
#include "binarySearchTree.cpp"
namespace SmartDongLib {
    template<class KeyType,class ElemType >
    class BalancedBinaryTree: public BinarySearchTree<KeyType,ElemType> {
    public:
        BalancedBinaryTree(): BinarySearchTree<KeyType,ElemType>(){}
        BalancedBinaryTree(KeyType key,ElemType e ):
                BinarySearchTree<KeyType,ElemType>(key,e){}
        BalancedBinaryTree(const BalancedBinaryTree &t): BinarySearchTree<KeyType,ElemType>(t.key(),t.elem()){/*复制构造只复制key和elem,其他用自身初始化*/}
        boost::shared_ptr<BalancedBinaryTree> parent()  {
            if (!TreeNode<KeyType, ElemType>::parent() )
                return NULL;
            boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BalancedBinaryTree<KeyType,ElemType>>(TreeNode<KeyType, ElemType>::parent());
            return aa;
        }
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>& parent(boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>& p){

            boost::shared_ptr<TreeNode<KeyType,ElemType>> aa = boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(p);
            TreeNode<KeyType, ElemType>::parent(aa);
            return p;
        }
        boost::shared_ptr<BalancedBinaryTree> insertNode(BalancedBinaryTree & a);
        boost::shared_ptr<BalancedBinaryTree> insertNode(boost::shared_ptr<BalancedBinaryTree>  a);
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> deleteNodeByKey(KeyType key);
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> deleteNodeByElem(ElemType elem);


        vector<boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>>> getAllnode();
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> getThis()
        {
            boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> ret
                    =boost::static_pointer_cast<BalancedBinaryTree<KeyType, ElemType>>(this->shared_from_this()) ;

            return ret;
        }
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> getNodeByElem(ElemType elem,bool mustleaf= false);
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> getNodeByKey(KeyType key,bool mustleaf= false);

    protected:
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> deleteNodeptr(boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> delnode);

        boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType> > & leftChild(boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType> > & c){
//            if (c ==NULL){
//                this->setChild(0,NULL) ;
//                return NULL;
//            }
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc=boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(c);
            this->setChild(0,cc);
            return  c;
        }

        boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType> > & rightChild(boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType> >  &c){

            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc=boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(c);
            this->setChild(1,cc) ;
            return  c;
        }
        boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType>>  leftChild(BalancedBinaryTree<KeyType,ElemType>  & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc(new BalancedBinaryTree(c));
            this->setChild(0,cc);
            boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BalancedBinaryTree<KeyType,ElemType>>(cc);
            return  aa;
        }

        boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType>>  rightChild(BalancedBinaryTree<KeyType,ElemType>  & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc(new BalancedBinaryTree(c));
            this->setChild(1,cc) ;
            boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BalancedBinaryTree<KeyType,ElemType>>(cc);
            return  aa;
        }
        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> leftChild()  {
            if (!this->leftchild_)
                return NULL;
            boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BalancedBinaryTree<KeyType,ElemType>>(this->leftchild_);
            return aa;
        }

        boost::shared_ptr<BalancedBinaryTree<KeyType, ElemType>> rightChild()  {
            if(!this->rightchild_)
                return NULL;
            boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BalancedBinaryTree<KeyType,ElemType>>(this->rightchild_);
            return aa;
        }
        boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType>>  resetBalance(KeyType findKey);
        boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType>> findLossBalanceChild(int & childBalanceFactor,
                KeyType key);
    private:
        boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType>>  rightRotationTransform();
        boost::shared_ptr<BalancedBinaryTree<KeyType,ElemType>>  leftRotationTransform();

    };



}
#endif //SMARTDONGLIB_BALANCEDBINARYTREE_H

#pragma clang diagnostic pop