//
// Created by hu on 2020/8/6.
//

#include <iostream>
#include "sdstructure/linearlist/SString.cpp"
using namespace std;
using namespace SmartDongLib;
Size main(){
    SString mainstr("acabaabaabcacaabc");
    SString substr("abaabcac");//-1   0   -1   1   0   2   -1   1
    SString target("ijn");
    Size next[substr.length()];
    substr.getnext(next);
    for (Size i :next){
        cout<<i<<"   ";
    }


    Size index= mainstr.indexKMP(substr);
    Size index2=mainstr.index(substr);
    cout<<endl<<index;
    cout<<endl<<index2;
    mainstr.replace(substr,target);
    cout<<endl<<mainstr.get();

    SString asbbefg("asbbbefg");
    SString aubeg("aubbeg");
    SString ret=asbbefg.maxCommonSubstr(asbbefg);
    cout<<"\n"<<ret;
}