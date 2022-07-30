//
// Created by hu on 2020/8/26.
//

#ifndef SMARTDONGLIB_TREE_H
#define SMARTDONGLIB_TREE_H
#include <boost/shared_ptr.hpp>
#include <cstdarg>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include "const.h"
#include <vector>
namespace SmartDongLib {
    class TreeRunTimeException: public std::runtime_error{
    public:
        TreeRunTimeException(): std::runtime_error("tree out of range Exception"){}
        TreeRunTimeException(const std::string& __arg): std::runtime_error("tree overflow_error Exception:" + __arg){}

    };
    template<class KeyType,class ElemType >
    class TreeNode: public boost::enable_shared_from_this<TreeNode <KeyType,ElemType>> {
    public:
        TreeNode(Size cnum=0) {
            initTree(cnum);

        };
        TreeNode(const TreeNode& t);
        TreeNode& operator =(const TreeNode  & t);
        TreeNode& operator =( TreeNode && t)noexcept;
        TreeNode (TreeNode && t) noexcept;
        TreeNode(KeyType key,ElemType e ,Size cnum=0);
        bool isLeaf();

         boost::shared_ptr<TreeNode> getThis()
        {
            return this->shared_from_this();
        }
        Size nodeCount();
        Size treeDeep();
        Size nodeHeight(){return treeDeep();}
        Size nodeDeep();
        KeyType key() const {
            return key_;
        }
        KeyType key(KeyType k)  {
            key_=k;
            return key_;
        }
        ElemType elem(ElemType e)  {
            elem_=e;
            return elem_;
        }
        ElemType elem() const {
            return elem_;
        }

        Size  getChildnum() const {
            return childnum_;
        }
        const boost::shared_ptr<TreeNode> &parent() const {
            return parent_;
        }
        boost::shared_ptr<TreeNode<KeyType, ElemType>>& parent(boost::shared_ptr<TreeNode<KeyType, ElemType>> p){
            parent_ =p;
            return parent_;
        }
        boost::shared_ptr<TreeNode<KeyType, ElemType>> brother(){
            boost::shared_ptr<TreeNode<KeyType, ElemType>> root= getThis();
            Size findIndexonParent=findIndexOnParent();
            if (findIndexonParent == -1 )
                return NULL;
            for (Size i = 0; i < root->parent()->childnum_; ++i) {
                if (root->parent()->children_[i] !=root )
                    return root->parent()->children_[i];
            }
            return NULL;
        }
        static void prSizeData(boost::shared_ptr<TreeNode<KeyType, ElemType>> c);

        void postOrderTraversal(void (*Visit)(boost::shared_ptr<TreeNode<KeyType, ElemType>> ) = TreeNode::prSizeData);
        void preOrderTraversal(void (*Visit)(boost::shared_ptr<TreeNode<KeyType, ElemType>> ) = TreeNode::prSizeData);

        boost::shared_ptr<TreeNode<KeyType, ElemType>> getNodeByKey(KeyType key,bool mustleaf= false);
        boost::shared_ptr<TreeNode<KeyType, ElemType>> getNodeByElem(ElemType elem,bool mustleaf= false);

        boost::shared_ptr<TreeNode<KeyType, ElemType>> deleteNodeByKey(KeyType key);
        boost::shared_ptr<TreeNode<KeyType, ElemType>> deleteNodeByElem(ElemType elem);
        Size findIndexOnParent();
        void getAllTreeNode(std::vector<boost::shared_ptr<TreeNode<KeyType, ElemType>>> & retVec);

//    protected:
        boost::shared_ptr<TreeNode<KeyType, ElemType> >& setChild(Size i , boost::shared_ptr<TreeNode > & c);
        boost::shared_ptr<TreeNode<KeyType, ElemType>> setChild(Size i , TreeNode  c);
        virtual boost::shared_ptr<TreeNode>& getChild(Size i);
        virtual boost::shared_ptr<TreeNode>& getChildEx(Size i);

    private:
        KeyType key_;
        ElemType elem_;
        Size childnum_;
        boost::shared_ptr<TreeNode> parent_;
        boost::shared_ptr< boost::shared_ptr<TreeNode>[] > children_;
        void initTree(Size childnum);
    };


}
#endif //SMARTDONGLIB_TREE_H
