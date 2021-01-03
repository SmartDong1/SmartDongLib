//
// Created by hu on 2020/8/21.
//


#include <iostream>
#include <generalList.cpp>
using namespace std;
using namespace SmartDongLib;
Size main(){
    boost::shared_ptr<generalList<char>> alist( new generalList<char>('a'));
    boost::shared_ptr<generalList<char>> dlist( new generalList<char>('d'));
    boost::shared_ptr<generalList<char>> flist( new generalList<char>('f'));
    boost::shared_ptr<generalList<char>> glist( new generalList<char>('g'));
    boost::shared_ptr<generalList<char>> hlist( new generalList<char>('h'));

    boost::shared_ptr<generalList<char>> blist( new generalList<char>());
    boost::shared_ptr<generalList<char>> zlist(new generalList<char>());
    alist->tail_ =flist;
    blist->elem.head_ = alist;
    blist->tail_=glist;
    dlist->tail_ = hlist;
    zlist->elem.head_=blist;
    zlist->tail_=dlist;
    /*
     *     z -> d ->h                           z -> b->g->d->h                   z ->g->d->h
     *     |                                    |    |                            |
     *     b -> g          =insertFirst(i)==>   i    a->f       =deleteFirst===>  b
     *     |                                                                      |
     *     a -> f                                                                 a->f
     *
     */
    char atom;
    generalList<char> * clist;
    boost::shared_ptr<generalList<char>> ilist( new generalList<char>('i'));
    zlist->insertFirst(ilist);  //((a,f),g),d,h
    zlist->deleteFirst();
    cout << zlist->prSize() << endl;
    cout << "ElemCount: "<<zlist->getElemCount() << endl;
    cout << "Depth: "<<zlist->getDepth() << endl;
    cout << "Length: "<<zlist->getLength() << endl;

    cout<<"finish";
}