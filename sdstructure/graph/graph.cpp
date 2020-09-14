//
// Created by Administrator on 2020/9/11.
//
#include "graph.h"

namespace SmartDongLib {
    /**
     * <p>通过Key找到对应的结点在邻接表的下标
     * @tparam KeyType
     * @tparam ElemType
     * @param k
     * @return
     */
    template<class KeyType, class ElemType>
    int Graph<KeyType, ElemType>::findKeyOnIndex(KeyType k) {
       for (int i=0;i< nodes_.size();i++){
           if (nodes_[i].key() == k){
               return  i ;
           }
       }
       return  -1;
    }
    /**
     * <p> 给图插入新的结点
     * @tparam KeyType
     * @tparam ElemType
     * @param n
     * @return
     */
    template<class KeyType, class ElemType>
    Graph<KeyType, ElemType> &Graph<KeyType, ElemType>::addNode(GraphAdjacencyList<KeyType, ElemType> n) {
        if (findKeyOnIndex(n->key()) ==-1) {
            nodes_.push_back(n);
        }
        return *this;
    }
    /**
     * <p> 给图插入新的结点
     * @tparam KeyType
     * @tparam ElemType
     * @param k 结点键值
     * @param e 结点数据
     * @return
     */
    template<class KeyType, class ElemType>
    Graph<KeyType, ElemType> &Graph<KeyType, ElemType>::addNode(KeyType k, ElemType e) {
        if (findKeyOnIndex(k) ==-1){
            GraphAdjacencyList<KeyType, ElemType> n(k,e);
            nodes_.push_back(n);
        }
        return *this;
    }
    /**
     * <p>根据Key值删除图的结点
     * @tparam KeyType
     * @tparam ElemType
     * @param key
     * @return
     */
    template<class KeyType, class ElemType>
    Graph<KeyType, ElemType> &Graph<KeyType, ElemType>::deleteNodeByKey(KeyType key) {
        int keyIndex = findKeyOnIndex(key);
        if (keyIndex ==-1){
            return *this;
        }
        // 大于keyIndex 的结点下标都要减1
        for (int i = 0; i < nodes_.size(); ++i) {
            //每个结点删除对应的边
            nodes_.at(i).deleteEdge(keyIndex);
            boost::shared_ptr<LinkList<int>> edge=nodes_[i].edge();
            while (edge){
                //大于keyIndex 的结点下标都要减1
                if (edge->data > keyIndex){
                    edge->data = edge->data -1;
                }
                edge=edge->next;
            }
        }
        //刪除结点
        typename std::vector<GraphAdjacencyList<KeyType,ElemType>>::iterator iter=nodes_.begin();
        nodes_.erase(iter + keyIndex);
        return  * this;
    }
    /**
     * <p> 建立 源节点到目标结点的单向边
     * @tparam KeyType
     * @tparam ElemType
     * @param src 源节点
     * @param target 目标结点
     * @return
     */
    template<class KeyType, class ElemType>
    Graph<KeyType, ElemType> &Graph<KeyType, ElemType>::setEdge(KeyType src, KeyType target) {
        int srcIndex = findKeyOnIndex(src);
        int targetIndex = findKeyOnIndex(target);
        if (srcIndex == -1 || targetIndex == -1){
            //不存在所谓的结点
            return *this;
        }
        nodes_.at(srcIndex).insertEdge(targetIndex);
        if (isUndirectedgraph_){
            nodes_.at(targetIndex).insertEdge(srcIndex);
        }
        return *this;
    }
    /**
     * <p>删除 src结点到target结点的单向边
     * @tparam KeyType
     * @tparam ElemType
     * @param src   出度结点
     * @param target  入度结点
     * @return
     */
    template<class KeyType, class ElemType>
    Graph<KeyType, ElemType> &Graph<KeyType, ElemType>::deleteEdge(KeyType src, KeyType target) {
        int srcIndex = findKeyOnIndex(src);
        int targetIndex = findKeyOnIndex(target);
        if (srcIndex == -1 || targetIndex == -1){
            return *this;
        }
        nodes_.at(srcIndex).deleteEdge(targetIndex);
        if (isUndirectedgraph_){
            nodes_.at(targetIndex).deleteEdge(srcIndex);
        }
        return *this;
    }
    /**
     * <p>深度优先搜索调用函数
     * @tparam KeyType
     * @tparam ElemType
     * @param isSearchAllNode 是否遍历所有的点,默认只遍历一个起始点
     * @param visitIndex    开始遍历的起始点位置
     * @param Visit         对点的操作函数
     * @return
     */
    template<class KeyType, class ElemType>
    std::vector<int> Graph<KeyType, ElemType>::depthFirstSearch(bool isSearchAllNode , int visitIndex, int (*Visit)(Graph& , int)) {
        std::vector<int> visitNode;
        if (vexnum()<=0)
            return std::vector<int>();
        bool visited[vexnum()];
        for (int i = 0; i < vexnum(); ++i) {
            visited[i]= false;
        };
        DFS(visitIndex, visited, visitNode, Visit);
        if (isSearchAllNode) {
            for (int i = 0; i < vexnum(); ++i) {
                if (!visited[i])
                    DFS(i, visited, visitNode, Visit);
            };
        }
        return visitNode;
    }
    /**
     * <p> 深度优先搜索重载函数
     * @tparam KeyType
     * @tparam ElemType
     * @param key             开始遍历的键值
     * @param isSearchAllNode 是否遍历所有的点,默认只遍历一个起始点
     * @param Visit         对点的操作函数
     * @return
     */
    template<class KeyType, class ElemType>
    std::vector<int> Graph<KeyType, ElemType>::depthFirstSearch(KeyType key, bool isSearchAllNode,
                                                                int (*Visit)(Graph &, int)) {
        return depthFirstSearch(isSearchAllNode,findKeyOnIndex(key),Visit);
    }


    template<class KeyType, class ElemType>
    void Graph<KeyType, ElemType>::DFS(int visitIndex, bool visited[], std::vector<int> & output, int (*Visit)(Graph& , int)) {
        Visit(*this,visitIndex);
        visited[visitIndex] = true;
        output.push_back(visitIndex);

        boost::shared_ptr<LinkList<int>> edge=nodes_[visitIndex].edge();
        while (edge->next) {
            edge = edge->next;
            if (!visited[edge->data]){
                DFS(edge->data,visited,output,Visit);
            }
        }
    }
    /**
     * <p> 广度优先遍历
     * @tparam KeyType
     * @tparam ElemType
     * @param isSearchAllNode  是否查询全部结点
     * @param visitIndex        首先开始查询的结点
     * @param Visit             对结点的操作函数
     * @return
     */
    template<class KeyType, class ElemType>
    std::vector<int>
    Graph<KeyType, ElemType>::breadthFirstSearch(bool isSearchAllNode, int visitIndex, int (*Visit)(Graph &, int)) {
        std::vector<int> visitNode;
        if (vexnum()<=0)
            return std::vector<int>();
        bool visited[vexnum()];
        for (int i = 0; i < vexnum(); ++i) {
            visited[i]= false;
        }
        std::queue<int> indexQueue;
        //把结点的边入访问队列,之后弹出,再把对应结点的边入队列
        Visit(*this,visitIndex);
        visited[visitIndex] = true;
        visitNode.push_back(visitIndex);
        indexQueue.push(visitIndex);
        while (!indexQueue.empty()){
            int nextindex = indexQueue.front();
            indexQueue.pop();
            boost::shared_ptr<LinkList<int>> edge=nodes_[nextindex].edge();
            while (edge->next) {
                edge = edge->next;
                if (!visited[edge->data]){
                    visited[edge->data] = true;
                    Visit(*this,edge->data);
                    visitNode.push_back(edge->data);
                    indexQueue.push(edge->data);
                } //if
            } // while (edge->next) {
        }   //while (!indexQueue.empty()){

        if (isSearchAllNode){
            for (int i = 0; i < vexnum(); ++i) {
                if (!visited[i]){
                    Visit(*this,i);
                    visited[i] = true;
                    visitNode.push_back(i);
                    indexQueue.push(i);
                    while (!indexQueue.empty()){
                        int nextindex = indexQueue.front();
                        indexQueue.pop();
                        boost::shared_ptr<LinkList<int>> edge=nodes_[nextindex].edge();
                        while (edge->next) {
                            edge = edge->next;
                            if (!visited[edge->data]){
                                visited[edge->data] = true;
                                Visit(*this,edge->data);
                                visitNode.push_back(edge->data);
                                indexQueue.push(edge->data);
                            } //if
                        } // while (edge->next) {
                    }//while (!indexQueue.empty()){
                }//  if (!visited[i]){
            }// for (int i = 0; i < vexnum(); ++i) {
        }//  if (isSearchAllNode){
        return visitNode;
    }

    /**
     * <p> 广度优先遍历重载函数
     * @tparam KeyType
     * @tparam ElemType
     * @param key             开始遍历的键值
     * @param isSearchAllNode 是否遍历所有的点,默认只遍历一个起始点
     * @param Visit         对点的操作函数
     * @return
     */
    template<class KeyType, class ElemType>
    std::vector<int> Graph<KeyType, ElemType>::breadthFirstSearch(KeyType key, bool isSearchAllNode,
                                                                int (*Visit)(Graph &, int)) {
        return breadthFirstSearch(isSearchAllNode,findKeyOnIndex(key),Visit);
    }

}