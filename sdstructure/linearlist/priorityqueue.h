//
// Created by Administrator on 2021/1/3.
// 优先级队列,所有元素的优先级都必须小于 maxPriority_
//

#ifndef SMARTDONGLIB_PRIORITYQUEUE_H
#define SMARTDONGLIB_PRIORITYQUEUE_H
#include <queue>
#include <vector>
namespace SmartDongLib {
    template<class ElemType>
    class PriorityQueue {
    public:
        PriorityQueue(int maxpriority);
        void resizeMaxPriority(int maxPriority);
        bool isEmpty();
        int size();
        ElemType top();
        ElemType pop();
        ElemType back();
        void push(ElemType elem,int priority =0);
        std::queue<ElemType> getQueueByPriority(int priority);
     private:
        std::vector<std::queue<ElemType>> queues_;
        int maxPriority_ ; //优先级最高级
    };



}
#endif //SMARTDONGLIB_PRIORITYQUEUE_H
