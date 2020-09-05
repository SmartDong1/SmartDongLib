//
// Created by hu on 2020/8/2.
//
#include <iostream>
#include <vector>
#include <sdstructure/linearlist/linkList.cpp>

using namespace SmartDongLib;
using std::cout;
using std::endl;
int listmain();
int boost_main();
int add(int &a){
    boost::shared_ptr<int>  ba(&a);
    *ba += 2;
    return  *ba;
}
int main(){

boost_main();
}
//int listmain() {
//    LinkList<int> linklist1;
//    linklist1.data=1;
//    LinkListUtil<int>::listInsert(linklist1, 1, 3);
//    LinkListUtil<int>::listInsert(linklist1, 0, 4);
//    LinkListUtil<int>::listAppend(linklist1, 92);
//    LinkListUtil<int>::listDelete(linklist1, 2);
//    LinkListUtil<int>::listDelete(linklist1, 0);
//    LinkListUtil<int>::listAppend(linklist1, 93);
//    int len =LinkListUtil<int>::listLenth(linklist1);
//    //-------------------------------
//    LinkList<int> s;
//    s.data=1;
//    LinkListUtil<int>::listInsert(s,1,3);
//    LinkListUtil<int>::listInsert(s,0,4);
//    LinkListUtil<int>::listAppend(s,92);
//    LinkListUtil<int>::listDelete(s,2);
//    LinkListUtil<int>::listDelete(s,0);
//    LinkListUtil<int>::listAppend(s,93);
//    LinkListUtil<int>::listMerge(linklist1,s, true);
//    int len2 =LinkListUtil<int>::listLenth(s);
//    //此时把 s 链表的Free 掉 那么Linklist1 也就废了
//    cout << len << endl
//         << LinkListUtil<int>::listGet(linklist1, len) << endl
//         << LinkListUtil<int>::listGet(linklist1, 0) << endl;
//    return 0;
//}

int boost_main() {
    boost::shared_ptr< LinkList<int>> linklist1 (new  LinkList<int>);
    linklist1->data=1;
    cout<<"address"<<&linklist1<<endl;
    LinkListUtil<int> linkListUtil;
    linkListUtil.listInsert(linklist1, 1, 3);
    linkListUtil.listInsert(linklist1, 0, 4);
    linkListUtil.listAppend(linklist1, 92);
    linkListUtil.listDelete(linklist1, 2);
    linkListUtil.listDelete(linklist1, 0);
    linkListUtil.listAppend(linklist1, 93);
    int len =linkListUtil.listLenth(linklist1);
    //-------------------------------
    boost::shared_ptr< LinkList<int>> s (new  LinkList<int>);
    s->data=1;
    linkListUtil.listInsert(s, 1, 3);
    linkListUtil.listInsert(s, 0, 4);
    linkListUtil.listAppend(s, 92);
    linkListUtil.listDelete(s, 2);
    linkListUtil.listDelete(s, 0);
    linkListUtil.listAppend(s, 93);
    linkListUtil.listMerge(linklist1, s, false);
    int len2 =linkListUtil.listLenth(s);
    //此时把 s 链表的Free 掉 那么Linklist1 也就废了
    cout << len << endl
         << linkListUtil.listGet(linklist1, len) << endl
         << linkListUtil.listGet(linklist1, 0) << endl;
    return 0;
}
