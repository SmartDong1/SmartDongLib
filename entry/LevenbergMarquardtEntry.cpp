//
// Created by Administrator on 2022/7/30.
//


#include <ql/math/optimization/all.hpp>
#include <iostream>
using namespace QuantLib;

class MyCostFunction : public CostFunction{
public:
    MyCostFunction (Real t1 ,Real t2):t1_(t1),t2_(t2){}
    Real value(const Array& x) const override {
//        QL_REQUIRE(x.size()==1,"independent variable must be 1 dimensional");
        Real result = 0;
        Array y(x.size());
        y = values(x) ;
        for (int i = 0; i < x.size(); ++i) {
            result +=  y[i] *y[i];
        }
        return result;
    }

    Disposable<Array> values(const Array& array) const override {
        Array y(array.size());

        Real a = array[0];
        Real b = array[1];
//        Real c = array[2];
        Real x = array[2];

        y[0]=t1_ -b +a ;
//        y[1]=340 * t2_ -c +b ;
        y[1]=a*a - 5*5 ;
        y[2]=b*b -  4*4 + (x +2)*(x +2);

        return y;
    }

private:
    Real  t1_;
    Real  t2_;
};

int  main(){
    Real esp = QL_EPSILON;

    const Array initialValues = {0,0,0};  //初始迭代值

    MyCostFunction costFct(1,0);
    NoConstraint noConstraint;  //约束条件
    Problem prob(costFct, noConstraint, initialValues);
    EndCriteria endCriteria(500, 100, esp, esp, esp);
    LevenbergMarquardt().minimize(
            prob, endCriteria);
    Real a = prob.currentValue()[0];
    Real b = prob.currentValue()[1];
//    Real c = prob.currentValue()[2];
    Real x = prob.currentValue()[2];
    std::cout<<"a:"<<a<<std::endl;
    std::cout<<"b:"<<b<<std::endl;
//    std::cout<<"c:"<<c<<std::endl;
    std::cout<<"x:"<<x<<std::endl;
    return 0 ;
}