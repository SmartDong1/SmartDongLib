//
// Created by hu on 2020/8/5.
//

#ifndef SMARTDONGLIB_SSTRING_H
#define SMARTDONGLIB_SSTRING_H
#include  <string>
#include <vector>

namespace SmartDongLib {

    class SString {
    public:
        SString(){ str_="";}
        explicit SString(std::string str): str_(std::move(str)){}
        SString(const  SString& str){ str_=str.str_;}
        int length(){return str_.length();}
        SString copy(){return *this;};
        bool isEmpty(){return str_.empty();}
        void clear(){str_=""; }
        SString concat(const SString& str2){ SString  ret(str_ + str2.str_); return ret;}
        SString subString(int pos, int len){SString ret (str_.substr(pos, len)); return ret;}
        SString subString(int pos=0){SString ret (str_.substr(pos)); return ret;}
        int index( const SString& , int pos =0);
        int index_KMP(SString& str2, int pos=0);
        SString replace(SString src, const SString& target);
        void strinsert(int pos,const SString& T){str_.insert(pos, T.str_);}
        void strdelete(int pos,int len){str_.erase(pos,len);}
        SString operator+(std::string str1){ return SString(str_ + std::move(str1));}
        SString operator+=(std::string str1){ return SString(str_ + std::move(str1));}
        bool operator==(const std::string& str1){return str_==str1;}
        std::string get(){return str_;}
        void getnext(int next[]);
    private:
        std::string  str_;
    };
}

#endif //SMARTDONGLIB_SSTRING_H
