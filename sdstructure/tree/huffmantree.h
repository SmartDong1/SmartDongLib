//
// Created by Administrator on 2020/9/2.
//

#ifndef SMARTDONGLIB_HUFFMANTREE_H
#define SMARTDONGLIB_HUFFMANTREE_H
#include "binaryTree.cpp"
namespace SmartDongLib {
    template<class KeyType, class ElemType>
    class HuffmanTree: public BinaryTree <KeyType,ElemType> {
    public:
        HuffmanTree()= default;
        HuffmanTree(KeyType key,ElemType e ):BinaryTree<KeyType,ElemType> ( key, e ){}
        std::string getHuffmanCodeByKey(KeyType key);
        std::string getHuffmanCodeByElem(ElemType e);
        boost::shared_ptr<HuffmanTree> parent()  {
            if (!TreeNode<KeyType, ElemType>::parent() )
                return NULL;
            boost::shared_ptr<HuffmanTree<KeyType,ElemType>> aa = boost::static_pointer_cast<HuffmanTree<KeyType,ElemType>>(TreeNode<KeyType, ElemType>::parent());
            return aa;
        }
        boost::shared_ptr<HuffmanTree<KeyType, ElemType>> leftChild()  {
            if (!this->leftchild_)
                return NULL;
            boost::shared_ptr<HuffmanTree<KeyType,ElemType>> aa = boost::static_pointer_cast<HuffmanTree<KeyType,ElemType>>(this->leftchild_);
            return aa;
        }

        boost::shared_ptr<HuffmanTree<KeyType, ElemType>> rightChild()  {
            if(!this->rightchild_)
                return NULL;
            boost::shared_ptr<HuffmanTree<KeyType,ElemType>> aa = boost::static_pointer_cast<HuffmanTree<KeyType,ElemType>>(this->rightchild_);
            return aa;
        }

        boost::shared_ptr<HuffmanTree<KeyType,ElemType> > & leftChild(boost::shared_ptr<HuffmanTree<KeyType,ElemType> > & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc=boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(c);
            this->setChild(0,cc);
            return  c;
        }

        boost::shared_ptr<HuffmanTree<KeyType,ElemType> > & rightChild(boost::shared_ptr<HuffmanTree<KeyType,ElemType> > & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc=boost::static_pointer_cast<TreeNode<KeyType,ElemType>>(c);
            this->setChild(1,cc) ;
            return  c;
        }
        boost::shared_ptr<HuffmanTree<KeyType,ElemType>>  leftChild(HuffmanTree<KeyType,ElemType>  & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc(new HuffmanTree(c));
            this->setChild(0,cc);
            boost::shared_ptr<HuffmanTree<KeyType,ElemType>> aa = boost::static_pointer_cast<HuffmanTree<KeyType,ElemType>>(cc);
            return  aa;
        }

        boost::shared_ptr<HuffmanTree<KeyType,ElemType>>  rightChild(HuffmanTree<KeyType,ElemType>  & c){
            boost::shared_ptr<TreeNode<KeyType,ElemType>> cc(new HuffmanTree(c));
            this->setChild(1,cc) ;
            boost::shared_ptr<HuffmanTree<KeyType,ElemType>> aa = boost::static_pointer_cast<HuffmanTree<KeyType,ElemType>>(cc);
            return  aa;
        }


    private:
        std::vector<boost::shared_ptr<HuffmanTree<KeyType,ElemType>>> leaves_; //叶子结点集合

    };



}
#endif //SMARTDONGLIB_HUFFMANTREE_H
