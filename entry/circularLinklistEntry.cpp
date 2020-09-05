//
// Created by hu on 2020/8/3.
//
#include <iostream>
#include <vector>
#include <sdstructure/linearlist/circularLinkedlist.cpp>

using namespace SmartDongLib;
using std::cout;
using std::endl;
int listmain();
int listmain(int);

int main(){
   listmain(1);
}
//int listmain() {
//    boost::shared_ptr<circularLinkedlist<int>> linklist1 (new circularLinkedlist<int>);
//    linklist1->data=1;
//    circularLinklistUtil<int> cLinklistUtil;
//
//    cLinklistUtil.listInsert(linklist1, 1, 3);
//    cLinklistUtil.listInsert(linklist1, 0, 4);
//    cLinklistUtil.listAppend(linklist1, 92);
//    cLinklistUtil.listDelete(linklist1, 2);
//    cLinklistUtil.listDelete(linklist1, 0);
//    cLinklistUtil.listAppend(linklist1, 93);
//    int len =cLinklistUtil.listLenth(linklist1);
//    //-------------------------------
//    boost::shared_ptr<circularLinkedlist<int>> s (new circularLinkedlist<int>);
//    s->data=1;
//    cLinklistUtil.listInsert(s,1,3);
//    cLinklistUtil.listInsert(s,0,4);
//    cLinklistUtil.listAppend(s,92);
//    cLinklistUtil.listDelete(s,2);
//    cLinklistUtil.listDelete(s,0);
//    cLinklistUtil.listAppend(s,93);
//    cLinklistUtil.listMerge(linklist1,s, true);
//    int len2 =cLinklistUtil.listLenth(s);
//    //此时把 s 链表的Free 掉 那么Linklist1 也就废了
//    cout << len << endl
//         << cLinklistUtil.listGet(linklist1, len) << endl
//         << cLinklistUtil.listGet(linklist1, 0) << endl;
//    return 0;
//}

int listmain(int pppppppp) {
    boost::shared_ptr<circularLinkedlist<int> > linklist1(new circularLinkedlist<int>);

    linklist1->data=1;
    linklist1->tocircularLinkedlist();
    circularLinklistUtil<int> cLinklistUtil;

    cLinklistUtil.listInsert(linklist1, 1, 3);
    cLinklistUtil.listInsert(linklist1, 0, 4);
    cLinklistUtil.listAppend(linklist1, 92);
    cLinklistUtil.listDelete(linklist1, 2);
    cLinklistUtil.listDelete(linklist1, 0);
    cLinklistUtil.listAppend(linklist1, 93);
    int len =cLinklistUtil.listLenth(linklist1);
    //-------------------------------
    boost::shared_ptr<circularLinkedlist<int> > s(new circularLinkedlist<int>);
    s->data=1;
    s->tocircularLinkedlist();
    cLinklistUtil.listInsert(s,1,3);
    cLinklistUtil.listInsert(s,0,4);
    cLinklistUtil.listAppend(s,92);
    cLinklistUtil.listDelete(s,2);
    cLinklistUtil.listDelete(s,0);
    cLinklistUtil.listAppend(s,93);
    cLinklistUtil.listMerge(linklist1,s, true);
    int len2 =cLinklistUtil.listLenth(s);
    //此时把 s 链表的Free 掉 那么Linklist1 也就废了
    cout << len << endl
         << cLinklistUtil.listGet(linklist1, len) << endl
         << cLinklistUtil.listGet(linklist1, 0) << endl;
    return 0;
}

