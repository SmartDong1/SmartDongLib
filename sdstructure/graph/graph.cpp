//
// Created by Administrator on 2020/9/11.
//
#include "graph.h"

#include <utility>
namespace SmartDongLib {
    /**
     * <p>通过Key找到对应的结点在邻接表的下标
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param k
     * @return
     */
    template<class KeyType, class ElemType>
    Size Graph<KeyType, ElemType>::findKeyOnIndex(KeyType k) {
       for (Size i=0;i< nodes_.size();i++){
           if (nodes_[i].key() == k){
               return  i ;
           }
       }
       return  -1;
    }
    /**
     * <p> 给图插入新的结点
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
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
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
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
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param key
     * @return
     */
    template<class KeyType, class ElemType>
    Graph<KeyType, ElemType> &Graph<KeyType, ElemType>::deleteNodeByKey(KeyType key) {
        Size keyIndex = findKeyOnIndex(key);
        if (keyIndex ==-1){
            return *this;
        }
        // 大于keyIndex 的结点下标都要减1
        for (Size i = 0; i < nodes_.size(); ++i) {
            //每个结点删除对应的边
            nodes_.at(i).deleteEdge(keyIndex);
            boost::shared_ptr<LinkList<GraphAdjacencyEdge>> edge=nodes_[i].edge();
            while (edge){
                //大于keyIndex 的结点下标都要减1
                if (edge->data.nodeIndex_ > keyIndex){
                    edge->data.nodeIndex_ = edge->data.nodeIndex_ -1;
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
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param src 源节点
     * @param target 目标结点
     * @return
     */
    template<class KeyType, class ElemType>
    Graph<KeyType, ElemType> &Graph<KeyType, ElemType>::setEdge(KeyType src, KeyType target,Real weight ) {
        Size srcIndex = findKeyOnIndex(src);
        Size targetIndex = findKeyOnIndex(target);
        setEdgeByIndex(srcIndex,targetIndex,weight);
//        if (srcIndex == -1 || targetIndex == -1){
//            //不存在所谓的结点
//            return *this;
//        }
//        nodes_.at(srcIndex).insertEdge(targetIndex,weight);
//        if (isUndirectedgraph_){
//            nodes_.at(targetIndex).insertEdge(srcIndex,weight);
//        }
        return *this;
    }

    /**
     * <p> 添加边src对target方向的边
     * @tparam KeyType
     * @tparam ElemType
     * @param src       源节点下标
     * @param target    目标节点下标
     * @param weight    边的权重
     * @return
     */
    template<class KeyType, class ElemType>
    Graph<KeyType, ElemType> &Graph<KeyType, ElemType>::setEdgeByIndex(Size src, Size target, Real weight) {
        if (src >= 0 && target>=0 && src<nodes_.size() && target < nodes_.size()) {
            nodes_.at(src).insertEdge(target, weight);
            if (isUndirectedgraph_) {
                nodes_.at(target).insertEdge(src, weight);
            }
        }
        return *this;
    }
    /**
     * <p>删除 src结点到target结点的单向边
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param src   出度结点
     * @param target  入度结点
     * @return
     */
    template<class KeyType, class ElemType>
    Graph<KeyType, ElemType> &Graph<KeyType, ElemType>::deleteEdge(KeyType src, KeyType target) {
        Size srcIndex = findKeyOnIndex(src);
        Size targetIndex = findKeyOnIndex(target);
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
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param isSearchAllNode 是否遍历所有的点,默认只遍历一个起始点
     * @param visitIndex    开始遍历的起始点位置
     * @param Visit         对点的操作函数
     * @return
     */
    template<class KeyType, class ElemType>
    std::vector<Size> Graph<KeyType, ElemType>::depthFirstSearch(bool isSearchAllNode , Size visitIndex, Size (*Visit)(Graph& , Size)) {
        std::vector<Size> visitNode;
        if (vexnum()<=0)
            return std::vector<Size>();
        bool visited[vexnum()];
        for (Size i = 0; i < vexnum(); ++i) {
            visited[i]= false;
        };
        DFS(visitIndex, visited, visitNode, Visit);
        if (isSearchAllNode) {
            for (Size i = 0; i < vexnum(); ++i) {
                if (!visited[i])
                    DFS(i, visited, visitNode, Visit);
            };
        }
        return visitNode;
    }
    /**
     * <p> 深度优先搜索重载函数
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param key             开始遍历的键值
     * @param isSearchAllNode 是否遍历所有的点,默认只遍历一个起始点
     * @param Visit         对点的操作函数
     * @return
     */
    template<class KeyType, class ElemType>
    std::vector<Size> Graph<KeyType, ElemType>::depthFirstSearch(KeyType key, bool isSearchAllNode,
                                                                Size (*Visit)(Graph &, Size)) {
        Size keyindex = findKeyOnIndex(key);
        if (keyindex == -1)
            return std::vector<Size>();
        return depthFirstSearch(isSearchAllNode,keyindex,Visit);
    }

    /**
     * <p>深度优先搜索
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param visitIndex 正在遍历的点
     * @param visited    已经遍历的点标识
     * @param output     已走的结点路径
     * @param Visit      结点函数
     */
    template<class KeyType, class ElemType>
    void Graph<KeyType, ElemType>::DFS(Size visitIndex, bool visited[], std::vector<Size> & output, Size (*Visit)(Graph& , Size)) {
        Visit(*this,visitIndex);
        visited[visitIndex] = true;
        output.push_back(visitIndex);

        boost::shared_ptr<LinkList<GraphAdjacencyEdge>> edge=nodes_[visitIndex].edge();
        while (edge->next) {
            edge = edge->next;
            if (!visited[edge->data.nodeIndex_]){
                DFS(edge->data.nodeIndex_,visited,output,Visit);
            }
        }
    }
    /**
     * <p> 广度优先遍历
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param isSearchAllNode  是否查询全部结点
     * @param visitIndex        首先开始查询的结点
     * @param Visit             对结点的操作函数
     * @return
     */
    template<class KeyType, class ElemType>
    std::vector<Size>
    Graph<KeyType, ElemType>::breadthFirstSearch(bool isSearchAllNode, Size visitIndex, Size (*Visit)(Graph &, Size)) {
        std::vector<Size> visitNode;
        if (vexnum()<=0)
            return std::vector<Size>();
        bool visited[vexnum()];
        for (Size i = 0; i < vexnum(); ++i) {
            visited[i]= false;
        }
        std::queue<Size> indexQueue;
        //把结点的边入访问队列,之后弹出,再把对应结点的边入队列
        Visit(*this,visitIndex);
        visited[visitIndex] = true;
        visitNode.push_back(visitIndex);
        indexQueue.push(visitIndex);
        while (!indexQueue.empty()){
            Size nextindex = indexQueue.front();
            indexQueue.pop();
            boost::shared_ptr<LinkList<GraphAdjacencyEdge>> edge=nodes_[nextindex].edge();
            while (edge->next) {
                edge = edge->next;
                if (!visited[edge->data.nodeIndex_]){
                    visited[edge->data.nodeIndex_] = true;
                    Visit(*this,edge->data.nodeIndex_);
                    visitNode.push_back(edge->data.nodeIndex_);
                    indexQueue.push(edge->data.nodeIndex_);
                } //if
            } // while (edge->next) {
        }   //while (!indexQueue.empty()){

        if (isSearchAllNode){
            for (Size i = 0; i < vexnum(); ++i) {
                if (!visited[i]){
                    Visit(*this,i);
                    visited[i] = true;
                    visitNode.push_back(i);
                    indexQueue.push(i);
                    while (!indexQueue.empty()){
                        Size nextindex = indexQueue.front();
                        indexQueue.pop();
                        boost::shared_ptr<LinkList<GraphAdjacencyEdge>> edge=nodes_[nextindex].edge();
                        while (edge->next) {
                            edge = edge->next;
                            if (!visited[edge->data.nodeIndex_]){
                                visited[edge->data.nodeIndex_] = true;
                                Visit(*this,edge->data.nodeIndex_);
                                visitNode.push_back(edge->data.nodeIndex_);
                                indexQueue.push(edge->data.nodeIndex_);
                            } //if
                        } // while (edge->next) {
                    }//while (!indexQueue.empty()){
                }//  if (!visited[i]){
            }// for (Size i = 0; i < vexnum(); ++i) {
        }//  if (isSearchAllNode){
        return visitNode;
    }

    /**
     * <p> 广度优先遍历重载函数
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param key             开始遍历的键值
     * @param isSearchAllNode 是否遍历所有的点,默认只遍历一个起始点
     * @param Visit         对点的操作函数
     * @return
     */
    template<class KeyType, class ElemType>
    std::vector<Size> Graph<KeyType, ElemType>::breadthFirstSearch(KeyType key, bool isSearchAllNode,
                                                                Size (*Visit)(Graph &, Size)) {
        Size keyindex = findKeyOnIndex(key);
        if (keyindex == -1)
            return std::vector<Size>();
        return breadthFirstSearch(isSearchAllNode,keyindex,Visit);
    }
    /**
     * <p> 根据深度优先遍历返回有向图和无向图的连通分量
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param visitIndex  要查询的起点
     * @return
     */
    template<class KeyType, class ElemType>
    std::vector<Size> Graph<KeyType, ElemType>::connectedComponent(KeyType visitIndex) {
        return  depthFirstSearch(visitIndex);
    }
    /**
     * <p> 私有成员函数,用深度优先原理迭代出第一个回路
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param visitIndex 正在遍历的点
     * @param visited    已经遍历的点标识
     * @param output     已走的结点路径
     * @param Visit      结点函数
     * @return
     */
    template<class KeyType, class ElemType>
    bool Graph<KeyType, ElemType>::circuitJudge(Size visitIndex, bool visited[], std::vector<Size> &output,
                                                   Size (*Visit)(Graph &, Size)) {
        Visit(*this,visitIndex);
        visited[visitIndex] = true;
        Size outputsize=output.size();
        output.push_back(visitIndex);
        bool flag= false;
        boost::shared_ptr<LinkList<GraphAdjacencyEdge>> edge=nodes_[visitIndex].edge();
        while (edge->next) {
            edge = edge->next;
            if (!visited[edge->data.nodeIndex_]){
                flag = circuitJudge(edge->data.nodeIndex_,visited,output,Visit);
                if (!flag){
                    //深度优先回退
                    output.pop_back();
                } else{
                    return flag;
                }
            } else{
                if (!isUndirectedgraph_){
                    //有向图,如果访问访问过的点 那就是有回路
                    output.push_back(edge->data.nodeIndex_);
                    return true;
                } else{
                    //无向图 如果访问的点是已访问的祖先结点 那就是回路
                    for (Size i = 0; i < outputsize -1 ; ++i) {
                        if (edge->data.nodeIndex_ == output[i]){
                            output.push_back(edge->data.nodeIndex_);
                            return true;
                        }
                    }
                }//isUndirectedgraph_
            }
        }
        return flag;
    }
    /**
     * <p> 根据深度优先搜索来返回 结点下标回路,空集表示无回路
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param visitIndex 开始的结点下标
     * @param Visit     函数...
     * @return 结点下标回路集
     */
    template<class KeyType, class ElemType>
    std::vector<Size>
    Graph<KeyType, ElemType>::simpleCircuitOnIndex(Size visitIndex, Size (*Visit)(Graph &, Size)) {
        std::vector<Size> visitNode;
        if (vexnum()<=0)
            return std::vector<Size>();
        bool visited[vexnum()];
        for (Size i = 0; i < vexnum(); ++i) {
            visited[i]= false;
        };
        bool flag=circuitJudge(visitIndex, visited, visitNode, Visit);
        if (!flag){
            visitNode.clear();
        }
        return visitNode;
    }


    /**
     * <p>  根据深度优先搜索来返回 结点下标回路,空集表示无回路
     * @tparam KeyType    结点的key类型
     * @tparam ElemType   和结点所带的数据
     * @param key    要开始的结点key
     * @param Visit   函数
     * @return 结点下标回路集
     */
    template<class KeyType, class ElemType>
    std::vector<Size> Graph<KeyType, ElemType>::simpleCircuitOnKey(KeyType key, Size (*Visit)(Graph &, Size)) {
        Size keyindex = findKeyOnIndex(key);
        if (keyindex == -1)
            return std::vector<Size>();
        return simpleCircuitOnIndex(keyindex, Visit);
    }

    template<class KeyType, class ElemType>
    const std::vector<GraphAdjacencyList<KeyType, ElemType>> &Graph<KeyType, ElemType>::getNodes() const {
        return nodes_;
    }

    template<class KeyType, class ElemType>
    const std::vector<std::vector<Real>> &Graph<KeyType, ElemType>::getAdjacencyMatrix() const {
        return adjacencyMatrix_;
    }
    /**
     * <p> 普利姆算法-最小生成树
     * @tparam KeyType
     * @tparam ElemType
     * @param nodeIndex  开始节点下标
     * @return
     */
    template<class KeyType, class ElemType>
    Graph<KeyType, ElemType> Graph<KeyType, ElemType>::miniSpanTreePrimOnIndex(Size nodeIndex) {

        std::vector<Size> usedIndex; //已经加入最小树的顶点集
        std::vector<LowestCost> closedge; //已加入的顶点集到各其他顶点的最短路径
        Graph retGraph(this->isUndirectedgraph_);
        if (nodeIndex<0 || nodeIndex>=nodes_.size())
            return retGraph;
        for (Size j = 0; j < nodes_.size(); ++j) {
            retGraph.addNode(nodes_[j].key(),nodes_[j].elem());
        }
        usedIndex.push_back(nodeIndex);
        closedge.resize(nodes_.size());
        closedge[nodeIndex] = LowestCost(nodeIndex,0.0);
        //初始化 closedge
        boost::shared_ptr<LinkList<GraphAdjacencyEdge> >edge =  nodes_[nodeIndex].edge();
        while (edge->next){
            edge =edge->next;
            closedge[edge->data.nodeIndex_] =LowestCost(nodeIndex,edge->data.weight_);
        }
//        std::cout<<nodes_[nodeIndex].key()<<":";
//        for (Size i = 0; i < closedge.size(); ++i) {
//            std::cout<<i<<"-"<<nodes_[closedge[i].nodeIndex_].key()<<"-"<<closedge[i].lowcost_<<"\t";
//        }
//        std::cout<<"\n";
        for (Size meaninglessVar = 0; meaninglessVar < nodes_.size(); ++meaninglessVar) {
            //获取closedge 中最小的下标
            Size newNodeIndex = getMinCostnodeIndex(closedge);
            if (newNodeIndex < 0 )
                break;
            retGraph.setEdgeByIndex(closedge[newNodeIndex].nodeIndex_,newNodeIndex,closedge[newNodeIndex].lowcost_);
            usedIndex.push_back(newNodeIndex);
            closedge[newNodeIndex] =LowestCost(closedge[newNodeIndex].nodeIndex_,0.0);
            boost::shared_ptr<LinkList<GraphAdjacencyEdge> >newNodeEdge =  nodes_[newNodeIndex].edge();
            while (newNodeEdge->next){
                newNodeEdge =newNodeEdge->next;
                if (newNodeEdge->data.weight_ < closedge[newNodeEdge->data.nodeIndex_].lowcost_) {
                    closedge[newNodeEdge->data.nodeIndex_] = LowestCost(newNodeIndex, newNodeEdge->data.weight_);
                }
            }
//            std::cout<<nodes_[newNodeIndex].key()<<":";
//            for (Size i = 0; i < closedge.size(); ++i) {
//                std::cout<<i<<"-"<<nodes_[closedge[i].nodeIndex_].key()<<"-"<<closedge[i].lowcost_<<"\t";
//            }
//            std::cout<<"\n";

        }

        return retGraph;
    }
    /**
     * <p> 初始化邻接矩阵
     * @tparam KeyType
     * @tparam ElemType
     */
    template<class KeyType, class ElemType>
    void Graph<KeyType, ElemType>::initialAdjacencyMatrix(){
        adjacencyMatrix_.clear();
        adjacencyMatrix_.resize(nodes_.size());
        for (auto & i : adjacencyMatrix_) {
            Real maxReal=SD_CONST::SD_MAXDOUBLE;
            i.resize(nodes_.size(),maxReal);
        }
        for (Size j = 0; j < nodes_.size(); ++j) {
            boost::shared_ptr<LinkList<GraphAdjacencyEdge> >edge =  nodes_[j].edge();
            while (edge->next){
                edge =edge->next;
                adjacencyMatrix_[j][edge->data.nodeIndex_] = edge->data.weight_;
            }
        }
    }
    /**
     * <p> 获取路径最小权重的点的下标
     * @tparam KeyType
     * @tparam ElemType
     * @param closedge  路径集
     * @return
     */
    template<class KeyType, class ElemType>
    Size Graph<KeyType, ElemType>::getMinCostnodeIndex(std::vector<LowestCost> &closedge) {
        Size ret = -1;
        Real minValue=SD_CONST::SD_MAXDOUBLE;
        for (Size i = 0; i < closedge.size(); ++i) {
            if (closedge[i].lowcost_<minValue && closedge[i].lowcost_>0.0){
                minValue =closedge[i].lowcost_;
                ret = i;
            }
        }
        return  ret;
    }
    /**
     * <p>普利姆算法 - 最小生成树
     * @tparam KeyType
     * @tparam ElemType
     * @param nodekey 开始节点Key
     * @return
     */
    template<class KeyType, class ElemType>
    Graph<KeyType, ElemType> Graph<KeyType, ElemType>::miniSpanTreePrimOnKey(KeyType nodekey) {
        return miniSpanTreePrimOnIndex(findKeyOnIndex(nodekey));
    }
    /**
     * <p> 迪杰斯特拉-最短路径
     * @tparam KeyType
     * @tparam ElemType
     * @param srcIndex               源节点下标
     * @param isInitAdjacencyMatrix  是否初始化邻接矩阵
     * @return 返回源节点到其他节点的最短路径和损耗
     */
    template<class KeyType, class ElemType>
    std::vector<LowestPath>
    Graph<KeyType, ElemType>::shortPathOnIndex(Size srcIndex, bool isInitAdjacencyMatrix) {
        if (isInitAdjacencyMatrix){
            initialAdjacencyMatrix();
        }
        if (srcIndex<0 || srcIndex>=nodes_.size())
            return std::vector<LowestPath>();
        //邻接矩阵从第 srcIndex行开始选择最小值
        std::vector<LowestPath> retLowestPaths ;
        std::vector<LowestPath> lowestPaths ;
        retLowestPaths.resize(this->vexnum());
        lowestPaths.resize(this->vexnum());
        for (Size first = 0; first < lowestPaths.size(); ++first) {
            lowestPaths.at(first).pathIndex_.push_back(srcIndex);
            lowestPaths.at(first).lowcost_=adjacencyMatrix_[srcIndex][first];
        }
        //0      1      2       3       4       5           currentPathIndex    currentPath   lowestcost
        //∞(0,)  ∞(0,)  10(0,)  ∞(0,)   30(0,)  100(0,)     2                   0,2           10
        //∞(0,)  ∞(0,)          60(0,2) 30(0,)  100(0,)     4                   0,4           30
        //∞(0,)  ∞(0,)          50(0,4)         90(0,4,)    3                   0,4,3         50
        //∞(0,)  ∞(0,)                          60(0,4,3,)  5                   0,4,3,5       60
        //∞(0,)  ∞(0,)                                      0                   0,0           ∞
        //       ∞(0,)                                      1                   0,1           ∞
        std::vector<Size> currentPath;
        Real lowestCost;
        for (Size i = 0; i < lowestPaths.size(); ++i) {
            //获取最小lostCost的下标 并且返回结果
            Size currentPathIndex = LowestPath::getMincost(lowestPaths);
            currentPath= lowestPaths[currentPathIndex].pathIndex_;
            currentPath.push_back(currentPathIndex);
            lowestCost=lowestPaths[currentPathIndex].lowcost_;
            retLowestPaths[currentPathIndex].lowcost_=lowestCost;
            retLowestPaths[currentPathIndex].pathIndex_=currentPath;
            lowestPaths[currentPathIndex].hasVisit_= true;
            //----------------------
            for (Size j = 0; j < lowestPaths.size(); ++j) {
                //如果当前路径是更短的路径，从新设置路径和该路径的最小值
                if (lowestCost+ adjacencyMatrix_[currentPathIndex][j] <lowestPaths[j].lowcost_) {
                    lowestPaths[j].lowcost_= lowestCost+ adjacencyMatrix_[currentPathIndex][j] ;
                    lowestPaths[j].pathIndex_=currentPath;
                }
            }

        }

        return retLowestPaths;
    }
    /**
     * <p> 迪杰斯特拉-最短路径
     * @tparam KeyType
     * @tparam ElemType
     * @param srcKey                源节点Key
     * @param isInitAdjacencyMatrix 是否初始化邻接矩阵
     * @return 返回源节点到其他节点的最短路径和损耗
     */
    template<class KeyType, class ElemType>
    std::vector<LowestPath> Graph<KeyType, ElemType>::shortPathOnKey(KeyType srcKey, bool isInitAdjacencyMatrix) {
        return shortPathOnIndex(findKeyOnIndex(srcKey),isInitAdjacencyMatrix);
    }
    /**
     * <p>最长路径(不走重复路)
     * @tparam KeyType
     * @tparam ElemType
     * @param srcIndex  源节点下标
     * @param target    目标节点下标
     * @param hasVisitIndex 已经访问过的点集，路径
     * @param isInitAdjacencyMatrix     是否初始化邻接矩阵
     * @return  返回最长路径的消耗
     */
    template<class KeyType, class ElemType>
    Real Graph<KeyType, ElemType>::longPathOnIndex(Size srcIndex,Size target,std::vector<Size>& hasVisitIndex, bool isInitAdjacencyMatrix) {
        if (isInitAdjacencyMatrix){
            initialAdjacencyMatrix();
        }

        if (srcIndex == target){
            return 0;
        }

        hasVisitIndex.insert(hasVisitIndex.begin(), target);
        std::vector<Size> hasVisitIndex_temp=hasVisitIndex;  //保留递归入栈时的状态

        std::vector<Size> preNode;//入栈时,未访问的前驱节点集合
        for (Size i = 0; i <  adjacencyMatrix_.size();++i) {
            if (adjacencyMatrix_[i][target] != SD_CONST::SD_MAXDOUBLE){
                //判断是否已经访问,把入栈时未访问的前驱节点加进去
                bool isVisit=isContain(hasVisitIndex,i);
                if (!isVisit) {
                    preNode.push_back(i);
                }
            }
        }
        Real maxvalue=SD_CONST::SD_MINDOUBLE;
        if (adjacencyMatrix_[srcIndex][target] !=SD_CONST::SD_MAXDOUBLE){
            //如果再邻接矩阵有直接值，先初始化
            maxvalue = adjacencyMatrix_[srcIndex][target];
        }
        for (Size & pnode : preNode) {
            //取 源节点到前驱节点,前驱节点到目标节点的最大值,并最大值且返回递归的路经
           if (adjacencyMatrix_[pnode][target] != SD_CONST::SD_MAXDOUBLE ){
               //使用复制后继节点入栈时的已访问状态
               //count  hasVisitIndex&     target      hasVisitIndex_temp      hasVisitIndextemp
               //1       null               9           9                       9
               //2       9                  7           7,9                     7,9
               //3       7,9                5           5,7,9                   5,7,9
               //4       5,7,9              2           2,5,7,9                 2,5,7,9
               //5       2,5,7,9            1           1,2,5,7,9               2,5,7,9          cost::18
               //3->6                       3                                   3,5,7,9
               //7       3,5,7,9            1           1,3,5,7,9
               std::vector<Size> hasVisitIndextemp=hasVisitIndex_temp;
               Real value = longPathOnIndex(srcIndex, pnode, hasVisitIndextemp, false)
                              + adjacencyMatrix_[pnode][target];
               if (maxvalue<value){
                   maxvalue=value;
                   hasVisitIndex=hasVisitIndextemp;
               }
           }

        }
        return maxvalue;
    }
    /**
     * <p>最长路径(不走重复路)
     * @tparam KeyType
     * @tparam ElemType
     * @param srcIndex 源节点下标
     * @param target    目标节点下标
     * @param isInitAdjacencyMatrix  是否初始化邻接矩阵
     * @return 已经访问过的点集和最长路径的消耗
     */
    template<class KeyType, class ElemType>
    LongestPath Graph<KeyType, ElemType>::longPathOnIndex(Size srcIndex, Size target, bool isInitAdjacencyMatrix) {

        std::vector<Size> retPath;
        Real maxPath=longPathOnIndex(srcIndex,target,retPath, isInitAdjacencyMatrix);
        retPath.insert(retPath.begin(),srcIndex);
        return LowestPath(retPath,maxPath);
    }

    /**
     * <p> 获取未访问过的最小消耗路径
     * @param vec 路径集
     * @return  最小消耗路径下标
     */
    inline Size LowestPath::getMincost(std::vector<LowestPath> vec) {
        Size minIndex=-1;
        for (Size i = 0; i <vec.size() ; ++i) {
            if (!(vec[i].hasVisit_)){
                minIndex = i;
                break;
            }
        }
        for (Size i = 0; i <vec.size() ; ++i) {
            if (vec[i] < vec[minIndex] && !(vec[i].hasVisit_)){
                minIndex = i;
            }
        }
        return minIndex;
    }

    inline LowestPath::LowestPath(std::vector<Size> pathIndex, Real lowcost, bool hasVisit ) : pathIndex_(std::move(pathIndex)),
                                                                                               lowcost_(lowcost),
                                                                                               hasVisit_(hasVisit) {}
}