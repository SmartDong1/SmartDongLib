//
// Created by Administrator on 2020/12/26.
//

#include <iostream>
#include <vector>
#include <sdstructure/linearlist/SkipList.cpp>

using namespace SmartDongLib;
using std::cout;
using std::endl;
int main(){
    boost::shared_ptr< LinkList<Size>> linklist1 (new  LinkList<Size>);
//    linklist1->data=1;
    LinkListUtil<Size> linkListUtil;
    linkListUtil.listOrderInsert(linklist1, 100);
    linkListUtil.listOrderInsert(linklist1,  3);
    linkListUtil.listOrderInsert(linklist1, 4);
    linkListUtil.listOrderInsert(linklist1, 92);
    linkListUtil.listOrderInsert(linklist1, 2);
    linkListUtil.listOrderInsert(linklist1, 0);
    linkListUtil.listOrderInsert(linklist1, 23);
    linkListUtil.listOrderInsert(linklist1, 53);
    linkListUtil.listOrderInsert(linklist1, 43);
    linkListUtil.listOrderInsert(linklist1, 93);

    SkipList<int> skipList(3);
    skipList.dataLinklist( linklist1);
    skipList.rebuildIndex(0);
    skipList.removeByElem(93);
    skipList.insertElem(93);
    return  0 ;
}