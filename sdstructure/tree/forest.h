//
// Created by Administrator on 2020/9/1.
//

#ifndef SMARTDONGLIB_FOREST_H
#define SMARTDONGLIB_FOREST_H
#include <vector>
#include <boost/shared_ptr.hpp>
#include <tree/tree.h>
namespace SmartDongLib {
    class ForestRunTimeException: public std::runtime_error{
    public:
        ForestRunTimeException(): std::runtime_error("Forest runtime_error"){}
        explicit ForestRunTimeException(const std::string& _arg): std::runtime_error("Forest runtime_error" + _arg){}

    };
    template<class KeyType,class ElemType >
    class Forest:public boost::enable_shared_from_this<Forest <KeyType,ElemType>> {
    public:
        Forest()=default;
        Forest(std::vector<boost::shared_ptr<TreeNode<KeyType,ElemType>>> t){
            trees_=t;
            if (!checkTreeNode()){
                throw ForestRunTimeException("these node is not a root node");
            }
        }
        boost::shared_ptr<Forest> insertTree(boost::shared_ptr<TreeNode<KeyType,ElemType>> t){
            if (t ==NULL || t->parent()){
                throw ForestRunTimeException("The node is not a root node");
            }
            trees_.push_back(t);
            return getThis();
        }
        boost::shared_ptr<Forest> deleteTree(KeyType key){
            for(typename std::vector<boost::shared_ptr<TreeNode<KeyType,ElemType>>>::iterator iter=trees_.begin(); iter!=trees_.end(); )
            {
                if (key == (*iter) ->key()){
                    trees_.erase(iter);
                } else{
                    iter++;
                }
            }
            return getThis();
        }
        boost::shared_ptr<TreeNode<KeyType,ElemType>> getTree(int i ){
            if (i >=trees_.size())
                throw TreeRunTimeException("out of range exception");
            return trees_[i];
        }
        int getTreenum(){
            return  trees_.size();
        }
        boost::shared_ptr<Forest> getThis()
        {
            return this->shared_from_this();
        }
    private:
        bool checkTreeNode(){
            for (int i = 0; i < trees_.size(); ++i) {
                if (trees_[i] == NULL || trees_[i] ->parent()){
                    return false;
                }
            }
            return true;
        }
        std::vector<boost::shared_ptr<TreeNode<KeyType,ElemType>>> trees_;
    };

}
#endif //SMARTDONGLIB_FOREST_H
