//
// Created by hu on 2020/8/27.
//

#include "binaryTree.h"
#include <stack>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
namespace SmartDongLib{
    /**
     * <p>判定树的类型 普通二叉树，满二叉树，完全二叉树.
     * @tparam KeyType
     * @tparam ElemType
     * @return
     */
    template<class KeyType, class ElemType>
    BiTreeType BinaryTree<KeyType, ElemType>::getTreeType() {
        int nodecount=this->nodeCount();
        int treedeep =this->treeDeep();
        if (nodecount == pow(2.0,treedeep) -1 ) {
            return FullBiTree;
        }
        //完全二叉树判定
        {
            //每个节点的左右孩子深度差距不能超过 1 ，且右节点存在时左节点必定存在
            //利用队列 把深度不为1的子节点的 左右孩子依次塞进队列,是空则为赛空进去，
            // 如果队列最后一个元素不为空队列长度就是nodecount为完全二叉树，如果队列最后一个元素不为空队列长度就是nodecount+1为完全二叉树
            std::queue<boost::shared_ptr<BinaryTree<KeyType,ElemType>>> que;
            //标记是否遍历到了叶子节点
            bool flag = false;

            boost::shared_ptr<BinaryTree> self =boost::dynamic_pointer_cast<BinaryTree<KeyType,ElemType>>(this->getThis());
            que.push(self);
            while(!que.empty()){
                self =que.front();
                que.pop();
                boost::shared_ptr<BinaryTree> selfleft = self->leftChild();
                boost::shared_ptr<BinaryTree> selfright = self->rightChild();
                if ((flag && (selfleft != NULL || selfright != NULL)) || (selfleft == NULL && selfright != NULL)) {
                    //当前结点不是叶子结点且之前结点有叶子结点 || 当前结点有右孩子无左孩子
                    goto OUT_OF_COMPLETEBITREE;
                }
                if (selfleft != NULL) {
                    que.push(selfleft);
                }else {
                    flag = true;//无孩子即为叶子结点
                }
                if (selfright != NULL) {
                    que.push(selfright);
                } else {
                    flag = true;//无孩子即为叶子结点
                }
            }
           return CompleteBiTree;
        }
        OUT_OF_COMPLETEBITREE:
        return NormalBiTree;
    }
    /**
     * <p>非递归中序遍历算法
     * @tparam KeyType
     * @tparam ElemType
     * @param Visit 关于TreeNode引用的函数
     */
    template<class KeyType, class ElemType>
    void BinaryTree<KeyType, ElemType>::inOrderTraversal(void (*Visit)(TreeNode<KeyType, ElemType> &)) {
        //用来存储待访问的栈
        std::stack<boost::shared_ptr<BinaryTree<KeyType,ElemType>>>  sta;
        boost::shared_ptr<BinaryTree<KeyType,ElemType>> root =boost::static_pointer_cast<BinaryTree<KeyType,ElemType>>(this->getThis());
        //根节点入栈，左节点入栈，当没有左节点的时候，弹出栈访问，再右子树入栈
        while (root || !sta.empty()){
            if (root){
                //如果节点存在入栈,遍历左子树
                sta.push(root);
                root=root->leftChild();
            } else{
                //如果节点不存在,弹出栈，访问,遍历右子树
                root = sta.top();
                sta.pop();
                Visit(*root);
                root=root->rightChild();
            }

        }
    }
    /**
     * <p>返回所有树节点.
     * @tparam KeyType
     * @tparam ElemType
     * @return BinaryTree智能指针集合
     */
    template<class KeyType, class ElemType>
    vector<boost::shared_ptr<BinaryTree<KeyType, ElemType>>> BinaryTree<KeyType, ElemType>::getAllnode() {
        vector<boost::shared_ptr<TreeNode<KeyType, ElemType>> >temp;
        TreeNode<KeyType, ElemType>::getAllTreeNode(temp);
        vector<boost::shared_ptr<BinaryTree<KeyType, ElemType>>> ret;
        for (int i = 0; i < temp.size(); ++i) {
            boost::shared_ptr<BinaryTree<KeyType, ElemType>> a = boost::static_pointer_cast<BinaryTree<KeyType, ElemType>>(temp.at(i));
            ret.push_back(a);
        }
        return ret;
    }

    template<class KeyType, class ElemType>
    boost::shared_ptr<BinaryTree<KeyType, ElemType>>
    BinaryTree<KeyType, ElemType>::getNodeByKey(KeyType key, bool mustleaf) {
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> ret = boost::static_pointer_cast<BinaryTree<KeyType, ElemType>>
                (TreeNode<KeyType, ElemType>::getNodeByKey(key, mustleaf) );
        return ret;
    }

    template<class KeyType, class ElemType>
    boost::shared_ptr<BinaryTree<KeyType, ElemType>>
    BinaryTree<KeyType, ElemType>::getNodeByElem(ElemType elem, bool mustleaf) {
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> ret = boost::static_pointer_cast<BinaryTree<KeyType, ElemType>>
                (TreeNode<KeyType, ElemType>::getNodeByElem(elem, mustleaf) );
        return ret;
    }
    /**
     * <p>根据Key删除节点,最先匹配原理是先序遍历,二叉搜索树删除方法,利用左子树的最右叶子，或者右子树的最左叶子替代。
     * @tparam KeyType
     * @tparam ElemType
     * @param key
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<BinaryTree<KeyType, ElemType>> BinaryTree<KeyType, ElemType>::deleteNodeByKey(KeyType key) {
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> delnode=getNodeByKey(key);
        if (delnode == NULL){
            //未找到对应的节点,直接返回
            return  getThis();
        }
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> targetNode = delnode;
        int notnullChildIndex=-1; //最右孩子的位置
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
            int parentChildIndex=delnode->findIndexOnParent();
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
    boost::shared_ptr<BinaryTree<KeyType, ElemType>> BinaryTree<KeyType, ElemType>::deleteNodeByElem(ElemType elem) {
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> delnode=getNodeByElem(elem);
        if (delnode == NULL){
            //未找到对应的节点,直接返回
            return  getThis();
        }
        boost::shared_ptr<BinaryTree<KeyType, ElemType>> targetNode = delnode;
        int notnullChildIndex=-1; //最右孩子的位置
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
            int parentChildIndex=delnode->findIndexOnParent();
            if (parentChildIndex == 0){
                delnode->parent()->leftchild_=NULL;
            }else if(parentChildIndex == 1){
                delnode->parent()->rightchild_=NULL;
            }

        }

        return getThis();
    }


}
#pragma clang diagnostic pop