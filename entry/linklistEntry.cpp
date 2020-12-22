//
// Created by hu on 2020/8/2.
//
#include <iostream>
#include <vector>
#include <sdstructure/linearlist/linkList.cpp>

using namespace SmartDongLib;
using std::cout;
using std::endl;
Size listmain();
Size boost_main();
Size add(Size &a){
    boost::shared_ptr<Size>  ba(&a);
    *ba += 2;
    return  *ba;
}
Size main(){

boost_main();
}
//Size listmain() {
//    LinkList<Size> linklist1;
//    linklist1.data=1;
//    LinkListUtil<Size>::listInsert(linklist1, 1, 3);
//    LinkListUtil<Size>::listInsert(linklist1, 0, 4);
//    LinkListUtil<Size>::listAppend(linklist1, 92);
//    LinkListUtil<Size>::listDelete(linklist1, 2);
//    LinkListUtil<Size>::listDelete(linklist1, 0);
//    LinkListUtil<Size>::listAppend(linklist1, 93);
//    Size len =LinkListUtil<Size>::listLenth(linklist1);
//    //-------------------------------
//    LinkList<Size> s;
//    s.data=1;
//    LinkListUtil<Size>::listInsert(s,1,3);
//    LinkListUtil<Size>::listInsert(s,0,4);
//    LinkListUtil<Size>::listAppend(s,92);
//    LinkListUtil<Size>::listDelete(s,2);
//    LinkListUtil<Size>::listDelete(s,0);
//    LinkListUtil<Size>::listAppend(s,93);
//    LinkListUtil<Size>::listMerge(linklist1,s, true);
//    Size len2 =LinkListUtil<Size>::listLenth(s);
//    //此时把 s 链表的Free 掉 那么Linklist1 也就废了
//    cout << len << endl
//         << LinkListUtil<Size>::listGet(linklist1, len) << endl
//         << LinkListUtil<Size>::listGet(linklist1, 0) << endl;
//    return 0;
//}

Size boost_main() {
    boost::shared_ptr< LinkList<Size>> linklist1 (new  LinkList<Size>);
    linklist1->data=1;
    cout<<"address"<<&linklist1<<endl;
    LinkListUtil<Size> linkListUtil;
    linkListUtil.listInsert(linklist1, 1, 3);
    linkListUtil.listInsert(linklist1, 0, 4);
    linkListUtil.listAppend(linklist1, 92);
    linkListUtil.listDelete(linklist1, 2);
    linkListUtil.listDelete(linklist1, 0);
    linkListUtil.listAppend(linklist1, 93);
    Size len =linkListUtil.listLenth(linklist1);
    //-------------------------------
    boost::shared_ptr< LinkList<Size>> s (new  LinkList<Size>);
    s->data=1;
    linkListUtil.listInsert(s, 1, 3);
    linkListUtil.listInsert(s, 0, 4);
    linkListUtil.listAppend(s, 92);
    linkListUtil.listDelete(s, 2);
    linkListUtil.listDelete(s, 0);
    linkListUtil.listAppend(s, 93);
    linkListUtil.listMerge(linklist1, s, false);
    Size len2 =linkListUtil.listLenth(s);
    //此时把 s 链表的Free 掉 那么Linklist1 也就废了
    cout << len << endl
         << linkListUtil.listGet(linklist1, len) << endl
         << linkListUtil.listGet(linklist1, 0) << endl;
    boost::shared_ptr< LinkList<int>> linklistOrder (new  LinkList<Size>);
    linkListUtil.listOrderInsert(linklistOrder,5);
    linkListUtil.listOrderInsert(linklistOrder,15);
    linkListUtil.listOrderInsert(linklistOrder,5);
    linkListUtil.listOrderInsert(linklistOrder,25);
    linkListUtil.listOrderInsert(linklistOrder,3);
    linkListUtil.listOrderInsert(linklistOrder,7);
    linkListUtil.listOrderInsert(linklistOrder,1);


    return 0;
}
