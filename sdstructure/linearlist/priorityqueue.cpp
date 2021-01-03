//
// Created by Administrator on 2021/1/3.
//

#include "priorityqueue.h"
template<class ElemType>
SmartDongLib::PriorityQueue<ElemType>::PriorityQueue(int maxpriority)
:maxPriority_(maxpriority){
    queues_.resize(maxPriority_);
}

template<class ElemType>
void SmartDongLib::PriorityQueue<ElemType>::resizeMaxPriority(int newMaxPriority) {
    maxPriority_=newMaxPriority;
    queues_.resize(maxPriority_);
}

template<class ElemType>
bool SmartDongLib::PriorityQueue<ElemType>::isEmpty() {
    bool isEmpty= true;
    for (int i = 0; i < maxPriority_; ++i) {
        isEmpty = isEmpty && queues_[i].empty();
    }
    return  isEmpty;
}

template<class ElemType>
int SmartDongLib::PriorityQueue<ElemType>::size() {

    int retSize = 0;
    for (int i = 0; i < maxPriority_; ++i) {
        retSize  += queues_[i].size();
    }
    return  retSize;
}

template<class ElemType>
ElemType SmartDongLib::PriorityQueue<ElemType>::top() {
    ElemType nullElemType;
    for (int i = maxPriority_-1 ; i >= 0 ; --i) {
        if (!queues_[i].empty()){
            return queues_[i].front();
        }
    }
    return nullElemType;
}

template<class ElemType>
ElemType SmartDongLib::PriorityQueue<ElemType>::pop() {
    ElemType nullElemType;
    for (int i = maxPriority_-1 ; i >= 0 ; --i) {
        if (!queues_[i].empty()){
            ElemType ret =  queues_[i].front() ;
            queues_[i].pop();
            return ret;
        }
    }
    return nullElemType;
}

template<class ElemType>
void SmartDongLib::PriorityQueue<ElemType>::push(ElemType elem, int priority) {
    queues_[priority].push(elem);
}

template<class ElemType>
ElemType SmartDongLib::PriorityQueue<ElemType>::back() {
    ElemType nullElemType;
    for (int i = 0 ; i < maxPriority_ ; ++i) {
        if (!queues_[i].empty()){
            return queues_[i].back();
        }
    }
    return nullElemType;
}

template<class ElemType>
std::queue<ElemType> SmartDongLib::PriorityQueue<ElemType>::getQueueByPriority(int priority) {
    return  queues_[priority];
}
