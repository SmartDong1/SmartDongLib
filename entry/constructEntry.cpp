//
// Created by hu on 2020/8/23.
//

#include <iostream>
using namespace std;

class ConstructTest{
public:
    ConstructTest(){
        cout<<"default Constructor\n";
        dim_=0;
        base_= nullptr;
    };    //默认构造函数
    ~ConstructTest(){
        cout<<"Destructor:base "<<base_<<endl;
        delete base_;

    }
    ConstructTest(Size dim){
        cout<<"Constructor with param"<<endl;
        dim_=dim;
        base_ = new Size [dim];
        for (Size i = 0; i < dim_; ++i) {
            *(base_ + i) = 0;
        }
    }
    ConstructTest (const ConstructTest & a){
        cout<<"copy Constructor"<<endl;
        dim_= a.dim_;
        base_ = new Size [dim_];
        for (Size i = 0; i < dim_; ++i) {
            *(base_ + i) = *(a.base_+i);
        }
    }
    ConstructTest& operator =(const ConstructTest & a){
        cout<<"copy assign "<<endl;
        if ( this == &a )
            return *this;
        dim_= a.dim_;
        base_ = new Size [dim_];
        for (Size i = 0; i < dim_; ++i) {
            *(base_ + i) = *(a.base_+i);
        }
        return *this;
    }
    ConstructTest& operator =( ConstructTest && a)noexcept{
        cout<<"moving copy assign "<<endl;
        //避免自己移动自己
        if ( this == &a )
            return *this;
        delete base_;
        dim_ = a.dim_;
        base_ = a.base_;
        a.base_ = nullptr;
        return *this;
    }
    ConstructTest (ConstructTest && a) noexcept{
        cout<<"moving copy Constructor"<<endl;

        dim_ = a.dim_;
        base_ = a.base_;
        a.base_ = nullptr;
    }

public:
    Size  dim_;
    Size * base_;
};
ConstructTest square(ConstructTest para){
    ConstructTest ret(para.dim_);
    ret.base_ = new Size [para.dim_];
    for (Size i = 0; i < para.dim_; ++i) {
        *(ret.base_+i) = *(para.base_+i) * (*(para.base_+i));
    }
   // ConstructTest* rett=&ret;
    return  ret;
}

Size main(){
    ConstructTest c1(3);
    ConstructTest c2(c1);
    ConstructTest c4 ;
    c4=c2;
    cout<<"------------------------\n";
    ConstructTest c5 ;
    c5=square(c4);
    cout<<"------------------------\n";
    ConstructTest c6 = std::move(c5);
    cout<<"------------------------\n";
    ConstructTest c7;
    c7=ConstructTest();
    ConstructTest c8 = square(c7);
    ConstructTest c9 = ConstructTest();
    cout<<"<<<<<<finish >>>>>>>>\n";

}