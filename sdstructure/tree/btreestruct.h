#pragma once
// the degree of btree
#ifndef SMARTDONGLIB_SMULTITREENODE
#define SMARTDONGLIB_SMULTITREENODE
#define MINDEGREE 2
namespace SmartDongLib {
    typedef struct sMultiTreeNode {
        int key_[2 * MINDEGREE - 1];
        struct sMultiTreeNode *ptr_[2 * MINDEGREE];
        int validnum_;                 //��Ч��Ԫ��
        bool isleaf_;                  //�Ƿ���Ҷ�ӽڵ�
        struct sMultiTreeNode *prev_;  // ǰ���ڵ�,B+Tree used
        struct sMultiTreeNode *next_;  // ��̽ڵ�,B+Tree used

    } sMultiTreeNode;


    typedef struct StorageNode {
        sMultiTreeNode bnode;
        int index[MINDEGREE];   // ��������:index_set
    } StorageNode;

    typedef struct StorageStruct {
        StorageNode *snode;
        int len;
    } StorageStruct;
}
#endif