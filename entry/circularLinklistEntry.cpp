//
// Created by hu on 2020/8/3.
//
#include <iostream>
#include <vector>
#include <sdstructure/linearlist/circularLinkedlist.cpp>

using namespace SmartDongLib;
using std::cout;
using std::endl;
Size listmain();
Size listmain(Size);

Size main(){
   listmain(1);
}
//Size listmain() {
//    boost::shared_ptr<circularLinkedlist<Size>> linklist1 (new circularLinkedlist<Size>);
//    linklist1->data=1;
//    circularLinklistUtil<Size> cLinklistUtil;
//
//    cLinklistUtil.listInsert(linklist1, 1, 3);
//    cLinklistUtil.listInsert(linklist1, 0, 4);
//    cLinklistUtil.listAppend(linklist1, 92);
//    cLinklistUtil.listDelete(linklist1, 2);
//    cLinklistUtil.listDelete(linklist1, 0);
//    cLinklistUtil.listAppend(linklist1, 93);
//    Size len =cLinklistUtil.listLenth(linklist1);
//    //-------------------------------
//    boost::shared_ptr<circularLinkedlist<Size>> s (new circularLinkedlist<Size>);
//    s->data=1;
//    cLinklistUtil.listInsert(s,1,3);
//    cLinklistUtil.listInsert(s,0,4);
//    cLinklistUtil.listAppend(s,92);
//    cLinklistUtil.listDelete(s,2);
//    cLinklistUtil.listDelete(s,0);
//    cLinklistUtil.listAppend(s,93);
//    cLinklistUtil.listMerge(linklist1,s, true);
//    Size len2 =cLinklistUtil.listLenth(s);
//    //此时把 s 链表的Free 掉 那么Linklist1 也就废了
//    cout << len << endl
//         << cLinklistUtil.listGet(linklist1, len) << endl
//         << cLinklistUtil.listGet(linklist1, 0) << endl;
//    return 0;
//}

Size listmain(Size pppppppp) {
    boost::shared_ptr<circularLinkedlist<Size> > linklist1(new circularLinkedlist<Size>);

    linklist1->data=1;
    linklist1->tocircularLinkedlist();
    circularLinklistUtil<Size> cLinklistUtil;

    cLinklistUtil.listInsert(linklist1, 1, 3);
    cLinklistUtil.listInsert(linklist1, 0, 4);
    cLinklistUtil.listAppend(linklist1, 92);
    cLinklistUtil.listDelete(linklist1, 2);
    cLinklistUtil.listDelete(linklist1, 0);
    cLinklistUtil.listAppend(linklist1, 93);
    Size len =cLinklistUtil.listLenth(linklist1);
    //-------------------------------
    boost::shared_ptr<circularLinkedlist<Size> > s(new circularLinkedlist<Size>);
    s->data=1;
    s->tocircularLinkedlist();
    cLinklistUtil.listInsert(s,1,3);
    cLinklistUtil.listInsert(s,0,4);
    cLinklistUtil.listAppend(s,92);
    cLinklistUtil.listDelete(s,2);
    cLinklistUtil.listDelete(s,0);
    cLinklistUtil.listAppend(s,93);
    cLinklistUtil.listMerge(linklist1,s, true);
    Size len2 =cLinklistUtil.listLenth(s);
    //此时把 s 链表的Free 掉 那么Linklist1 也就废了
    cout << len << endl
         << cLinklistUtil.listGet(linklist1, len) << endl
         << cLinklistUtil.listGet(linklist1, 0) << endl;
    return 0;
}

