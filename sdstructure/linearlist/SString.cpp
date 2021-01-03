//
// Created by hu on 2020/8/5.
//

#include "sdstructure/linearlist/SString.h"
namespace SmartDongLib {

   inline Size SString::index(const SString& str2,  Size pos ) {
        Size iptr = pos , jptr = 0;
        while (iptr < str_.length() && jptr<str2.str_.length()){
            if (str_[iptr] == str2.str_[jptr]){
                //相等则比较下一位
                iptr++ ; jptr++;
            } else{
                //不相等则回溯，模式串指针从0 开始 i 回溯到原先的起始值+1 ， 现值i'与原先的起始值i 满足 i'-i=j'-j其中j=0
                iptr = iptr - jptr+1;
                jptr = 0;
            }
        }
        if (jptr >=str2.str_.length()){
            return iptr - jptr;
        }
        return -1;
    }
    /**
     * <p> 1 . 求next数组,有了next数组后一个一个匹配，如果失配让 j = next[j];
     * @param str2
     * @param pos
     * @return
     */
    inline Size SString::indexKMP(SString& str2, Size pos) {
        Size i=pos, j=0;
        Size next[str2.str_.length()];
        str2.getnext(next);
        Size thisLen=length(),sublen=str2.length();
        while ( i < thisLen && j < sublen){
            if (j==-1 || str_[i] == str2.str_[j]){
                i++;
                j++;
            } else{
                j=next[j];
            }
        }
        if (j >= sublen){
            Size ret =i-sublen;
            return ret;
        }
        return -1;
    }

    inline SString SString::replace(SString src, const SString& target) {
        if (src.str_.empty()){
            return *this;
        }
        Size index=0;
        while ( index != -1) {
            index = indexKMP(src);
            if(index != -1) {
                str_.erase(index,  src.str_.length());
                str_.insert(index, target.str_);
            }
        }
        return *this;
    }

    /**
     * <p>原理: 当求next的第j个元素时，看  j-1 个元素开始和第0个元素比对，k不断增加取最大值满足  0<k<j
     * 从后往前数k个即第 j-k+1...j-1元素与 0...k-1
     * 如  abaabcac    当(a)j=0 next[0]=0 ; （b）j =1 ,next[1]=1,;(a) j=2时，k=1，第1个元素和第0个元素比对即a和b比不对就是1
     *  当(a)j=3,k=1，第2个元素和第0个元素 比a和a匹配上了 那就是next[3]=2;
     * @param substr
     * @return
     */
    inline void SString::getnext(Size next[]) {

        const Size len =str_.length();
//        next.resize(len,-1);
        Size i = 0,j=-1;next[0]=-1;
        while (i<len){
            if (j==-1 ||str_[i] == str_[j]){
                ++i;++j;
                if (str_[i] != str_[j]){
                    next[i]=j;
                } else{
                    next[i]=next[j];
                }
            } else{
                j=next[j];
            }
        }
        //return next;
    }
    /**
     * <p> 返回最长公共字串
     * @param str2
     * @return
     */
    inline SString SString::maxCommonSubstr(SString &str2) {
        //原理: 动态规划  x 轴和 y 轴分别取 自身和str2
        //然后表格对齐，相同的字符 设成 1 其他为 0 ,取斜对角线最长不为0
        //asbbefg   和   aubeg  最大值2
        /*
            a	s	b	b	e	f	g
        a	1	0	0	0	0	0	0
        u	0	0	0	0	0	0	0
        b	0	0	1	1	0	0	0
        e	0	0	0	0	2	0	0
        g	0	0	0	0	0	0	1
        */
        Size len1 = this->length();
        Size len2 = str2.length();
        if (len1 ==0 || len2 == 0 ){
            return SString();
        }
        Size maxlen=-1;      //最大长度
        Size lastIndex =-1;  //最大值在主串的位置
        Size comparetbl[len2][len1];
        for (Size i = 0; i <len2 ; ++i) {
            char modelchar=str2[i];
            for (Size j = 0; j < len1; ++j) {
                if (str_[j]==modelchar){
                    if (i<1 || j<1 ){
                        comparetbl[i][j]=1;
                    }else{
                        comparetbl[i][j]=1+comparetbl[i-1][j-1];
                    }
                } else{
                    comparetbl[i][j]=0;
                }
                if (maxlen<comparetbl[i][j]){
                    maxlen=comparetbl[i][j];
                    lastIndex = j;
                }
            }
        }
        SString ret = this->subString(lastIndex-maxlen+1,maxlen);
        return ret;
    }
}