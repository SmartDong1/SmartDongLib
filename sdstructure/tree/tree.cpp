//
// Created by Administrator on 2020/8/30.
//
#include <stack>
#include "tree.h"
namespace SmartDongLib{
    template<class KeyType, class ElemType>
    TreeNode<KeyType, ElemType>::TreeNode(const TreeNode &t) {
        key_=t.key_;
        elem_=t.elem_;
        parent_=t.parent_;
        childnum_=t.childnum_;
        initTree(childnum_);
    }

    template<class KeyType, class ElemType>
    TreeNode<KeyType, ElemType> &TreeNode<KeyType, ElemType>::operator=(const TreeNode &t) {
        key_=t.key_;
        elem_=t.elem_;
        parent_=t.parent_;
        childnum_=t.childnum_;
        initTree(childnum_);
        //setRowPos();
        return *this;
    }

    template<class KeyType, class ElemType>
    TreeNode<KeyType, ElemType>  &TreeNode<KeyType, ElemType>::operator=(TreeNode &&t) noexcept {
        //避免自己移动自己
        if ( this == &t )
            return *this;
        key_=t.key_;
        elem_=t.elem_;
        parent_=t.parent_;
        childnum_=t.childnum_;
        initTree(childnum_);
//        for (int i = 0; i < childnum_; ++i) {
//            t.setChild(i, NULL);
//        }

        return *this;
    }

    template<class KeyType, class ElemType>
    TreeNode<KeyType, ElemType>::TreeNode(TreeNode &&t) noexcept {
        key_=t.key_;
        elem_=t.elem_;
        parent_=t.parent_;
        childnum_=t.childnum_;
        initTree(childnum_);
//        for (int i = 0; i < childnum_; ++i) {
//            t.setChild(i, NULL);
//        }
    }

    template<class KeyType, class ElemType>
    TreeNode<KeyType, ElemType>::TreeNode(KeyType key, ElemType e, int cnum) {
        key_=key;
        elem_=e;
        initTree(cnum);
    }
    /**
     * <p>利用孩子数初始化孩子数组指针。
     * @tparam KeyType
     * @tparam ElemType
     * @param childnum 最大孩子数
     */
    template<class KeyType, class ElemType>
    void TreeNode<KeyType, ElemType>::initTree(int childnum){
        childnum_=childnum;
        children_=boost::shared_ptr< boost::shared_ptr<TreeNode>[]>(new   boost::shared_ptr<TreeNode>[childnum]);
//        for (int i = 0; i < childnum; ++i) {
//            children_[i] = NULL ;
//        }

    }
    /**
     * <p> 返回第i个孩子节点.
     * @tparam
     * @tparam ElemType
     * @param i 孩子位置
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<TreeNode<KeyType, ElemType>> &TreeNode<KeyType, ElemType>::getChild(int i) {
        if(i >= childnum_)
            throw TreeRunTimeException("childPointer out of range Exception");
        if (children_[i] != NULL )
            return children_[i];

        throw TreeRunTimeException("null childPointer Exception");
    }
    /**
    * <p> 返回第i个孩子节点.
    * @tparam KeyType
    * @tparam ElemType
    * @param i 孩子位置
    * @return 可以返回空指针
    */
    template<class KeyType, class ElemType>
    boost::shared_ptr<TreeNode<KeyType, ElemType>> &TreeNode<KeyType, ElemType>::getChildEx(int i) {
        if(i >= childnum_)
            throw TreeRunTimeException("childPointer out of range Exception");
        return children_[i];
    }
    /**
     * <p>树的节点总数.
     * @tparam KeyType
     * @tparam ElemType
     * @return
     */
    template<class KeyType, class ElemType>
    int TreeNode<KeyType, ElemType>::nodeCount(){
        int sum = 1;
        for (int i = 0; i < childnum_; ++i) {
            if (children_[i] !=NULL)
                sum += getChild(i)->nodeCount();
        }
        return sum;
    }
    /**
     * <p>树的深度.
     * @tparam KeyType
     * @tparam ElemType
     * @return
     */
    template<class KeyType, class ElemType>
    int TreeNode<KeyType, ElemType>::treeDeep() {
        int deep=0;
        if (getThis() !=NULL)
            deep =1;
        int maxdeep =deep;
        for (int i = 0; i < childnum_; ++i) {
            if (children_[i] !=NULL) {
                int childdeep= getChild(i)->treeDeep();
                maxdeep = maxdeep - (1+childdeep)<0? 1+childdeep:maxdeep;
            }
        }
        return maxdeep;
    }
    /**
     * <p>在第i个孩子中插入元素
     * @tparam KeyType
     * @tparam ElemType
     * @param i 孩子位置
     * @param c 要插入的东西
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<TreeNode<KeyType, ElemType> >& TreeNode<KeyType, ElemType>::setChild(int i, boost::shared_ptr<TreeNode> &c) {
        if(i >= childnum_)
            throw TreeRunTimeException("childPointer out of range Exception");
        if (c !=NULL){
            children_[i] =c;
            (children_[i])->parent_=getThis();
        }
        else
            children_[i] = NULL;
        return c;
    }
    /**
     * <p>在第i个孩子中插入元素
     * @tparam KeyType
     * @tparam ElemType
     * @param i 孩子位置
     * @param c 要插入的东西
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<TreeNode<KeyType, ElemType>> TreeNode<KeyType, ElemType>::setChild(int i, TreeNode c) {
        if(i >= childnum_)
            throw TreeRunTimeException("childPointer out of range Exception");
        boost::shared_ptr<TreeNode<KeyType, ElemType>>cc(new TreeNode<KeyType, ElemType>(c));
        children_[i] =cc;
        (children_[i])->parent_=getThis();
        return cc;
    }
//-------------------------------static-------------------------
    template<class KeyType, class ElemType>
    void TreeNode<KeyType, ElemType>::printData( TreeNode & c) {
        std::cout<<c.key() << "->" <<c.elem()<<"\n";
    }
    /**
     * <p>后序遍历树,先遍历左右孩子再遍历自己.
     * @tparam KeyType
     * @tparam ElemType
     * @param Visit 为TreeNode引用的函数
     */
    template<class KeyType, class ElemType>
    void TreeNode<KeyType, ElemType>::postOrderTraversal(void (*Visit)(TreeNode&)) {
        for (int i = 0; i < childnum_; ++i) {
            if (children_[i]!= NULL){
                children_[i] ->postOrderTraversal(Visit);
            }
        }
        Visit(*this);

    }
    /**
     * <p>先序遍历树，先遍历自己再遍历左右孩子.
     * @tparam KeyType
     * @tparam ElemType
     * @param Visit 为TreeNode引用的函数
     */
    template<class KeyType, class ElemType>
    void TreeNode<KeyType, ElemType>::preOrderTraversal(void (*Visit)(TreeNode &)) {
        Visit(*this);
        for (int i = 0; i < childnum_; ++i) {
            if (children_[i]!= NULL){
                children_[i] ->preOrderTraversal(Visit);
            }
        }
    }

    /**
     * <p>判断节点是否是叶子节点.
     * @tparam KeyType
     * @tparam ElemType
     * @return
     */
    template<class KeyType, class ElemType>
    bool TreeNode<KeyType, ElemType>::isLeaf() {
        for (int i = 0; i < childnum_; ++i) {
            if (children_[i] != NULL)
                return false;
        }
        return true;
    }
    /**
     * <p>根据key值返回节点，原理：先序遍历,取先序遍历最先符合条件的节点
     * @tparam KeyType
     * @tparam ElemType
     * @param key
     * @param mustleaf 是否要求是叶子节点
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<TreeNode<KeyType, ElemType>> TreeNode<KeyType, ElemType>::getNodeByKey(KeyType key,bool mustleaf) {
        std::vector<boost::shared_ptr<TreeNode<KeyType, ElemType>>> vecNode;
        getAllTreeNode(vecNode);
        for (int i = 0; i < vecNode.size(); ++i) {
            if (vecNode.at(i)->key() == key){
               if (!mustleaf ||  vecNode.at(i)->isLeaf())
                  return vecNode.at(i);
            }
        }
        return NULL;
    }
    /**
     * <p> 根据elem返回节点,原理：先序遍历,取先序遍历最先符合条件的节点
     * @tparam KeyType
     * @tparam ElemType
     * @param elem
     * @param mustleaf 是否要求是叶子节点
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<TreeNode<KeyType, ElemType>> TreeNode<KeyType, ElemType>::getNodeByElem(ElemType elem,bool mustleaf) {
        std::vector<boost::shared_ptr<TreeNode<KeyType, ElemType>>> vecNode;
        getAllTreeNode(vecNode);
        for (int i = 0; i < vecNode.size(); ++i) {
            if (vecNode.at(i)->elem() == elem){
                if (!mustleaf ||  vecNode.at(i)->isLeaf())
                    return vecNode.at(i);
            }
        }
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
    boost::shared_ptr<TreeNode<KeyType, ElemType>> TreeNode<KeyType, ElemType>::deleteNodeByKey(KeyType key) {
        boost::shared_ptr<TreeNode<KeyType, ElemType>> delnode=getNodeByKey(key);
        if (delnode == NULL){
            //未找到对应的节点,直接返回
            return  getThis();
        }

        int notnullChildIndex=-1; //最右孩子的位置
        for(int i = delnode->getChildnum() - 1 ; i >= 0 ; i--){
            //从右子树寻找非空的孩子
            if (delnode->getChildEx(i) != NULL){
                notnullChildIndex=i;
                break;
            }
        }
        int parentChildIndex=delnode->findIndexOnParent();
        if ( notnullChildIndex ==-1 && parentChildIndex == -1){
            //无孩子,无父母的节点
            return NULL;
        }
        //notnullChildIndex ==-1 为叶子节点  , parentChildIndex == -1 为根节点
        if (notnullChildIndex == -1){
            //是叶子节点时，中断和父母的联系
            delnode->parent()->getChildEx(parentChildIndex) =NULL;
            delnode->parent(NULL);
        } else{
            //非叶子节点  复制孩子内容后,删除孩子递归
            delnode->key(delnode->getChild(notnullChildIndex)->key());
            delnode->elem(delnode->getChild(notnullChildIndex)->elem());
            delnode->getChild(notnullChildIndex)->deleteNodeByKey(
                    delnode->getChild(notnullChildIndex)->key()
                    );
        }

        return getThis();
    }
    /**
     * <p>根据Elem删除节点,最先匹配原理是先序遍历,二叉搜索树删除方法,利用左子树的最右叶子，或者右子树的最左叶子替代。
     * @tparam KeyType
     * @tparam ElemType
     * @param elem
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<TreeNode<KeyType, ElemType>> TreeNode<KeyType, ElemType>::deleteNodeByElem(ElemType elem) {
        boost::shared_ptr<TreeNode<KeyType, ElemType>> delnode=getNodeByElem(elem);
        if (delnode == NULL){
            //未找到对应的节点,直接返回
            return  getThis();
        }

        int notnullChildIndex=-1; //最右孩子的位置
        for(int i = delnode->getChildnum() - 1 ; i >= 0 ; i--){
            //从右子树寻找非空的孩子
            if (delnode->getChildEx(i) != NULL){
                notnullChildIndex=i;
                break;
            }
        }
        int parentChildIndex=delnode->findIndexOnParent();
        if ( notnullChildIndex ==-1 && parentChildIndex == -1){
            //无孩子,无父母的节点
            return NULL;
        }
        //notnullChildIndex ==-1 为叶子节点  , parentChildIndex == -1 为根节点
        if (notnullChildIndex == -1){
            //是叶子节点时，中断和父母的联系
            delnode->parent()->getChildEx(parentChildIndex) =NULL;
            delnode->parent(NULL);
        } else{
            //非叶子节点  复制孩子内容后,删除孩子递归
            delnode->key(delnode->getChild(notnullChildIndex)->key());
            delnode->elem(delnode->getChild(notnullChildIndex)->elem());
            delnode->getChild(notnullChildIndex)->deleteNodeByElem(
                    delnode->getChild(notnullChildIndex)->elem()
            );
        }

        return getThis();
    }
    /**
     * <p>获取所有树节点
     * @tparam KeyType
     * @tparam ElemType
     * @param retVec  返回TreeNode集合
     */
    template<class KeyType, class ElemType>
    void TreeNode<KeyType, ElemType>::getAllTreeNode(std::vector<boost::shared_ptr<TreeNode<KeyType, ElemType>>> &retVec) {
        retVec.push_back(getThis());
        for (int i = 0; i < childnum_; ++i) {
            if (children_[i]!= NULL){
                children_[i]->getAllTreeNode(retVec);
            }
        }
    }
    /**
     * <p> 查找自身在父母孩子中的位置
     * @tparam KeyType
     * @tparam ElemType
     * @return -1无父母  0左子树  1次左子树(右子树)
     */
    template<class KeyType, class ElemType>
    int TreeNode<KeyType, ElemType>::findIndexOnParent() {
        boost::shared_ptr<TreeNode<KeyType, ElemType>> delnode=getThis();
        for (int i = 0; delnode->parent() != NULL && i < delnode->parent()->getChildnum(); ++i) {
            if (delnode->parent()->getChildEx(i) != NULL
                && delnode->parent()->getChild(i).get() == delnode.get()) {
                return i;
            }

        }
        return -1;

    }
    /**
     * <p>节点在树的深度,从根节点为1到自身位置的距离
     * @tparam KeyType
     * @tparam ElemType
     * @return
     */
    template<class KeyType, class ElemType>
    int TreeNode<KeyType, ElemType>::nodeDeep() {
        int ret=0;
        if (getThis() !=NULL)
            ret =1;
        boost::shared_ptr<TreeNode<KeyType, ElemType>> node =getThis();
        while(node->parent_){
            ret ++ ;
            node = node->parent_;
        }
        return ret;
    }
}