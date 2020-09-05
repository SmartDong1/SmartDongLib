//
// Created by hu on 2020/8/26.
//

#ifndef SMARTDONGLIB_TREE_H
#define SMARTDONGLIB_TREE_H
#include <boost/shared_ptr.hpp>
#include <cstdarg>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
namespace SmartDongLib {
    class TreeRunTimeException: public std::runtime_error{
    public:
        TreeRunTimeException(): std::runtime_error("tree out of range Exception"){}
        TreeRunTimeException(const std::string& __arg): std::runtime_error("tree overflow_error Exception:" + __arg){}

    };
    template<class KeyType,class ElemType >
    class TreeNode: public boost::enable_shared_from_this<TreeNode <KeyType,ElemType>> {
    public:
        TreeNode(int cnum=0) {
            initTree(cnum);

        };
        TreeNode(const TreeNode& t);
        TreeNode& operator =(const TreeNode  & t);
        TreeNode& operator =( TreeNode && t)noexcept;
        TreeNode (TreeNode && t) noexcept;
        TreeNode(KeyType key,ElemType e ,int cnum=0);
        bool isLeaf();

         boost::shared_ptr<TreeNode> getThis()
        {
            return this->shared_from_this();
        }
        int nodeCount();
        int treeDeep();
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

        int  getChildnum() const {
            return childnum_;
        }
        const boost::shared_ptr<TreeNode> &parent() const {
            return parent_;
        }
        boost::shared_ptr<TreeNode<KeyType, ElemType>>& parent(boost::shared_ptr<TreeNode<KeyType, ElemType>> p){
            parent_ =p;
            return parent_;
        }
        static void printData(TreeNode & c);

        void postOrderTraversal(void (*Visit)(TreeNode&) = TreeNode::printData);
        void preOrderTraversal(void (*Visit)(TreeNode&) = TreeNode::printData);

        boost::shared_ptr<TreeNode<KeyType, ElemType>> getNodeByKey(KeyType key,bool mustleaf= false);
        boost::shared_ptr<TreeNode<KeyType, ElemType>> getNodeByElem(ElemType elem,bool mustleaf= false);

        boost::shared_ptr<TreeNode<KeyType, ElemType>> deleteNodeByKey(KeyType key);
        boost::shared_ptr<TreeNode<KeyType, ElemType>> deleteNodeByElem(ElemType elem);
        int findIndexOnParent();
        void getAllTreeNode(std::vector<boost::shared_ptr<TreeNode<KeyType, ElemType>>> & retVec);

    protected:
        boost::shared_ptr<TreeNode<KeyType, ElemType> >& setChild(int i , boost::shared_ptr<TreeNode > & c);
        boost::shared_ptr<TreeNode<KeyType, ElemType>> setChild(int i , TreeNode  c);
        virtual boost::shared_ptr<TreeNode>& getChild(int i);
        virtual boost::shared_ptr<TreeNode>& getChildEx(int i);

    private:
        KeyType key_;
        ElemType elem_;
        int childnum_;
        boost::shared_ptr<TreeNode> parent_;
        boost::shared_ptr< boost::shared_ptr<TreeNode>[] > children_;
        void initTree(int childnum);
    };


}
#endif //SMARTDONGLIB_TREE_H
