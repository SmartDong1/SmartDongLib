//
// Created by Administrator on 2020/11/2.
//

#ifndef SMARTDONGLIB_SORT_H
#define SMARTDONGLIB_SORT_H
namespace SmartDongLib{
    class Sort{
    public:
        enum sortMethod {

            SelectionSort =1,
            BubbleSort ,
            InsertionSort
        };
        /**
         * <p>选择排序.每次选择最值放到最前面
         * @tparam _RandomAccessIterator    线性表地址类型
         * @tparam _Compare                 比较函数类型
         * @param _first                    线性表起始地址
         * @param _last                     线性表结束地址
         * @param _comp                     比较函数
         */
        template<class _RandomAccessIterator, class _Compare>
        static void selectionSort(_RandomAccessIterator _first, _RandomAccessIterator _last,
                _Compare _comp ){
            for (_RandomAccessIterator iter = _first ; iter < _last ;iter++){
                _RandomAccessIterator maxValue = iter;
                for (_RandomAccessIterator index= iter; index <  _last; ++index) {
                    if ( _comp (*index,*maxValue)  ){
                        maxValue=index;
                    }
                }
                iteratorSwap(maxValue,iter);
            }
        }
        template<class _RandomAccessIterator>
        static void selectionSort(_RandomAccessIterator _first, _RandomAccessIterator _last){
            for (_RandomAccessIterator iter = _first ; iter < _last ;iter++){
                _RandomAccessIterator maxValue = iter;
                for (_RandomAccessIterator index= iter; index <  _last; ++index) {
                    if (*index<*maxValue ){
                        maxValue=index;
                    }
                }
                iteratorSwap(maxValue,iter);
            }
        }
        /**
         * <p> 冒泡排序。每次双循环把最值交换到最前面
         * @tparam _RandomAccessIterator    线性表地址类型
         * @tparam _Compare                 比较函数类型
         * @param _first                    线性表起始地址
         * @param _last                     线性表结束地址
         * @param _comp                     比较函数
         */
        template<class _RandomAccessIterator, class _Compare>
        static void bubbleSort(_RandomAccessIterator _first, _RandomAccessIterator _last,
                                  _Compare _comp ){
            for (_RandomAccessIterator iter = _last ; iter > _first+1 ;iter--){
                for (_RandomAccessIterator index= _first; index <  iter -1; ++index) {
                    if ( _comp (*(index +1),*index)  ){
                        iteratorSwap(index,index +1);
                    }
                }

            }
        }
        template<class _RandomAccessIterator>
        static void bubbleSort(_RandomAccessIterator _first, _RandomAccessIterator _last){
            for (_RandomAccessIterator iter = _last ; iter > _first+1 ;iter--){
                for (_RandomAccessIterator index= _first; index <  iter -1; ++index) {
                    if ( *(index +1)<*index  ){
                        iteratorSwap(index,index +1);
                    }
                }

            }
        }
        /**
         * <p> 直接插入排序。每次双循环i次表示前 i-1 个数都已经排好序。
         * @tparam _RandomAccessIterator    线性表地址类型
         * @tparam _Compare                 比较函数类型
         * @param _first                    线性表起始地址
         * @param _last                     线性表结束地址
         * @param _comp                     比较函数
         */
        template<class _RandomAccessIterator, class _Compare>
        static void insertionSort(_RandomAccessIterator _first, _RandomAccessIterator _last,
                               _Compare _comp ){
            for (_RandomAccessIterator iter = _first+1 ; iter < _last ;iter++){
                auto temp =  *iter;
                _RandomAccessIterator index = iter -1;
                //假如前面 iter -1 个都已经排好序 ，现在插第 iter 个
                // 先把iter的值保存起来 到temp
                // 然后从  iter -1 开始 和 temp 开始比较,如果小则 index的值往后移
                // 当比较结果为大时结束循环,把 temp 放入到 当前比较位置的后一个
                for ( ;index >= _first && _comp(temp , *index); --index) {
                    *(index +1) = *(index);
                }
                *(index +1) = (temp);
            }
        }
        template<class _RandomAccessIterator>
        static void insertionSort(_RandomAccessIterator _first, _RandomAccessIterator _last){
            for (_RandomAccessIterator iter = _first+1 ; iter < _last ;iter++){
                auto temp =  *iter;
                _RandomAccessIterator index = iter -1;
                //假如前面 iter -1 个都已经排好序 ，现在插第 iter 个
                // 先把iter的值保存起来 到temp
                // 然后从  iter -1 开始 和 temp 开始比较,如果小则 index的值往后移
                // 当比较结果为大时结束循环,把 temp 放入到 当前比较位置的后一个
                for ( ;index >= _first && temp < *index; --index) {
                    *(index +1) = *(index);
                }
                *(index +1) = (temp);
            }
        }
    private:
        template<class _RandomAccessIterator>
        static void iteratorSwap(_RandomAccessIterator _elem1, _RandomAccessIterator _elem2){
            auto temp = *_elem1;
            *_elem1 = *_elem2;
            *_elem2 = temp;
        }

    };
}
#endif //SMARTDONGLIB_SORT_H
