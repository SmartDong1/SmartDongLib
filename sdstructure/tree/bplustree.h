#pragma once
#ifndef SMARTDONGLIB_BPLUSTREE
#define SMARTDONGLIB_BPLUSTREE
#include "btreestruct.h"
#include "multitree.h"
namespace SmartDongLib {

    class BPlusTree :
            public MultiTree {
    protected:
        virtual sMultiTreeNode *createRoot();

        virtual sMultiTreeNode *createNode();

        virtual int splitChild(sMultiTreeNode *parent, int pos, sMultiTreeNode *child);

        virtual void insertPartNode(sMultiTreeNode *node, int target);

        virtual void mergeChild(sMultiTreeNode *root, int pos, sMultiTreeNode *y, sMultiTreeNode *z);

        virtual void deletePartNode(sMultiTreeNode *root, int target);

        virtual int minKey(sMultiTreeNode *root);

        virtual int maxKey(sMultiTreeNode *root);

        virtual void leftShiftMinkeyTopos(sMultiTreeNode *root, int pos, sMultiTreeNode *y, sMultiTreeNode *z);

        virtual void rightShiftMaxkeyTopos(sMultiTreeNode *root, int pos, sMultiTreeNode *y, sMultiTreeNode *z);

        virtual sMultiTreeNode *insertNode(sMultiTreeNode *root, int target);

        virtual sMultiTreeNode *deleteNode(sMultiTreeNode *root, int target);

        virtual void inOrderTraversal(sMultiTreeNode *root);

        virtual void levelTraversal(sMultiTreeNode *root);

        virtual void Save(sMultiTreeNode *root);

        /**
         * @brief print tree linearly using prev_/next pointer
         *
         * @param root: root of tree
         */
        void btree_linear_print(sMultiTreeNode *root);

    public:
        BPlusTree();

        ~BPlusTree();

        void linear_print();
    };
}
#endif
