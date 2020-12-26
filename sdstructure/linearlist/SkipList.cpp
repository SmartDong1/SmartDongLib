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
int SmartDongLib::SkipList<ElemType>::findIndexListPosition(int indexlevel, ElemType dataPosition) {
    int idxpos =0;
    boost::shared_ptr<LinkList<IndexStruct>> idxlist=indexLinklist_[indexlevel];
    while (idxlist->next && idxlist->next->data.position() < dataPosition){
        idxpos++;
        idxlist=idxlist->next;
    }
    return idxpos;
}
/**
 * <p>从第数据链表的startIndex开始重建立链表
 * @tparam ElemType
 * @param startIndex
 */
template<class ElemType>
void SmartDongLib::SkipList<ElemType>::rebuildIndex(ElemType startIndex) {

    //获取索引表总数
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
            for (int i = 1; i <=indexlevelCount; ++i) {
//                boost::shared_ptr<LinkList<IndexStruct>> currentIndexNode (new LinkList<IndexStruct>);
                IndexStruct currentIndexNode;
//                currentIndexNode->data.position_ =  i*std::pow(skipstep_,indexlevel+1);
                //第0索引层指向data数据，其他指向下层索引数据
                if (indexlevel == 0) {

                    boost::shared_ptr<LinkList<ElemType>> linkNode = dataListUtil_.listGetNode(dataLinklist_,
                                                                                               i  * skipstep_);
                    currentIndexNode.position_ =linkNode->data;
                    currentIndexNode.pointer_.dataPointer = linkNode;
                }else{
                    boost::shared_ptr<LinkList<IndexStruct>>  linkNode =indexListUtil_.listGetNode(indexLinklist_[indexlevel-1], i* skipstep_);
                    currentIndexNode.position_ =linkNode->data.position_;
                    currentIndexNode.pointer_.indexPointer = linkNode;
                }
                indexListUtil_.listOrderInsert(currentIndexList,currentIndexNode);
            }
            indexLinklist_.push_back(currentIndexList);
        } else{
            boost::shared_ptr<LinkList<IndexStruct>> currentIndexList=indexLinklist_[indexlevel];
            int startIdx = findIndexListPosition(indexlevel,startIndex);
            boost::shared_ptr<LinkList<IndexStruct>>  startIndexNode=indexListUtil_.listGetNode(indexLinklist_[indexlevel],startIdx);
            startIndexNode->next = NULL;
            //第indexlevel层从startIdx开始重建索引
            for (int i = startIdx+1; i <=indexlevelCount; ++i){
//                boost::shared_ptr<LinkList<IndexStruct>> currentIndexNode (new LinkList<IndexStruct>);
//                LinkList<IndexStruct> currentIndexNode;
                 IndexStruct  currentIndexNode;
//                currentIndexNode.data.position_ =  i*std::pow(skipstep_,indexlevel+1);
                if (indexlevel == 0) {
                    boost::shared_ptr<LinkList<ElemType>> linkNode = dataListUtil_.listGetNode(dataLinklist_,
                                                                                               i  * skipstep_);
                    currentIndexNode.position_ =linkNode->data;
                    currentIndexNode.pointer_.dataPointer = linkNode;
                }else{
                    boost::shared_ptr<LinkList<IndexStruct>>  linkNode =indexListUtil_.listGetNode(indexLinklist_[indexlevel-1], i* skipstep_);
                    currentIndexNode.position_ =linkNode->data.position_;
                    currentIndexNode.pointer_.indexPointer = linkNode;
                }
                indexListUtil_.listOrderInsert(currentIndexList,currentIndexNode);
            }

        }
        indexlevel++;
        indexlevelCount /= skipstep_;
    }

}

template<class ElemType>
void SmartDongLib::SkipList<ElemType>::removeByPos(Size e) {
    ElemType elem=dataListUtil_.listGet(dataLinklist_,e);
    dataListUtil_.listDelete(dataLinklist_,e);
    rebuildIndex(elem);
}

template<class ElemType>
void SmartDongLib::SkipList<ElemType>::removeByElem(ElemType e) {
    Size pos = dataListUtil_.listGetIndex(dataLinklist_,e);
    removeByPos(pos);
}

template<class ElemType>
void SmartDongLib::SkipList<ElemType>::insertElem(ElemType e) {
    dataListUtil_.listOrderInsert(dataLinklist_,e);
    rebuildIndex(e);
}

