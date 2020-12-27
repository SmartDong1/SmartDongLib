//
// Created by Administrator on 2020/12/22.
//

#include "SkipList.h"
//region IndexStruct::function
template<class ElemType>
ElemType SmartDongLib::SkipList<ElemType>::IndexStruct::position() const {
    return position_;
}

template<class ElemType>
void SmartDongLib::SkipList<ElemType>::IndexStruct::position(ElemType position) {
    position_ = position;
}


//template<class ElemType>
//void SmartDongLib::SkipList<ElemType>::IndexStruct::pointer(const boost::shared_ptr<LinkList<ElemType>> &pointer) {
//    pointer_ = pointer;
//}

template<class ElemType>
bool SmartDongLib::SkipList<ElemType>::IndexStruct::operator<(SmartDongLib::SkipList<ElemType>::IndexStruct a) {
    return this->position() < a.position();
}

template<class ElemType>
bool SmartDongLib::SkipList<ElemType>::IndexStruct::operator==(SmartDongLib::SkipList<ElemType>::IndexStruct a) {
    return this->position()== a.position();
}

template<class ElemType>
bool SmartDongLib::SkipList<ElemType>::IndexStruct::operator>(SmartDongLib::SkipList<ElemType>::IndexStruct a) {
    return this->position() > a.position();
}

template<class ElemType>
SmartDongLib::SkipList<ElemType>::IndexStruct::IndexStruct(ElemType position,
                                                           const boost::shared_ptr<LinkList<ElemType>> &pointer)
        :position_(position), pointer_(pointer) {}

template<class ElemType>
typename SmartDongLib::SkipList<ElemType>::IndexStruct &
SmartDongLib::SkipList<ElemType>::IndexStruct::operator=(const SmartDongLib::SkipList<ElemType>::IndexStruct &a) {
    if ( this == &a )
        return *this;
    position_= a.position_;
    pointer_= a.pointer_;
    return *this;
}

template<class ElemType>
const typename SmartDongLib::SkipList<ElemType>::IndexStruct::U &SmartDongLib::SkipList<ElemType>::IndexStruct::pointer() const {
    return pointer_;
}

template<class ElemType>
void SmartDongLib::SkipList<ElemType>::IndexStruct::pointer(const SmartDongLib::SkipList<ElemType>::IndexStruct::U &pointer) {
    pointer_ = pointer;
}
//endregion

/**
 * <p>数据链表元素对应层级的索引链表位置
 * @tparam ElemType
 * @param indexlevel   索引层级
 * @param dataPosition 数据有序链表查询位置
 * @return  待查询位置对应层级的索引链表位置，0代表从0位置开始查
 */
template<class ElemType>
int SmartDongLib::SkipList<ElemType>::findIndexListPosition(int indexlevel, ElemType dataPosition,boost::shared_ptr<LinkList<IndexStruct>>& idxlist) {
    int idxpos =0;
    idxlist=indexLinklist_[indexlevel];
    while (idxlist->next && idxlist->next->data.position() < dataPosition){
        idxpos++;
        idxlist=idxlist->next;
    }
    return idxpos;
}
/**
 * <p>从第数据链表的startElem开始重建立链表
 * @tparam ElemType
 * @param startElem
 */
template<class ElemType>
void SmartDongLib::SkipList<ElemType>::rebuildIndex(ElemType startElem) {
    //获取数据总数
    int datalistsize = dataListUtil_.listLenth(dataLinklist_);
    //要重建数据索引的个数
//    int rebuldDataCount =  datalistsize - startIndex +1;
    //索引层应建立索引的节点数
    int indexlevelCount = datalistsize / skipstep_;
    int indexlevel=0;
    while (indexlevelCount !=0){
        //如果层级要大于 indexLinklist_.size(),需要扩充indexList，否则再原来的基础上修改，还需要判断是不是第0索引层
        if(indexlevel >= indexLinklist_.size()){
            boost::shared_ptr<LinkList<IndexStruct>> currentIndexList (new LinkList<IndexStruct>());
            //头指针也进行关联
            if (indexlevel ==0){
                currentIndexList->data.pointer_.dataPointer = dataLinklist_;
//                currentIndexList->data.position_ =dataLinklist_->data;
            }else{
                currentIndexList->data.pointer_.indexPointer = indexLinklist_[indexlevel-1];
//              currentIndexList->data.position_ =indexLinklist_[indexlevel-1]->data.position_;

            }
            bool  isfirst = true;
            boost::shared_ptr<LinkList<ElemType>> linkdataNode;
            boost::shared_ptr<LinkList<IndexStruct>>  linkindexNode;
            //扩展 indexlevel 层的后面的索引
            for (int i = 1; i <=indexlevelCount; ++i) {
//                boost::shared_ptr<LinkList<IndexStruct>> currentIndexNode (new LinkList<IndexStruct>);
                IndexStruct currentIndexNode;
                //优化：第0索引层指向data数据，其他指向下层索引数据，第一次从头节点确定指向的位置，之后再此基础上在+上skipstep_
                if (indexlevel == 0) {
                    if (isfirst){
                        linkdataNode = dataListUtil_.listGetNode(dataLinklist_,i  * skipstep_);
                        isfirst= false;
                    }else{
                        linkdataNode = dataListUtil_.listGetNode(linkdataNode, skipstep_);
                    }
                    currentIndexNode.position_ =linkdataNode->data;
                    currentIndexNode.pointer_.dataPointer = linkdataNode;
                }else{
                    if (isfirst){
                        linkindexNode =indexListUtil_.listGetNode(indexLinklist_[indexlevel - 1], i * skipstep_);
                        isfirst= false;
                    }else{
                        linkindexNode =indexListUtil_.listGetNode(linkindexNode,  skipstep_);
                    }
                    currentIndexNode.position_ =linkindexNode->data.position_;
                    currentIndexNode.pointer_.indexPointer = linkindexNode;
                }
                indexListUtil_.listOrderInsert(currentIndexList,currentIndexNode);
            }
            indexLinklist_.push_back(currentIndexList);
        } else{
            boost::shared_ptr<LinkList<IndexStruct>> currentIndexList=indexLinklist_[indexlevel];
            //找到startElem前一个元素的位置
            boost::shared_ptr<LinkList<IndexStruct>>  startIndexNode;
            int startIdx = findIndexListPosition(indexlevel, startElem,startIndexNode);
            //重键startIndexNode之后的索引
            startIndexNode->next = NULL;
            boost::shared_ptr<LinkList<ElemType>> linkdataNode;
            boost::shared_ptr<LinkList<IndexStruct>>  linkindexNode;
            bool  isfirst = true;
            //第indexlevel层从startIdx开始重建索引
            for (int i = startIdx+1; i <=indexlevelCount; ++i){
//                boost::shared_ptr<LinkList<IndexStruct>> currentIndexNode (new LinkList<IndexStruct>);
//                LinkList<IndexStruct> currentIndexNode;
                 IndexStruct  currentIndexNode;
                //优化：第0索引层指向data数据，其他指向下层索引数据，第一次从头节点确定指向的位置，之后再此基础上在+上skipstep_
                if (indexlevel == 0) {
                    if (isfirst){
                        linkdataNode = dataListUtil_.listGetNode(dataLinklist_,i  * skipstep_);
                        isfirst= false;
                    }else{
                        linkdataNode = dataListUtil_.listGetNode(linkdataNode, skipstep_);
                    }
                    currentIndexNode.position_ =linkdataNode->data;
                    currentIndexNode.pointer_.dataPointer = linkdataNode;
                }else{
                    if (isfirst){
                        linkindexNode =indexListUtil_.listGetNode(indexLinklist_[indexlevel - 1], i * skipstep_);
                        isfirst= false;
                    }else{
                        linkindexNode =indexListUtil_.listGetNode(linkindexNode,  skipstep_);
                    }
                    currentIndexNode.position_ =linkindexNode->data.position_;
                    currentIndexNode.pointer_.indexPointer = linkindexNode;
                }
                indexListUtil_.listOrderInsert(currentIndexList,currentIndexNode);
            }

        }
        indexlevel++;
        indexlevelCount /= skipstep_;
    }

}
/**
 * <p>根据位置删除元素并重建索引
 * @tparam ElemType
 * @param pos
 */
template<class ElemType>
void SmartDongLib::SkipList<ElemType>::removeByPos(Size pos) {
    ElemType elem=dataListUtil_.listGet(dataLinklist_, pos);
    dataListUtil_.listDelete(dataLinklist_, pos);
    rebuildIndex(elem);
}
/**
 * <p>根据元素删除元素并重建索引
 * @tparam ElemType
 * @param e
 */
template<class ElemType>
void SmartDongLib::SkipList<ElemType>::removeByElem(ElemType e) {
    Size pos =findPosByElem(e);
//    removeByPos(pos);
    dataListUtil_.listDelete(dataLinklist_,pos);
    rebuildIndex(e);
}
/**
 * <p>插入元素并重建索引
 * @tparam ElemType
 * @param e
 */
template<class ElemType>
void SmartDongLib::SkipList<ElemType>::insertElem(ElemType e) {
    boost::shared_ptr<LinkList<ElemType>>  a=findDataNode(e, false);
    dataListUtil_.listOrderInsert(a,e);
    rebuildIndex(e);
}
/**
 * <p>根据元素寻找索引节点
 * @tparam ElemType
 * @param indexlevel 索引层级
 * @param dataPos    datalist中的位置
 * @return
 */
template<class ElemType>
boost::shared_ptr<SmartDongLib::LinkList<typename SmartDongLib::SkipList<ElemType>::IndexStruct> >
SmartDongLib::SkipList<ElemType>::findIndexNode(int indexlevel, ElemType dataPos) {
    int indexlistsize = indexLinklist_.size();
    if (indexlistsize == 0)
        return  NULL;
    boost::shared_ptr<LinkList<IndexStruct>> idxlist=indexLinklist_[indexlistsize-1];
    int currentIndexlevel = indexlistsize-1;
    while (currentIndexlevel >= indexlevel && currentIndexlevel >= 0){
        if ( idxlist->next!=NULL  && idxlist->next->data.position() <= dataPos ){
            //如果查在后面
            idxlist=idxlist->next;
        }else{
            //如果当前层确定了位置，就下一层直到第indexlevel结束
            if ( currentIndexlevel == indexlevel || currentIndexlevel == 0 ){
                return idxlist;
            }else{
                idxlist  = idxlist->data.pointer_.indexPointer;
                currentIndexlevel --;
            }
        }
    }
    return NULL;
}
/**
 * <p>根据elem寻找节点
 * @tparam ElemType
 * @param elem
 * @param isAccurate  是否精准匹配，当为否的时候，匹配最接近（大）的节点
 * @return
 */
template<class ElemType>
boost::shared_ptr<SmartDongLib::LinkList<ElemType>>SmartDongLib::SkipList<ElemType>::findDataNode(ElemType elem,bool isAccurate ) {
    boost::shared_ptr<LinkList<SkipList<ElemType>::IndexStruct>> indexNode=findIndexNode(0,elem);
    boost::shared_ptr<LinkList<ElemType>> dataNode  = indexNode->data.pointer_.dataPointer;
    while (dataNode->next && dataNode->next->data <= elem){
        dataNode=dataNode->next;
    }
    if (dataNode->data == elem || !isAccurate){
        return dataNode;
    } else{
        return NULL;
    }
}
/**
 * <p>根据元素寻找在datalinklist中的位置
 * @tparam ElemType
 * @param elem
 * @return 位找到是-1 ，头节点是第0个位置
 */
template<class ElemType>
int SmartDongLib::SkipList<ElemType>::findPosByElem(ElemType elem) {
    int indexlistsize = indexLinklist_.size();
    int currentIndexlevel = indexlistsize-1;
    boost::shared_ptr<LinkList<IndexStruct>> idxlist=indexLinklist_[currentIndexlevel];
    int pos = 0;
    while (currentIndexlevel >= 0){
        if ( idxlist->next  && idxlist->next->data.position() <= elem ){
            //如果查在后面
            idxlist=idxlist->next;
            pos =pos + std::pow(skipstep_,currentIndexlevel +1 );
        }else{
            //如果当前层确定了位置，就下一层直到第indexlevel结束
            if ( currentIndexlevel == 0 ){
                break;
            }else{
                idxlist  = idxlist->data.pointer_.indexPointer;
                currentIndexlevel --;
            }
        }
    }
    boost::shared_ptr<LinkList<ElemType>> dataNode = idxlist->data.pointer_.dataPointer;
    if (dataNode ->data == elem){
        return pos;
    } else{
        int rslt =dataListUtil_.listGetIndex(dataNode,elem);
        if (rslt == -1 )
            return  -1;
        else
            return  pos + dataListUtil_.listGetIndex(dataNode,elem);
    }
}

