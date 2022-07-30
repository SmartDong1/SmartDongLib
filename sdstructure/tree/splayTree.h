//
// Created by Administrator on 2021/1/8.
// 伸展树：一种访问过后的节点会变的更接近与树根的二叉搜索树
//
#pragma ide diagnostic ignored "HidingNonVirtualFunction"

#ifndef SMARTDONGLIB_SPLAYTREE_H
#define SMARTDONGLIB_SPLAYTREE_H
#include "binarySearchTree.cpp"
namespace SmartDongLib {

    template<class KeyType,class ElemType >
    class SplayTree: public BinarySearchTree<KeyType,ElemType> {
    public:
        SplayTree(): BinarySearchTree<KeyType,ElemType>(){}
        SplayTree(KeyType key,ElemType e ):BinarySearchTree<KeyType,ElemType>(key,e){}
        SplayTree(const SplayTree &t): BinarySearchTree<KeyType,ElemType>(t.key(),t.elem()){ /*复制构造只复制key和elem,其他用自身初始化*/}
        boost::shared_ptr<SplayTree<KeyType, ElemType>> parent()  {
            if (!TreeNode<KeyType, ElemType>::parent() )
                return NULL;
            boost::shared_ptr<SplayTree<KeyType,ElemType>> aa = boost::static_pointer_cast<SplayTree<KeyType,ElemType>>(TreeNode<KeyType, ElemType>::parent());
            return aa;
        }
        boost::shared_ptr<SplayTree<KeyType, ElemType>>& parent(boost::shared_ptr<SplayTree<KeyType, ElemType>>& p){

            boost::shared_ptr<TreeNode<KeyType,ElemType>> aa = boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(p);
            TreeNode<KeyType, ElemType>::parent(aa);
            return p;
        }
        boost::shared_ptr<SplayTree<KeyType, ElemType>> brother(){
            boost::shared_ptr<TreeNode<KeyType, ElemType>> bro= TreeNode<KeyType,ElemType>::brother();
            boost::shared_ptr<SplayTree<KeyType,ElemType>> ret =
                                                                      boost::dynamic_pointer_cast<SplayTree<KeyType,ElemType>>(bro);
            return ret;
        }
        boost::shared_ptr<SplayTree<KeyType, ElemType>> getThis()
        {
            boost::shared_ptr<SplayTree<KeyType, ElemType>> ret=boost::static_pointer_cast<SplayTree<KeyType, ElemType>>(this->shared_from_this()) ;
            return ret;
        }
        boost::shared_ptr<SplayTree<KeyType,ElemType> > & leftChild(boost::shared_ptr<SplayTree<KeyType,ElemType> > & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc=boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(c);
            this->setChild(0,cc);
            return  c;
        }
        boost::shared_ptr<SplayTree<KeyType,ElemType> > & rightChild(boost::shared_ptr<SplayTree<KeyType,ElemType> >  &c){

            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc=boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(c);
            this->setChild(1,cc) ;
            return  c;
        }
        boost::shared_ptr<SplayTree<KeyType,ElemType>>  leftChild(SplayTree<KeyType,ElemType>  & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc(new SplayTree(c));
            this->setChild(0,cc);
            boost::shared_ptr<SplayTree<KeyType,ElemType>> aa = boost::static_pointer_cast<SplayTree<KeyType,ElemType>>(cc);
            return  aa;
        }
        boost::shared_ptr<SplayTree<KeyType,ElemType>>  rightChild(SplayTree<KeyType,ElemType>  & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc(new SplayTree(c));
            this->setChild(1,cc) ;
            boost::shared_ptr<SplayTree<KeyType,ElemType>> aa = boost::static_pointer_cast<SplayTree<KeyType,ElemType>>(cc);
            return  aa;
        }
        boost::shared_ptr<SplayTree<KeyType, ElemType>> leftChild()  {
            if (!this->leftchild_)
                return NULL;
            boost::shared_ptr<SplayTree<KeyType,ElemType>> aa = boost::static_pointer_cast<SplayTree<KeyType,ElemType>>(this->leftchild_);
            return aa;
        }
        boost::shared_ptr<SplayTree<KeyType, ElemType>> rightChild()  {
            if(!this->rightchild_)
                return NULL;
            boost::shared_ptr<SplayTree<KeyType,ElemType>> aa = boost::static_pointer_cast<SplayTree<KeyType,ElemType>>(this->rightchild_);
            return aa;
        }
        boost::shared_ptr<SplayTree<KeyType, ElemType>> findroot();
    private:
        void adjustNode(boost::shared_ptr<SplayTree < KeyType, ElemType>> splayNode);
        boost::shared_ptr<SplayTree<KeyType,ElemType>>  rightRotationTransform();
        boost::shared_ptr<SplayTree<KeyType,ElemType>>  leftRotationTransform();
        boost::shared_ptr<SplayTree<KeyType,ElemType>> delsplayNode_; //删除操作中的分裂节点
    public:
        boost::shared_ptr<SplayTree<KeyType, ElemType>> getNodeByKey(KeyType key,bool mustleaf= false,bool isadjust=true);
        boost::shared_ptr<SplayTree<KeyType, ElemType>> getNodeByElem(ElemType elem,bool mustleaf= false,bool isadjust= true);

        boost::shared_ptr<SplayTree<KeyType, ElemType>> deleteNodeByKey(KeyType key);
        boost::shared_ptr<SplayTree<KeyType, ElemType>> deleteNodeByElem(ElemType elem);

        boost::shared_ptr<SplayTree> insertNode(boost::shared_ptr<SplayTree>  a);
        boost::shared_ptr<SplayTree> insertNode(SplayTree & a);


    };
}

#endif //SMARTDONGLIB_SPLAYTREE_H
