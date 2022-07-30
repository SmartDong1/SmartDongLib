//
// Created by hu on 2020/8/27.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#ifndef SMARTDONGLIB_BINARYTREE_H
#define SMARTDONGLIB_BINARYTREE_H
#include "tree.cpp"
#include <ostream>
#include <math.h>
#include <queue>
using namespace std;
namespace SmartDongLib {
    enum BiTreeType{NormalBiTree=0,CompleteBiTree,FullBiTree};

    template<class KeyType,class ElemType >
    class BinaryTree: public TreeNode<KeyType,ElemType> {
    public:
        BinaryTree(): TreeNode<KeyType,ElemType>(2),
                leftchild_(this->getChildEx(0)), rightchild_(this->getChildEx(1)){
        }
        BinaryTree(KeyType key,ElemType e ):
                TreeNode<KeyType,ElemType>(key,e,2),
                        leftchild_(this->getChildEx(0)), rightchild_(this->getChildEx(1)){
        }

        BinaryTree(const BinaryTree &t): TreeNode<KeyType,ElemType>(t.key(),t.elem(),2),
                                         leftchild_(this->getChildEx(0)), rightchild_(this->getChildEx(1)){/*复制构造只复制key和elem,其他用自身初始化*/}

        boost::shared_ptr<BinaryTree<KeyType,ElemType> > & leftChild(boost::shared_ptr<BinaryTree<KeyType,ElemType> > & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc=boost::static_pointer_cast <TreeNode<KeyType,ElemType>>(c);
            this->setChild(0,cc);
            return  c;
        }
        boost::shared_ptr<BinaryTree> getThis()
        {
            boost::shared_ptr<BinaryTree<KeyType,ElemType>> ret = boost::static_pointer_cast<BinaryTree<KeyType,ElemType>>(this->shared_from_this());
            return ret;
        }
        boost::shared_ptr<BinaryTree<KeyType,ElemType> > & rightChild(boost::shared_ptr<BinaryTree<KeyType,ElemType> > & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc=boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(c);
            this->setChild(1,cc) ;
            return  c;
        }
        boost::shared_ptr<BinaryTree<KeyType,ElemType>>  leftChild(BinaryTree<KeyType,ElemType>  & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc(new BinaryTree(c));
            this->setChild(0,cc);
            boost::shared_ptr<BinaryTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BinaryTree<KeyType,ElemType>>(cc);
            return  aa;
        }

        boost::shared_ptr<BinaryTree<KeyType,ElemType>>  rightChild(BinaryTree<KeyType,ElemType>  & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc(new BinaryTree(c));
            this->setChild(1,cc) ;
            boost::shared_ptr<BinaryTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BinaryTree<KeyType,ElemType>>(cc);
            return  aa;
        }
         boost::shared_ptr<BinaryTree<KeyType, ElemType>> leftChild()  {
            if (!leftchild_)
                return NULL;
             boost::shared_ptr<BinaryTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BinaryTree<KeyType,ElemType>>(leftchild_);
            return aa;
        }

         boost::shared_ptr<BinaryTree<KeyType, ElemType>> rightChild()  {
             if(!rightchild_)
                 return NULL;
             boost::shared_ptr<BinaryTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BinaryTree<KeyType,ElemType>>(rightchild_);
             return aa;
        }
         boost::shared_ptr<BinaryTree> parent()  {
            if (!TreeNode<KeyType, ElemType>::parent() )
                return NULL;
             boost::shared_ptr<BinaryTree<KeyType,ElemType>> aa = boost::static_pointer_cast<BinaryTree<KeyType,ElemType>>(TreeNode<KeyType, ElemType>::parent());
            return aa;
        }

        boost::shared_ptr<BinaryTree<KeyType, ElemType>> getNodeByKey(KeyType key,bool mustleaf= false);
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> getNodeByElem(ElemType elem,bool mustleaf= false);
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> deleteNodeByKey(KeyType key);
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> deleteNodeByElem(ElemType elem);
        void inOrderTraversal(void (*Visit)(boost::shared_ptr<TreeNode<KeyType, ElemType>>)
                = TreeNode<KeyType,ElemType>::prSizeData);
        BiTreeType getTreeType();
        std::vector<boost::shared_ptr<BinaryTree<KeyType, ElemType>>> getAllnode();
    protected:
        boost::shared_ptr<TreeNode<KeyType,ElemType>>& leftchild_;
        boost::shared_ptr<TreeNode<KeyType,ElemType>>& rightchild_;
    };



}
#endif //SMARTDONGLIB_BINARYTREE_H

#pragma clang diagnostic pop