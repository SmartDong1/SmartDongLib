//
// Created by Administrator on 2020/9/7.
//每个节点颜色不是黑色，就是红色
//根节点是黑色的
//如果一个节点是红色，那么它的两个子节点就是黑色的（没有连续的红节点）
//对于每个节点，从该节点到其后代叶节点的简单路径上，均包含相同数目的黑色节点
//
// 祖宗根节点必黑，允许黑连黑，不允许红连红；新增红色，爸叔通红就变色，爸红叔黑就旋转，那黑往那旋
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#ifndef SMARTDONGLIB_REDBLACKTREE_H
#define SMARTDONGLIB_REDBLACKTREE_H
#include "binarySearchTree.cpp"
namespace SmartDongLib {
    enum ColorTag{Red = 0, Black,RealBlack};
    template<class KeyType,class ElemType >
    class RedBlackTree: public BinarySearchTree<KeyType, ElemType>{
    public:
        RedBlackTree(): BinarySearchTree<KeyType,ElemType>(){ colorTag_ = Black;}
        RedBlackTree(KeyType key,ElemType e ):BinarySearchTree<KeyType,ElemType>(key,e){ colorTag_ = Black;}
        RedBlackTree(const RedBlackTree &t): BinarySearchTree<KeyType,ElemType>(t.key(),t.elem()){ colorTag_ = t.colorTag_;/*复制构造只复制key和elem,其他用自身初始化*/}
        boost::shared_ptr<RedBlackTree> parent()  {
            if (!TreeNode<KeyType, ElemType>::parent() )
                return NULL;
            boost::shared_ptr<RedBlackTree<KeyType,ElemType>> aa = boost::static_pointer_cast<RedBlackTree<KeyType,ElemType>>(TreeNode<KeyType, ElemType>::parent());
            return aa;
        }
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>>& parent(boost::shared_ptr<RedBlackTree<KeyType, ElemType>>& p){

            boost::shared_ptr<TreeNode<KeyType,ElemType>> aa = boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(p);
            TreeNode<KeyType, ElemType>::parent(aa);
            return p;
        }
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> brother(){
            boost::shared_ptr<TreeNode<KeyType, ElemType>> bro= TreeNode<KeyType,ElemType>::brother();
            boost::shared_ptr<RedBlackTree<KeyType,ElemType>> ret =
                    boost::dynamic_pointer_cast<RedBlackTree<KeyType,ElemType>>(bro);
            return ret;
        }

        boost::shared_ptr<RedBlackTree> insertNode(RedBlackTree & a);
        boost::shared_ptr<RedBlackTree> insertNode(boost::shared_ptr<RedBlackTree>  a);
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> deleteNodeByKey(KeyType key);
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> deleteNodeByElem(ElemType elem);


        vector<boost::shared_ptr<RedBlackTree<KeyType, ElemType>>> getAllnode();
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> getThis()
        {
            boost::shared_ptr<RedBlackTree<KeyType, ElemType>> ret
            =boost::static_pointer_cast<RedBlackTree<KeyType, ElemType>>(this->shared_from_this()) ;
            return ret;
        }
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> getNodeByElem(ElemType elem,bool mustleaf= false);
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> getNodeByKey(KeyType key,bool mustleaf= false);
        ColorTag getColor(){return  colorTag_;}
        static ColorTag color(boost::shared_ptr<RedBlackTree<KeyType, ElemType>> a){
            if (a == NULL)
                return Black;
            return  a->colorTag_;
        }

    protected:
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> deleteNodeptr(boost::shared_ptr<RedBlackTree<KeyType, ElemType>> delnode);

        boost::shared_ptr<RedBlackTree<KeyType,ElemType> > & leftChild(boost::shared_ptr<RedBlackTree<KeyType,ElemType> > & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc=boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(c);
            this->setChild(0,cc);
            return  c;
        }

        boost::shared_ptr<RedBlackTree<KeyType,ElemType> > & rightChild(boost::shared_ptr<RedBlackTree<KeyType,ElemType> >  &c){

            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc=boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(c);
            this->setChild(1,cc) ;
            return  c;
        }
        boost::shared_ptr<RedBlackTree<KeyType,ElemType>>  leftChild(RedBlackTree<KeyType,ElemType>  & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc(new RedBlackTree(c));
            this->setChild(0,cc);
            boost::shared_ptr<RedBlackTree<KeyType,ElemType>> aa = boost::static_pointer_cast<RedBlackTree<KeyType,ElemType>>(cc);
            return  aa;
        }

        boost::shared_ptr<RedBlackTree<KeyType,ElemType>>  rightChild(RedBlackTree<KeyType,ElemType>  & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc(new RedBlackTree(c));
            this->setChild(1,cc) ;
            boost::shared_ptr<RedBlackTree<KeyType,ElemType>> aa = boost::static_pointer_cast<RedBlackTree<KeyType,ElemType>>(cc);
            return  aa;
        }
        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> leftChild()  {
            if (!this->leftchild_)
                return NULL;
            boost::shared_ptr<RedBlackTree<KeyType,ElemType>> aa = boost::static_pointer_cast<RedBlackTree<KeyType,ElemType>>(this->leftchild_);
            return aa;
        }

        boost::shared_ptr<RedBlackTree<KeyType, ElemType>> rightChild()  {
            if(!this->rightchild_)
                return NULL;
            boost::shared_ptr<RedBlackTree<KeyType,ElemType>> aa = boost::static_pointer_cast<RedBlackTree<KeyType,ElemType>>(this->rightchild_);
            return aa;
        }
        boost::shared_ptr<RedBlackTree<KeyType,ElemType>>  resetBalance(KeyType findKey);

        boost::shared_ptr<RedBlackTree<KeyType,ElemType>>  resetDelBalance(boost::shared_ptr<RedBlackTree<KeyType,ElemType>> delnode);
    private:
        boost::shared_ptr<RedBlackTree<KeyType,ElemType>>  rightRotationTransform();
        boost::shared_ptr<RedBlackTree<KeyType,ElemType>>  leftRotationTransform();
        ColorTag colorTag_;

    };


}

#endif //SMARTDONGLIB_REDBLACKTREE_H

#pragma clang diagnostic pop