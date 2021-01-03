#include <iostream>
#include <vector>
#include <structure/linearlist/linkList.cpp>

using namespace SmartDongLib;
using std::cout;
using std::endl;
Size main() {
    LinkList<Size> linklist1;
    linklist1.data=1;
    LinkListUtil<Size>::listInsert(linklist1, 1, 3);
    LinkListUtil<Size>::listInsert(linklist1, 0, 4);
    LinkListUtil<Size>::listAppend(linklist1, 92);
    LinkListUtil<Size>::listDelete(linklist1, 2);
    LinkListUtil<Size>::listDelete(linklist1, 0);
    LinkListUtil<Size>::listAppend(linklist1, 93);
    Size len =LinkListUtil<Size>::listLenth(linklist1);
    //-------------------------------
    LinkList<Size> s;
    s.data=1;
    LinkListUtil<Size>::listInsert(s,1,3);
    LinkListUtil<Size>::listInsert(s,0,4);
    LinkListUtil<Size>::listAppend(s,92);
    LinkListUtil<Size>::listDelete(s,2);
    LinkListUtil<Size>::listDelete(s,0);
    LinkListUtil<Size>::listAppend(s,93);
    LinkListUtil<Size>::listMerge(linklist1,s, true);
    Size len2 =LinkListUtil<Size>::listLenth(s);
    //此时把 s 链表的Free 掉 那么Linklist1 也就废了
    cout << len << endl
         << LinkListUtil<Size>::listGet(linklist1, len) << endl
         << LinkListUtil<Size>::listGet(linklist1, 0) << endl;
    return 0;
}
