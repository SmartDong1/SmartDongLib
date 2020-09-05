//
// Created by Administrator on 2020/9/4.
//

#ifndef SMARTDONGLIB_BINARYSEARCHTREE_H
#define SMARTDONGLIB_BINARYSEARCHTREE_H
#include "binaryTree.cpp"
namespace SmartDongLib {
    template<class KeyType,class ElemType >
    class BinarySearchTree : public BinaryTree<KeyType,ElemType>{
    public:
        BinarySearchTree(): BinaryTree<KeyType,ElemType>(){}
        BinarySearchTree(KeyType key,ElemType e ):
                BinaryTree<KeyType,ElemType>(key,e){}
        BinarySearchTree(const BinarySearchTree &t): BinaryTree<KeyType,ElemType>(t.key(),t.elem()){/*复制构造只复制key和elem,其他用自身初始化*/}
        boost::shared_ptr<BinarySearchTree> parent()  {
            if (!TreeNode<KeyType, ElemType>::parent() )
                return NULL;
            boost::shared_ptr<BinarySearchTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BinarySearchTree<KeyType,ElemType>>(TreeNode<KeyType, ElemType>::parent());
            return aa;
        }
        boost::shared_ptr<BinarySearchTree> insertNode(BinarySearchTree & a);
        boost::shared_ptr<BinarySearchTree> insertNode(boost::shared_ptr<BinarySearchTree>  a);
        vector<boost::shared_ptr<BinarySearchTree<KeyType, ElemType>>> getAllnode();
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> getThis()
        {
            boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> ret
            =boost::static_pointer_cast<BinarySearchTree<KeyType, ElemType>>(this->shared_from_this()) ;

            return ret;
        }
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> getNodeByElem(ElemType elem,bool mustleaf= false);
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> getNodeByKey(KeyType key,bool mustleaf= false);
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> deleteNodeByKey(KeyType key);
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> deleteNodeByElem(ElemType elem);
    protected:
        boost::shared_ptr<BinarySearchTree<KeyType,ElemType> > & leftChild(boost::shared_ptr<BinarySearchTree<KeyType,ElemType> > & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc=boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(c);
            this->setChild(0,cc);
            return  c;
        }

        boost::shared_ptr<BinarySearchTree<KeyType,ElemType> > & rightChild(boost::shared_ptr<BinarySearchTree<KeyType,ElemType> > & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc=boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(c);
            this->setChild(1,cc) ;
            return  c;
        }
        boost::shared_ptr<BinarySearchTree<KeyType,ElemType>>  leftChild(BinarySearchTree<KeyType,ElemType>  & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc(new BinarySearchTree(c));
            this->setChild(0,cc);
            boost::shared_ptr<BinarySearchTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BinarySearchTree<KeyType,ElemType>>(cc);
            return  aa;
        }

        boost::shared_ptr<BinarySearchTree<KeyType,ElemType>>  rightChild(BinarySearchTree<KeyType,ElemType>  & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc(new BinarySearchTree(c));
            this->setChild(1,cc) ;
            boost::shared_ptr<BinarySearchTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BinarySearchTree<KeyType,ElemType>>(cc);
            return  aa;
        }
        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> leftChild()  {
            if (!this->leftchild_)
                return NULL;
            boost::shared_ptr<BinarySearchTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BinarySearchTree<KeyType,ElemType>>(this->leftchild_);
            return aa;
        }

        boost::shared_ptr<BinarySearchTree<KeyType, ElemType>> rightChild()  {
            if(!this->rightchild_)
                return NULL;
            boost::shared_ptr<BinarySearchTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BinarySearchTree<KeyType,ElemType>>(this->rightchild_);
            return aa;
        }

    };


}

#endif //SMARTDONGLIB_BINARYSEARCHTREE_H
