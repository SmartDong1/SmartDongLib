#pragma once
#ifndef SMARTDONGLIB_BTREE
#define SMARTDONGLIB_BTREE
#include "btreestruct.h"
#include "multitree.h"
namespace SmartDongLib {
    class BTree : public MultiTree {
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

    public:

        BTree(void);

        ~BTree(void);
    };
}
#endif //SMARTDONGLIB_MULTITREE_H
