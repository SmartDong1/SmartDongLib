//
// Created by Administrator on 2021/1/3.
//

#include<iostream>
#include "priorityqueue.cpp"


using namespace std;
using namespace SmartDongLib;
int main(){

    PriorityQueue<double> queues(6);
    queues.push(0);
    queues.push(0.1);

    queues.push(3,3);
    queues.push(3.1,3);
    queues.push(3.2,3);
    queues.push(3.3,3);
    queues.push(3.3,3);
    queues.push(5.0,5);
    queues.push(5.2,5);
    queues.push(5.4,5);
    queues.push(5.5,5);
    queues.push(5.6,5);
    queues.push(5.7,5);
    queues.push(5.8,5);
    queues.resizeMaxPriority(7);
    std::queue<double> test=queues.getQueueByPriority(5);
    test.push(0);
    test.push(0.1);
    queues.push(6,6);
    cout<<"isEmpty"<<queues.isEmpty()<<"top:"<<queues.top()<<"back:"<<queues.back()<<endl;
     for (int i = 0; i < queues.size(); ) {
        cout<<queues.pop()<<"\t";
    }
    return  0;
}