//
// Created by Administrator on 2021/2/20.
//

#ifndef SMARTDONGLIB_MULTITREE_H
#define SMARTDONGLIB_MULTITREE_H
#pragma once
#include "btreestruct.h"
#include <stdio.h>
/**
 * @brief the degree of btree
 * key per node: [M-1, 2M-1]
 * child per node: [M, 2M]
 */
namespace SmartDongLib {
    class MultiTree {
    protected:
        sMultiTreeNode *roots;

        FILE *pfile;

        /**
         * @brief create a btree root
         *
         * @return pointer of btree root
         */
        virtual sMultiTreeNode *createRoot() = 0;

        /**
         * @brief allocate a new btree node
         * default: is_leaf == true
         *
         * @return pointer of new node
         */
        virtual sMultiTreeNode *createNode() = 0;

        /**
         * @brief split child if num of key in child exceed 2M-1
         *
         * @param parent: parent of child
         * @param pos: p[pos] points to child
         * @param child: the node to be splited
         *
         * @return
         */
        virtual int splitChild(sMultiTreeNode *parent, int pos, sMultiTreeNode *child) = 0;

        /**
         * @brief insert a value into btree
         * the num of key in node less than 2M-1
         *
         * @param node: tree root
         * @param target: target to insert
         */
        virtual void insertPartNode(sMultiTreeNode *node, int target) = 0;

        /**
         * @brief merge y, z and root->k[pos] to left
         * this appens while y and z both have M-1 keys
         *
         * @param root: parent node
         * @param pos: postion of y
         * @param y: left node to merge
         * @param z: right node to merge
         */
        virtual void mergeChild(sMultiTreeNode *root, int pos, sMultiTreeNode *y, sMultiTreeNode *z) = 0;

        /**
         * @brief delete a vlue from btree
         * root has at least M keys
         *
         * @param root: btree root
         * @param target: target to delete
         *
         * @return
         */
        virtual void deletePartNode(sMultiTreeNode *root, int target) = 0;

        /**
         * @brief find the leftmost value
         *
         * @param root: root of tree
         *
         * @return: the leftmost value
         */
        virtual int minKey(sMultiTreeNode *root) = 0;

        /**
         * @brief find the rightmost value
         *
         * @param root: root of tree
         *
         * @return: the rightmost value
         */
        virtual int maxKey(sMultiTreeNode *root) = 0;

        /**
         * @brief shift a value from z to y
         *
         * @param root: btree root
         * @param pos: position of y
         * @param y: left node
         * @param z: right node
         */
        virtual void leftShiftMinkeyTopos(sMultiTreeNode *root, int pos, sMultiTreeNode *y, sMultiTreeNode *z) = 0;

        /**
         * @brief shift a value from z to y
         *
         * @param root: btree root
         * @param pos: position of y
         * @param y: left node
         * @param z: right node
         */
        virtual void rightShiftMaxkeyTopos(sMultiTreeNode *root, int pos, sMultiTreeNode *y, sMultiTreeNode *z) = 0;

        /**
         * @brief insert a value into btree

         *
         * @param root: tree root
         * @param target: target to insert
         *
         * @return: new root of tree
         */
        virtual sMultiTreeNode *insertNode(sMultiTreeNode *root, int target) = 0;

        /**
         * @brief delete a vlue from btree
         *
         * @param root: btree root
         * @param target: target to delete
         *
         * @return: new root of tree
         */
        virtual sMultiTreeNode *deleteNode(sMultiTreeNode *root, int target) = 0;

        /**
         * @brief inorder traverse the btree
         *
         * @param root: root of treee
         */
        virtual void inOrderTraversal(sMultiTreeNode *root) = 0;


        /**
         * @brief level print the btree
         *
         * @param root: root of tree
         */
        virtual void levelTraversal(sMultiTreeNode *root) = 0;

        /**
         * @Save the btree
         *
         * @param root: root of tree
         */
        virtual void Save(sMultiTreeNode *root) = 0;

        int nodenum_;  //记录多少个树结点： how many  btree_node
    public:

        MultiTree(void) {
            nodenum_ = 0;
        };

        virtual ~MultiTree(void) {
            nodenum_ = 0;
            delete roots;
        };

        /*
        * @param target: target to insert
        */
        void insert(int target) {
            roots = insertNode(roots, target);
            Save(roots);  // 即时保存
        };

        /**
         * @brief level print the btree
         */
        void level_display() {
            levelTraversal(roots);
        };

        /**
         * @brief level print the btree
         */
        void del(int target) {
            roots = deleteNode(roots, target);

            Save(roots);  // 即时保存
        };

        void inorder_print() {
            inOrderTraversal(roots);
        };

        // tree node num
        void NodeNum_print() {
            printf("%d\n", nodenum_);
        };
    };
}
#endif //SMARTDONGLIB_MULTITREE_H
