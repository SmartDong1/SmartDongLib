#include "BTree.h"
#include <cstdlib>

#ifdef WIN32
	#include <io.h>
#endif

#ifdef LINUX
	#include <unistd.h>
#endif
namespace SmartDongLib {

    sMultiTreeNode *BTree::createNode() {
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
        node->isleaf_ = true;     //默认为叶子

        return node;
    }

    sMultiTreeNode *BTree::createRoot() {
        sMultiTreeNode *node = createNode();
        if (NULL == node) {
            return NULL;
        }
        return node;
    }

    int BTree::splitChild(sMultiTreeNode *parent, int pos, sMultiTreeNode *child) {
        sMultiTreeNode *new_child = createNode();
        if (NULL == new_child) {
            return -1;
        }
        // 新节点的is_leaf与child相同，key的个数为M-1
        new_child->isleaf_ = child->isleaf_;
        new_child->validnum_ = MINDEGREE - 1;

        // 将child后半部分的key拷贝给新节点
        for (int i = 0; i < MINDEGREE - 1; i++) {
            new_child->key_[i] = child->key_[i + MINDEGREE];
        }

        // 如果child不是叶子，还需要把指针拷过去，指针比节点多1
        if (false == new_child->isleaf_) {
            for (int i = 0; i < MINDEGREE; i++) {
                new_child->ptr_[i] = child->ptr_[i + MINDEGREE];
            }
        }

        child->validnum_ = MINDEGREE - 1;

        // child的中间节点需要插入parent的pos处，更新parent的key和pointer
        for (int i = parent->validnum_; i > pos; i--) {
            parent->ptr_[i + 1] = parent->ptr_[i];
        }
        parent->ptr_[pos + 1] = new_child;

        for (int i = parent->validnum_ - 1; i >= pos; i--) {
            parent->key_[i + 1] = parent->key_[i];
        }
        parent->key_[pos] = child->key_[MINDEGREE - 1];

        parent->validnum_ += 1;
        return 0;
    }

// 执行该操作时，node->num < 2M-1 
    void BTree::insertPartNode(sMultiTreeNode *node, int target) {
        if (1 == node->isleaf_) {
            // 如果在叶子中找到，直接删除
            int pos = node->validnum_;
            while (pos >= 1 && target < node->key_[pos - 1]) {
                node->key_[pos] = node->key_[pos - 1];
                pos--;
            }

            node->key_[pos] = target;
            node->validnum_ += 1;
            nodenum_ += 1;

        } else {
            // 沿着查找路径下降
            int pos = node->validnum_;
            while (pos > 0 && target < node->key_[pos - 1]) {
                pos--;
            }

            if (2 * MINDEGREE - 1 == node->ptr_[pos]->validnum_) {
                // 如果路径上有满节点则分裂
                splitChild(node, pos, node->ptr_[pos]);
                if (target > node->key_[pos]) {
                    pos++;
                }
            }

            insertPartNode(node->ptr_[pos], target);
        }
    }

//插入入口
    sMultiTreeNode *BTree::insertNode(sMultiTreeNode *root, int target) {
        if (NULL == root) {
            return NULL;
        }

        // 对根节点的特殊处理，如果根是满的，唯一使得树增高的情形
        // 先申请一个新的
        if (2 * MINDEGREE - 1 == root->validnum_) {
            sMultiTreeNode *node = createNode();
            if (NULL == node) {
                return root;
            }

            node->isleaf_ = 0;
            node->ptr_[0] = root;
            splitChild(node, 0, root);
            insertPartNode(node, target);
            return node;
        } else {
            insertPartNode(root, target);
            return root;
        }
    }

// 将y，root->k[pos], z合并到y节点，并释放z节点，y,z各有M-1个节点
    void BTree::mergeChild(sMultiTreeNode *root, int pos, sMultiTreeNode *y, sMultiTreeNode *z) {
        // 将z中节点拷贝到y的后半部分
        y->validnum_ = 2 * MINDEGREE - 1;
        for (int i = MINDEGREE; i < 2 * MINDEGREE - 1; i++) {
            y->key_[i] = z->key_[i - MINDEGREE];
        }
        y->key_[MINDEGREE - 1] = root->key_[pos];// k[pos]下降为y的中间节点

        // 如果z非叶子，需要拷贝pointer
        if (false == z->isleaf_) {
            for (int i = MINDEGREE; i < 2 * MINDEGREE; i++) {
                y->ptr_[i] = z->ptr_[i - MINDEGREE];
            }
        }

        // k[pos]下降到y中，更新key和pointer
        for (int j = pos + 1; j < root->validnum_; j++) {
            root->key_[j - 1] = root->key_[j];
            root->ptr_[j] = root->ptr_[j + 1];
        }

        root->validnum_ -= 1;
        free(z);
    }

/************  删除分析   **************
*
在删除B树节点时，为了避免回溯，当遇到需要合并的节点时就立即执行合并，B树的删除算法如下：从root向叶子节点按照search规律遍历：
（1）  如果target在叶节点x中，则直接从x中删除target，情况（2）和（3）会保证当再叶子节点找到target时，肯定能借节点或合并成功而不会引起父节点的关键字个数少于t-1。
（2）  如果target在分支节点x中：
（a）  如果x的左分支节点y至少包含t个关键字，则找出y的最右的关键字prev，并替换target，并在y中递归删除prev。
（b）  如果x的右分支节点z至少包含t个关键字，则找出z的最左的关键字next，并替换target，并在z中递归删除next。
（c）  否则，如果y和z都只有t-1个关键字，则将targe与z合并到y中，使得y有2t-1个关键字，再从y中递归删除target。
（3）  如果关键字不在分支节点x中，则必然在x的某个分支节点p[i]中，如果p[i]节点只有t-1个关键字。
（a）  如果p[i-1]拥有至少t个关键字，则将x的某个关键字降至p[i]中，将p[i-1]的最大节点上升至x中。
（b）  如果p[i+1]拥有至少t个关键字，则将x个某个关键字降至p[i]中，将p[i+1]的最小关键字上升至x个。
（c）  如果p[i-1]与p[i+1]都拥有t-1个关键字，则将p[i]与其中一个兄弟合并，将x的一个关键字降至合并的节点中，成为中间关键字。
* 
*/

// 删除入口
    sMultiTreeNode *BTree::deleteNode(sMultiTreeNode *root, int target) {
        // 特殊处理，当根只有两个子女，切两个子女的关键字个数都为M-1时，合并根与两个子女
        // 这是唯一能降低树高的情形
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

// root至少有个t个关键字，保证不会回溯
    void BTree::deletePartNode(sMultiTreeNode *root, int target) {
        if (true == root->isleaf_) {
            // 如果在叶子节点，直接删除
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
            if (i < root->validnum_ && target == root->key_[i]) {
                // 如果在分支节点找到target
                y = root->ptr_[i];
                z = root->ptr_[i + 1];
                if (y->validnum_ > MINDEGREE - 1) {
                    // 如果左分支关键字多于M-1，则找到左分支的最右节点prev，替换target
                    // 并在左分支中递归删除prev,情况2（a)
                    int pre = maxKey(y);
                    root->key_[i] = pre;
                    deletePartNode(y, pre);
                } else if (z->validnum_ > MINDEGREE - 1) {
                    // 如果右分支关键字多于M-1，则找到右分支的最左节点next，替换target
                    // 并在右分支中递归删除next,情况2(b)
                    int next = minKey(z);
                    root->key_[i] = next;
                    deletePartNode(z, next);
                } else {
                    // 两个分支节点数都为M-1，则合并至y，并在y中递归删除target,情况2(c)
                    mergeChild(root, i, y, z);
                    deleteNode(y, target);
                }
            } else {
                // 在分支没有找到，肯定在分支的子节点中
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
                        // 左邻接节点关键字个数大于M-1
                        //情况3(a)
                        rightShiftMaxkeyTopos(root, i - 1, p, y);
                    } else if (i < root->validnum_ && z->validnum_ > MINDEGREE - 1) {
                        // 右邻接节点关键字个数大于M-1
                        // 情况3(b)
                        leftShiftMinkeyTopos(root, i, y, z);
                    } else if (i > 0) {
                        // 情况3（c)
                        mergeChild(root, i - 1, p, y); // note
                        y = p;
                    } else {
                        // 情况3(c)
                        mergeChild(root, i, y, z);
                    }
                    deletePartNode(y, target);
                } else {
                    deletePartNode(y, target);
                }
            }

        }
    }

//寻找rightmost，以root为根的最大关键字
    int BTree::maxKey(sMultiTreeNode *root) {
        sMultiTreeNode *y = root;
        while (false == y->isleaf_) {
            y = y->ptr_[y->validnum_];
        }
        return y->key_[y->validnum_ - 1];
    }

// 寻找leftmost，以root为根的最小关键字
    int BTree::minKey(sMultiTreeNode *root) {
        sMultiTreeNode *z = root;
        while (false == z->isleaf_) {
            z = z->ptr_[0];
        }
        return z->key_[0];
    }

// z向y借节点，将root->k[pos]下降至z，将y的最大关键字上升至root的pos处
    void BTree::rightShiftMaxkeyTopos(sMultiTreeNode *root, int pos,
                                      sMultiTreeNode *y, sMultiTreeNode *z) {
        z->validnum_ += 1;
        for (int i = z->validnum_ - 1; i > 0; i--) {
            z->key_[i] = z->key_[i - 1];
        }
        z->key_[0] = root->key_[pos];
        root->key_[pos] = y->key_[y->validnum_ - 1];

        if (false == z->isleaf_) {
            for (int i = z->validnum_; i > 0; i--) {
                z->ptr_[i] = z->ptr_[i - 1];
            }
            z->ptr_[0] = y->ptr_[y->validnum_];
        }

        y->validnum_ -= 1;
    }

// y向借节点，将root->k[pos]下降至y，将z的最小关键字上升至root的pos处
    void BTree::leftShiftMinkeyTopos(sMultiTreeNode *root, int pos,
                                     sMultiTreeNode *y, sMultiTreeNode *z) {
        y->validnum_ += 1;
        y->key_[y->validnum_ - 1] = root->key_[pos];
        root->key_[pos] = z->key_[0];

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

    void BTree::inOrderTraversal(sMultiTreeNode *root) {
        if (NULL != root) {
            inOrderTraversal(root->ptr_[0]);
            for (int i = 0; i < root->validnum_; i++) {
                printf("%d ", root->key_[i]);
                inOrderTraversal(root->ptr_[i + 1]);
            }
        }
    }

    void BTree::levelTraversal(sMultiTreeNode *root) {
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

    void BTree::Save(sMultiTreeNode *root) {
        /*
        storage_struct ss;

        // malloc len space
        ss.len = partNodenum_;
        ss.snode = (storage_node *)malloc(sizeof(storage_node)*ss.len);

        ss.snode[0].bnode = *root;
        for(int i=1;i<ss.len;i++)
        {
            btree_node *node = createNode();
            if(NULL == node) {
                return;
            }
        }

    //	fwrite(&ss,sizeof(ss),1,pfile);
    */
    }

    BTree::BTree(void) {
        // 先判断文件是否存在
        // windows下，是io.h文件，linux下是 unistd.h文件
        // int access(const char *pathname, int mode);
        if (-1 == access("define.Bdb", F_OK)) {
            // 不存在 ,创建
            //   	pfile = fopen("bstree.b","w");
            roots = createRoot();
        } else {
//	   	pfile = fopen("bstree.b","r+");
            roots = createRoot();
//	   	fread(roots,sizeof(roots),1,pfile);
        }

    }


    BTree::~BTree(void) {
//	fclose(pfile); 
    }

}