//
// Created by Administrator on 2021/1/8.
//

#include "splayTree.h"
namespace SmartDongLib {

    /**
    * <p>左旋 ：右子作父，原父为左子，原子节点左子树变原父节点右子树
    * @tparam KeyType
    * @tparam ElemType
    * @return
    */
    template<class KeyType, class ElemType>
    boost::shared_ptr<SplayTree < KeyType, ElemType>>
    SplayTree<KeyType, ElemType>::leftRotationTransform() {
        boost::shared_ptr<SplayTree < KeyType, ElemType>>
        orginRoot = getThis();
        boost::shared_ptr<SplayTree < KeyType, ElemType>>
        newRoot = orginRoot->rightChild();
        if (newRoot == NULL)
            return orginRoot;
        boost::shared_ptr<SplayTree < KeyType, ElemType>>
        parenttemp = orginRoot->parent();
        Size findIndexOnParent = orginRoot->findIndexOnParent();
        if (findIndexOnParent == 0) {
            orginRoot->parent()->leftChild(newRoot);
        } else if (findIndexOnParent == 1) {
            orginRoot->parent()->rightChild(newRoot);
        }
        //原子节点左子树变原父节点右子树
        boost::shared_ptr<SplayTree < KeyType, ElemType>>
        leftchildtemp = newRoot->leftChild();
        orginRoot->rightChild(leftchildtemp);
        newRoot->parent(parenttemp);
        //原父为左子
        newRoot->leftChild(orginRoot);
        return newRoot;
    }
    /**
    * <p>右旋 ：左子作父，原父为右子，原子节点右子树变原父节点左子树
    * @tparam KeyType
    * @tparam ElemType
    * @return
    */
    template<class KeyType, class ElemType>
    boost::shared_ptr<SplayTree < KeyType, ElemType>>
    SplayTree<KeyType, ElemType>::rightRotationTransform() {
        boost::shared_ptr<SplayTree < KeyType, ElemType>>
        orginRoot = getThis();
        boost::shared_ptr<SplayTree < KeyType, ElemType>>
        newRoot = orginRoot->leftChild();
        if (newRoot == NULL)
            return orginRoot;
        boost::shared_ptr<SplayTree < KeyType, ElemType>>
        parenttemp = orginRoot->parent();
        Size findIndexOnParent = orginRoot->findIndexOnParent();
        if (findIndexOnParent == 0) {
            orginRoot->parent()->leftChild(newRoot);
        } else if (findIndexOnParent == 1) {
            orginRoot->parent()->rightChild(newRoot);
        }
        //原 子节点右子树变原父节点左子树
        boost::shared_ptr<SplayTree < KeyType, ElemType>>
        rightchildtemp = newRoot->rightChild();
        newRoot->parent(parenttemp);
        orginRoot->leftChild(rightchildtemp);
        //原父为右子
        newRoot->rightChild(orginRoot);
        return newRoot;
    }
    /**
     * <p>分裂节点调整：
     * ①当分裂节点上面只有一个父节点时，分裂的时候将分裂节点上移1层（此时变为新根节点）
     * ②当分裂节点还有父节点以及祖父节点时，每次分裂的时候要将分裂节点上移2层
     * ③当还有父节点/祖父节点时，分裂节点参照步骤①或步骤②不断的向上移动，直到成为新根节点.
     * @tparam KeyType
     * @tparam ElemType
     * @param splayNode
     */
    template<class KeyType, class ElemType>
    void SplayTree<KeyType, ElemType>::adjustNode( boost::shared_ptr<SplayTree < KeyType, ElemType>> splayNode) {
        boost::shared_ptr<SplayTree < KeyType, ElemType>> parentNode = splayNode->parent();
        if (parentNode !=NULL){
            Size findIndexOnParent =splayNode->findIndexOnParent();
            boost::shared_ptr<SplayTree < KeyType, ElemType>> grandParentNode = splayNode->parent()->parent();
            if (grandParentNode !=NULL){
                //如果是在第二层以上节点,往根调整两层
                Size findIndexOnGrapdParent =parentNode->findIndexOnParent();
                if (findIndexOnParent ==0  && findIndexOnGrapdParent ==0 ){
                    parentNode->rightRotationTransform();
                    grandParentNode->rightRotationTransform();
                }else if(findIndexOnParent ==0  && findIndexOnGrapdParent ==1){
                    parentNode->rightRotationTransform();
                    grandParentNode->leftRotationTransform();
                }else if(findIndexOnParent ==1  && findIndexOnGrapdParent ==0){
                    parentNode->leftRotationTransform();
                    grandParentNode->rightRotationTransform();
                }else if(findIndexOnParent ==1  && findIndexOnGrapdParent ==1){
                    parentNode->leftRotationTransform();
                    grandParentNode->leftRotationTransform();
                }else{
                    return;
                }

            }else{
                //如果是在第二层节点,没有祖父节点,调整到第一层根节点
                if (findIndexOnParent ==0 ){
                    parentNode->rightRotationTransform();
                } else if(findIndexOnParent == 1){
                    parentNode->leftRotationTransform();
                } else{
                    return;
                }
            }
        }
        else{
            //根节点不调整
            return;
        }
    }
    /**
    * <p>根据元素键值查询节点，分裂节点是最后一次查询到的节点
    * @tparam KeyType
    * @tparam ElemType
    * @param elem
    * @param mustleaf  是否要求是叶子节点
    * @param isadjust  是否要求分裂节点的调整
    * @return
    */
    template<class KeyType, class ElemType>
    boost::shared_ptr<SplayTree<KeyType, ElemType>>
    SplayTree<KeyType, ElemType>::getNodeByKey(KeyType key, bool mustleaf,bool isadjust) {
        boost::shared_ptr<SplayTree<KeyType, ElemType>> root =this->getThis() ;
        bool isleaf =root ->isLeaf();
        while (root !=NULL){
            //add 2021-1-91 20:20 要求是否是叶子节点
            if (root->key()== key &&(!mustleaf || isleaf)){
                boost::shared_ptr<SplayTree<KeyType, ElemType>> ret = boost::static_pointer_cast<SplayTree<KeyType, ElemType>>(root);
                if(isadjust){
                    adjustNode(ret);
                }
                return ret;
            }
            if (key <= root->key() ){
                //小的往左子樹走,
                if (root->leftChild() != NULL){
                    root = root->leftChild();
                }else {
                    if(isadjust){
                        adjustNode(root);
                    }

                    return NULL;
                }
            }else{
                //大的往右子樹走
                if (root->rightChild() != NULL){
                    root = root->rightChild();
                }else {
                    if(isadjust){
                        adjustNode(root);
                    }
                    return NULL;
                }
            } //if ..elseif
        }//while
        return NULL;
    }
    /**
     * <p>根据元素类型查询节点，分裂节点是最后一次查询到的节点
     * @tparam KeyType
     * @tparam ElemType
     * @param elem
     * @param mustleaf  是否要求是叶子节点
     * @param isadjust  是否要求分裂节点的调整
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<SplayTree<KeyType, ElemType>>
    SplayTree<KeyType, ElemType>::getNodeByElem(ElemType elem, bool mustleaf,bool isadjust) {
        boost::shared_ptr<SplayTree<KeyType, ElemType>> ret = boost::static_pointer_cast<SplayTree<KeyType, ElemType>>
                (TreeNode<KeyType, ElemType>::getNodeByElem(elem, mustleaf) );
        if(isadjust){
            adjustNode(ret);
        }
        return ret;
    }
    /**
     * <p> 插入节点,分裂节点是插入的节点
     * @tparam KeyType
     * @tparam ElemType
     * @param a
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<SplayTree<KeyType, ElemType>> SplayTree<KeyType, ElemType>::insertNode(SplayTree & a) {
        boost::shared_ptr<SplayTree<KeyType, ElemType>> aa(new SplayTree<KeyType, ElemType>(a));
        return this->insertNode(aa);
    }
    /**
     * <p> 插入节点,分裂节点是插入的节点
     * @tparam KeyType
     * @tparam ElemType
     * @param node
     * @return
     */
    template<class KeyType, class ElemType>
    boost::shared_ptr<SplayTree<KeyType, ElemType>> SplayTree<KeyType, ElemType>::insertNode( boost::shared_ptr<SplayTree<KeyType, ElemType>> node) {
        boost::shared_ptr<SplayTree<KeyType, ElemType>> root = boost::dynamic_pointer_cast<SplayTree<KeyType,ElemType>>(this->getThis());
        Size childpos=-1;
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
        adjustNode(node);
        return this->getThis()->findroot();
    }

    template<class KeyType, class ElemType>
    boost::shared_ptr<SplayTree<KeyType, ElemType>> SplayTree<KeyType, ElemType>::findroot() {
        boost::shared_ptr<SplayTree<KeyType, ElemType>> root = boost::dynamic_pointer_cast<SplayTree<KeyType,ElemType>>(this->getThis());
        while (root ->parent() !=NULL){
            root = root ->parent();
        }
        return root;
    }



    /**
   * <p>根据Key删除节点,最先匹配原理是先序遍历,二叉搜索树删除方法,利用左子树的最右叶子，或者右子树的最左叶子替代。分裂节点是删除节点的孩子
   * @tparam KeyType
   * @tparam ElemType
   * @param key
   * @return
   */
    template<class KeyType, class ElemType>
    boost::shared_ptr<SplayTree<KeyType, ElemType>> SplayTree<KeyType, ElemType>::deleteNodeByKey(KeyType key) {
        boost::shared_ptr<SplayTree<KeyType, ElemType>> delnode=getNodeByKey(key, false, false);
        boost::shared_ptr<SplayTree<KeyType, ElemType>> root = findroot()  ;
        boost::shared_ptr<SplayTree<KeyType, ElemType>> NULLnode=NULL;

        if (delnode == NULL){
            //未找到对应的节点,直接返回
            return  getThis()->findroot();
        }
        boost::shared_ptr<SplayTree<KeyType, ElemType>> targetNode = delnode;
        Size notnullChildIndex=-1; //最右孩子的位置
        if (delnode ->leftChild()!=NULL){
            targetNode = delnode ->leftChild();
            if (root->delsplayNode_ ==NULL){
                //用树根节点记录分裂节点
                root->delsplayNode_ =targetNode;
            }
            //左子树不空,拿左子树的最深右子树替代
            while (targetNode->rightChild() !=NULL){
                targetNode = targetNode->rightChild();
            }
            delnode->key(targetNode->key());
            delnode->elem(targetNode->elem());
            targetNode->deleteNodeByKey(targetNode->key());
        }else if(delnode ->rightChild() !=NULL){
            targetNode = delnode ->rightChild();
            if (root->delsplayNode_ ==NULL){
                //用树根节点记录分裂节点
                root->delsplayNode_ =targetNode;
            }
            //右子树不空,拿右子树的最深左子树替代
            while (targetNode->leftChild() !=NULL){
                targetNode = targetNode->leftChild();
            }
            delnode->key(targetNode->key());
            delnode->elem(targetNode->elem());
            targetNode->deleteNodeByKey(targetNode->key());
        }else{
            //叶子节点
            if(delnode->parent() == NULL){
                //如果删除唯一根节点
                return  NULL;
            }
            Size parentChildIndex=delnode->findIndexOnParent();
            boost::shared_ptr<SplayTree<KeyType, ElemType>> parentNode= delnode->parent();

            if (parentChildIndex == 0){
                parentNode->leftchild_=NULL;
            }else if(parentChildIndex == 1){
                parentNode->rightchild_=NULL;
            }
            delnode->parent(NULLnode);
            if (root->delsplayNode_ !=NULL){
                //由于根节点删除规则是替换值，导致分裂节点是被删除的节点时,调整分裂节点父节点，否则调整分裂节点
                if (root->delsplayNode_->parent()==NULL)
                    adjustNode(parentNode);
                else
                    adjustNode(root->delsplayNode_);
                root->delsplayNode_=NULL;
            }
        }

        return getThis()->findroot();
    }

    /**
    * <p>根据elem删除节点,最先匹配原理是先序遍历,二叉搜索树删除方法,利用左子树的最右叶子，或者右子树的最左叶子替代。分裂节点是删除节点的孩子
    * @tparam KeyType
    * @tparam ElemType
    * @param elem
    * @return
    */
    template<class KeyType, class ElemType>
    boost::shared_ptr<SplayTree<KeyType, ElemType>> SplayTree<KeyType, ElemType>::deleteNodeByElem(ElemType elem) {
        boost::shared_ptr<SplayTree<KeyType, ElemType>> delnode=getNodeByElem(elem, false, false);
        boost::shared_ptr<SplayTree<KeyType, ElemType>> root = findroot()  ;
        boost::shared_ptr<SplayTree<KeyType, ElemType>> NULLnode=NULL;
        if (delnode == NULL){
            //未找到对应的节点,直接返回
            return  getThis()->findroot();
        }
        boost::shared_ptr<SplayTree<KeyType, ElemType>> targetNode = delnode;
        Size notnullChildIndex=-1; //最右孩子的位置
        if (delnode ->leftChild()!=NULL){
            targetNode = delnode ->leftChild();
            if (root->delsplayNode_ ==NULL){
                //用树根节点记录分裂节点
                root->delsplayNode_ =targetNode;
            }
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
            if (root->delsplayNode_ ==NULL){
                //用树根节点记录分裂节点
                root->delsplayNode_ =targetNode;
            }
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
            Size parentChildIndex=delnode->findIndexOnParent();
            boost::shared_ptr<SplayTree<KeyType, ElemType>> parentNode= delnode->parent();
            if (parentChildIndex == 0){
                parentNode->leftchild_=NULL;
            }else if(parentChildIndex == 1){
                parentNode->rightchild_=NULL;
            }
            delnode->parent(NULLnode);
            if (root->delsplayNode_ !=NULL){
                //由于根节点删除规则是替换值，导致分裂节点是被删除的节点时,调整分裂节点父节点，否则调整分裂节点
                if (root->delsplayNode_->parent()==NULL)
                    adjustNode(parentNode);
                else
                    adjustNode(root->delsplayNode_);
                root->delsplayNode_=NULL;
            }
        }

        return  getThis()->findroot();
    }



}