#pragma once
// the degree of btree
#ifndef SMARTDONGLIB_SMULTITREENODE
#define SMARTDONGLIB_SMULTITREENODE
#define MINDEGREE 2
namespace SmartDongLib {
    typedef struct sMultiTreeNode {
        int key_[2 * MINDEGREE - 1];
        struct sMultiTreeNode *ptr_[2 * MINDEGREE];
        int validnum_;                 //有效的元素
        bool isleaf_;                  //是否是叶子节点
        struct sMultiTreeNode *prev_;  // 前驱节点,B+Tree used
        struct sMultiTreeNode *next_;  // 后继节点,B+Tree used

    } sMultiTreeNode;


    typedef struct StorageNode {
        sMultiTreeNode bnode;
        int index[MINDEGREE];   // 索引集合:index_set
    } StorageNode;

    typedef struct StorageStruct {
        StorageNode *snode;
        int len;
    } StorageStruct;
}
#endif