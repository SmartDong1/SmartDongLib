//
// Created by hu on 2020/8/6.
//

#include <iostream>
#include "sdstructure/linearlist/SString.cpp"
using namespace std;
using namespace SmartDongLib;
int main(){
    SString mainstr("acabaabaabcacaabc");
    SString substr("abaabcac");//-1   0   -1   1   0   2   -1   1
    SString target("ijn");
    int next[substr.length()];
    substr.getnext(next);
    for (int i :next){
        cout<<i<<"   ";
    }


    int index= mainstr.indexKMP(substr);
    int index2=mainstr.index(substr);
    cout<<endl<<index;
    cout<<endl<<index2;
    mainstr.replace(substr,target);
    cout<<endl<<mainstr.get();

    SString asbbefg("asbbbefg");
    SString aubeg("aubbeg");
    SString ret=asbbefg.maxCommonSubstr(asbbefg);
    cout<<"\n"<<ret;
}