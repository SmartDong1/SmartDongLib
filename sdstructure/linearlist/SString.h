//
// Created by hu on 2020/8/5.
//

#ifndef SMARTDONGLIB_SSTRING_H
#define SMARTDONGLIB_SSTRING_H
#include  <string>
#include <vector>
#include <ostream>
#include "const.h"
namespace SmartDongLib {

    class SString {
    public:
        SString(){ str_="";}
        explicit SString(std::string str): str_(std::move(str)){}
        SString(const  SString& str){ str_=str.str_;}
        Size length(){return str_.length();}
        SString copy(){return *this;};
        bool isEmpty(){return str_.empty();}
        void clear(){str_=""; }
        SString concat(const SString& str2){ SString  ret(str_ + str2.str_); return ret;}
        SString subString(Size pos, Size len){SString ret (str_.substr(pos, len)); return ret;}
        SString subString(Size pos=0){SString ret (str_.substr(pos)); return ret;}
        Size index( const SString& , Size pos =0);
        Size indexKMP(SString& str2, Size pos= 0);
        SString maxCommonSubstr(SString& str2);
        SString replace(SString src, const SString& target);
        void strinsert(Size pos,const SString& T){str_.insert(pos, T.str_);}
        void strdelete(Size pos,Size len){str_.erase(pos,len);}
        SString operator+(std::string str1){ return SString(str_ + std::move(str1));}
        SString operator+=(std::string str1){ return SString(str_ + std::move(str1));}
        char operator [](Size i){return  str_[i];}
        bool operator==(const std::string& str1){return str_==str1;}
        friend std::ostream& operator<<(std::ostream &os, const SString &pd){
            os << pd.str_;
            return os;
        }
        std::string get(){return str_;}
        void getnext(Size next[]);
    private:
        std::string  str_;
    };
}

#endif //SMARTDONGLIB_SSTRING_H
