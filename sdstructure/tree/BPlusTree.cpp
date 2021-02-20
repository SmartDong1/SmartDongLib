#include "BPlusTree.h"
#include "btreestruct.h"
#include <cstdio>
#include <cstdlib>

#ifdef WIN32
	#include <io.h>
#endif

#ifdef LINUX
	#include <unistd.h>
#endif
namespace SmartDongLib {

    sMultiTreeNode *BPlusTree::createNode() {
        sMultiTreeNode *node = (sMultiTreeNode *) malloc(sizeof(sMultiTreeNode));
        if (NULL == node) {
            return NULL;
        }

        for (int i = 0; i < 2 * MINDEGREE - 1; i++) {
            node->key_[i] = 0;
        }

        for (int i = 0; i < 2 * MINDEGREE; i++) {
            node->ptr_[i] = NULL;
        }

        node->validnum_ = 0;
        node->isleaf_ = true;
        node->prev_ = NULL;
        node->next_ = NULL;
        return node;
    }

    sMultiTreeNode *BPlusTree::createRoot() {
        sMultiTreeNode *node = createNode();
        if (NULL == node) {
            return NULL;
        }

        node->next_ = node;
        node->prev_ = node;

        return node;
    }

    int BPlusTree::splitChild(sMultiTreeNode *parent, int pos, sMultiTreeNode *child) {
        sMultiTreeNode *new_child = createNode();
        if (NULL == new_child) {
            return -1;
        }

        new_child->isleaf_ = child->isleaf_;
        new_child->validnum_ = MINDEGREE - 1;

        for (int i = 0; i < MINDEGREE - 1; i++) {
            new_child->key_[i] = child->key_[i + MINDEGREE];
        }

        if (false == new_child->isleaf_) {
            for (int i = 0; i < MINDEGREE; i++) {
                new_child->ptr_[i] = child->ptr_[i + MINDEGREE];
            }
        }

        child->validnum_ = MINDEGREE - 1;
        if (true == child->isleaf_) {
            child->validnum_++;  // if leaf, keep the middle ele, put it in the left
        }

        for (int i = parent->validnum_; i > pos; i--) {
            parent->ptr_[i + 1] = parent->ptr_[i];
        }
        parent->ptr_[pos + 1] = new_child;

        for (int i = parent->validnum_ - 1; i >= pos; i--) {
            parent->key_[i + 1] = parent->key_[i];
        }
        parent->key_[pos] = child->key_[MINDEGREE - 1];

        parent->validnum_ += 1;

        // update link
        if (true == child->isleaf_) {
            new_child->next_ = child->next_;
            child->next_->prev_ = new_child;
            new_child->prev_ = child;
            child->next_ = new_child;
        }
        return 1;
    }

    void BPlusTree::insertPartNode(sMultiTreeNode *node, int target) {
        if (true == node->isleaf_) {
            int pos = node->validnum_;
            while (pos >= 1 && target < node->key_[pos - 1]) {
                node->key_[pos] = node->key_[pos - 1];
                pos--;
            }

            node->key_[pos] = target;
            node->validnum_ += 1;
            nodenum_ += 1;

        } else {
            int pos = node->validnum_;
            while (pos > 0 && target < node->key_[pos - 1]) {
                pos--;
            }

            if (2 * MINDEGREE - 1 == node->ptr_[pos]->validnum_) {
                splitChild(node, pos, node->ptr_[pos]);
                if (target > node->key_[pos]) {
                    pos++;
                }
            }

            insertPartNode(node->ptr_[pos], target);
        }
    }

    sMultiTreeNode *BPlusTree::insertNode(sMultiTreeNode *root, int target) {
        if (NULL == root) {
            return NULL;
        }

        if (2 * MINDEGREE - 1 == root->validnum_) {
            sMultiTreeNode *node = createNode();
            if (NULL == node) {
                return root;
            }

            node->isleaf_ = false;
            node->ptr_[0] = root;
            splitChild(node, 0, root);
            insertPartNode(node, target);
            return node;
        } else {
            insertPartNode(root, target);
            return root;
        }
    }

    void BPlusTree::mergeChild(sMultiTreeNode *root, int pos, sMultiTreeNode *y, sMultiTreeNode *z) {
        if (true == y->isleaf_) {
            y->validnum_ = 2 * MINDEGREE - 2;
            for (int i = MINDEGREE; i < 2 * MINDEGREE - 1; i++) {
                y->key_[i - 1] = z->key_[i - MINDEGREE];
            }
        } else {
            y->validnum_ = 2 * MINDEGREE - 1;
            for (int i = MINDEGREE; i < 2 * MINDEGREE - 1; i++) {
                y->key_[i] = z->key_[i - MINDEGREE];
            }
            y->key_[MINDEGREE - 1] = root->key_[pos];
            for (int i = MINDEGREE; i < 2 * MINDEGREE; i++) {
                y->ptr_[i] = z->ptr_[i - MINDEGREE];
            }
        }

        for (int j = pos + 1; j < root->validnum_; j++) {
            root->key_[j - 1] = root->key_[j];
            root->ptr_[j] = root->ptr_[j + 1];
        }

        root->validnum_ -= 1;

        // update link
        if (true == y->isleaf_) {
            y->next_ = z->next_;
            z->next_->prev_ = y;
        }

        free(z);
    }

    sMultiTreeNode *BPlusTree::deleteNode(sMultiTreeNode *root, int target) {
        if (1 == root->validnum_) {
            sMultiTreeNode *y = root->ptr_[0];
            sMultiTreeNode *z = root->ptr_[1];
            if (NULL != y && NULL != z &&
                MINDEGREE - 1 == y->validnum_ && MINDEGREE - 1 == z->validnum_) {
                mergeChild(root, 0, y, z);
                free(root);
                deletePartNode(y, target);
                return y;
            } else {
                deletePartNode(root, target);
                return root;
            }
        } else {
            deletePartNode(root, target);
            return root;
        }
    }

    void BPlusTree::deletePartNode(sMultiTreeNode *root, int target) {
        if (true == root->isleaf_) {
            int i = 0;
            while (i < root->validnum_ && target > root->key_[i]) i++;
            if (target == root->key_[i]) {
                for (int j = i + 1; j < 2 * MINDEGREE - 1; j++) {
                    root->key_[j - 1] = root->key_[j];
                }
                root->validnum_ -= 1;
                nodenum_ -= 1;

            } else {
                printf("target not found\n");
            }
        } else {
            int i = 0;
            sMultiTreeNode *y = NULL, *z = NULL;
            while (i < root->validnum_ && target > root->key_[i]) i++;

            y = root->ptr_[i];
            if (i < root->validnum_) {
                z = root->ptr_[i + 1];
            }
            sMultiTreeNode *p = NULL;
            if (i > 0) {
                p = root->ptr_[i - 1];
            }

            if (y->validnum_ == MINDEGREE - 1) {
                if (i > 0 && p->validnum_ > MINDEGREE - 1) {
                    rightShiftMaxkeyTopos(root, i - 1, p, y);
                } else if (i < root->validnum_ && z->validnum_ > MINDEGREE - 1) {
                    leftShiftMinkeyTopos(root, i, y, z);
                } else if (i > 0) {
                    mergeChild(root, i - 1, p, y);
                    y = p;
                } else {
                    mergeChild(root, i, y, z);
                }
                deletePartNode(y, target);
            } else {
                deletePartNode(y, target);
            }
        }
    }

    int BPlusTree::maxKey(sMultiTreeNode *root) {
        sMultiTreeNode *y = root;
        while (false == y->isleaf_) {
            y = y->ptr_[y->validnum_];
        }
        return y->key_[y->validnum_ - 1];
    }

    int BPlusTree::minKey(sMultiTreeNode *root) {
        sMultiTreeNode *z = root;
        while (false == z->isleaf_) {
            z = z->ptr_[0];
        }
        return z->key_[0];
    }

    void BPlusTree::rightShiftMaxkeyTopos(sMultiTreeNode *root, int pos,
                                          sMultiTreeNode *y, sMultiTreeNode *z) {
        z->validnum_ += 1;

        if (false == z->isleaf_) {
            z->key_[0] = root->key_[pos];
            root->key_[pos] = y->key_[y->validnum_ - 1];
        } else {
            z->key_[0] = y->key_[y->validnum_ - 1];
            root->key_[pos] = y->key_[y->validnum_ - 2];
        }

        for (int i = z->validnum_ - 1; i > 0; i--) {
            z->key_[i] = z->key_[i - 1];
        }

        if (false == z->isleaf_) {
            for (int i = z->validnum_; i > 0; i--) {
                z->ptr_[i] = z->ptr_[i - 1];
            }
            z->ptr_[0] = y->ptr_[y->validnum_];
        }

        y->validnum_ -= 1;
    }

    void BPlusTree::leftShiftMinkeyTopos(sMultiTreeNode *root, int pos,
                                         sMultiTreeNode *y, sMultiTreeNode *z) {
        y->validnum_ += 1;

        if (!z->isleaf_) {
            y->key_[y->validnum_ - 1] = root->key_[pos];
            root->key_[pos] = z->key_[0];
        } else {
            y->key_[y->validnum_ - 1] = z->key_[0];
            root->key_[pos] = z->key_[0];
        }

        for (int j = 1; j < z->validnum_; j++) {
            z->key_[j - 1] = z->key_[j];
        }

        if (!z->isleaf_) {
            y->ptr_[y->validnum_] = z->ptr_[0];
            for (int j = 1; j <= z->validnum_; j++) {
                z->ptr_[j - 1] = z->ptr_[j];
            }
        }

        z->validnum_ -= 1;
    }

    void BPlusTree::inOrderTraversal(sMultiTreeNode *root) {
        if (NULL != root) {
            inOrderTraversal(root->ptr_[0]);
            for (int i = 0; i < root->validnum_; i++) {
                printf("%d ", root->key_[i]);
                // 	fwrite(&root,sizeof(root),1,fp);
                inOrderTraversal(root->ptr_[i + 1]);
            }
        }
    }

    void BPlusTree::btree_linear_print(sMultiTreeNode *root) {
        if (NULL != root) {
            sMultiTreeNode *leftmost = root;
            while (false == leftmost->isleaf_) {
                leftmost = leftmost->ptr_[0];
            }

            sMultiTreeNode *iter = leftmost;
            do {
                for (int i = 0; i < iter->validnum_; i++) {
                    printf("%d ", iter->key_[i]);
                    //	fwrite(&root,sizeof(root),1,fp);
                }
                iter = iter->next_;
            } while (iter != leftmost);
            printf("\n");
        }
    }

    void BPlusTree::Save(sMultiTreeNode *root) {
//	fwrite(root,sizeof(root),1,pfile);
    }

    void BPlusTree::levelTraversal(sMultiTreeNode *root) {
        // just for simplicty, can't exceed 200 nodes in the tree
        sMultiTreeNode *queue[200] = {NULL};
        int front = 0;
        int rear = 0;

        queue[rear++] = root;

        while (front < rear) {
            sMultiTreeNode *node = queue[front++];

            printf("[");
            for (int i = 0; i < node->validnum_; i++) {
                printf("%d ", node->key_[i]);
            }
            printf("]");

            for (int i = 0; i <= node->validnum_; i++) {
                if (NULL != node->ptr_[i]) {
                    queue[rear++] = node->ptr_[i];
                }
            }
        }
        printf("\n");
    }

    void BPlusTree::linear_print() {
        btree_linear_print(roots);
    }

    BPlusTree::BPlusTree() {
        // 先判断文件是否存在
        // windows下，是io.h文件，linux下是 unistd.h文件
        // int access(const char *pathname, int mode);
        if (-1 == access("define.Bdb", F_OK)) {
            // 不存在 ,创建
//	   	pfile = fopen("bplus.bp","w");
            roots = createRoot();
        } else {
//	   	pfile = fopen("bplus.bp","r+");
            roots = createRoot();
//	   	fread(roots,sizeof(roots),1,pfile);
        }
    }

    BPlusTree::~BPlusTree(void) = default;
}
