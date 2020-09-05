#include <iostream>
#include <vector>
#include <structure/linearlist/linkList.cpp>

using namespace SmartDongLib;
using std::cout;
using std::endl;
int main() {
    LinkList<int> linklist1;
    linklist1.data=1;
    LinkListUtil<int>::listInsert(linklist1, 1, 3);
    LinkListUtil<int>::listInsert(linklist1, 0, 4);
    LinkListUtil<int>::listAppend(linklist1, 92);
    LinkListUtil<int>::listDelete(linklist1, 2);
    LinkListUtil<int>::listDelete(linklist1, 0);
    LinkListUtil<int>::listAppend(linklist1, 93);
    int len =LinkListUtil<int>::listLenth(linklist1);
    //-------------------------------
    LinkList<int> s;
    s.data=1;
    LinkListUtil<int>::listInsert(s,1,3);
    LinkListUtil<int>::listInsert(s,0,4);
    LinkListUtil<int>::listAppend(s,92);
    LinkListUtil<int>::listDelete(s,2);
    LinkListUtil<int>::listDelete(s,0);
    LinkListUtil<int>::listAppend(s,93);
    LinkListUtil<int>::listMerge(linklist1,s, true);
    int len2 =LinkListUtil<int>::listLenth(s);
    //此时把 s 链表的Free 掉 那么Linklist1 也就废了
    cout << len << endl
         << LinkListUtil<int>::listGet(linklist1, len) << endl
         << LinkListUtil<int>::listGet(linklist1, 0) << endl;
    return 0;
}
