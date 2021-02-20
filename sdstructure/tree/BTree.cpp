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
        node->isleaf_ = true;     //Ĭ��ΪҶ��

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
        // �½ڵ��is_leaf��child��ͬ��key�ĸ���ΪM-1
        new_child->isleaf_ = child->isleaf_;
        new_child->validnum_ = MINDEGREE - 1;

        // ��child��벿�ֵ�key�������½ڵ�
        for (int i = 0; i < MINDEGREE - 1; i++) {
            new_child->key_[i] = child->key_[i + MINDEGREE];
        }

        // ���child����Ҷ�ӣ�����Ҫ��ָ�뿽��ȥ��ָ��Ƚڵ��1
        if (false == new_child->isleaf_) {
            for (int i = 0; i < MINDEGREE; i++) {
                new_child->ptr_[i] = child->ptr_[i + MINDEGREE];
            }
        }

        child->validnum_ = MINDEGREE - 1;

        // child���м�ڵ���Ҫ����parent��pos��������parent��key��pointer
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

// ִ�иò���ʱ��node->num < 2M-1 
    void BTree::insertPartNode(sMultiTreeNode *node, int target) {
        if (1 == node->isleaf_) {
            // �����Ҷ�����ҵ���ֱ��ɾ��
            int pos = node->validnum_;
            while (pos >= 1 && target < node->key_[pos - 1]) {
                node->key_[pos] = node->key_[pos - 1];
                pos--;
            }

            node->key_[pos] = target;
            node->validnum_ += 1;
            nodenum_ += 1;

        } else {
            // ���Ų���·���½�
            int pos = node->validnum_;
            while (pos > 0 && target < node->key_[pos - 1]) {
                pos--;
            }

            if (2 * MINDEGREE - 1 == node->ptr_[pos]->validnum_) {
                // ���·���������ڵ������
                splitChild(node, pos, node->ptr_[pos]);
                if (target > node->key_[pos]) {
                    pos++;
                }
            }

            insertPartNode(node->ptr_[pos], target);
        }
    }

//�������
    sMultiTreeNode *BTree::insertNode(sMultiTreeNode *root, int target) {
        if (NULL == root) {
            return NULL;
        }

        // �Ը��ڵ�����⴦������������ģ�Ψһʹ�������ߵ�����
        // ������һ���µ�
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

// ��y��root->k[pos], z�ϲ���y�ڵ㣬���ͷ�z�ڵ㣬y,z����M-1���ڵ�
    void BTree::mergeChild(sMultiTreeNode *root, int pos, sMultiTreeNode *y, sMultiTreeNode *z) {
        // ��z�нڵ㿽����y�ĺ�벿��
        y->validnum_ = 2 * MINDEGREE - 1;
        for (int i = MINDEGREE; i < 2 * MINDEGREE - 1; i++) {
            y->key_[i] = z->key_[i - MINDEGREE];
        }
        y->key_[MINDEGREE - 1] = root->key_[pos];// k[pos]�½�Ϊy���м�ڵ�

        // ���z��Ҷ�ӣ���Ҫ����pointer
        if (false == z->isleaf_) {
            for (int i = MINDEGREE; i < 2 * MINDEGREE; i++) {
                y->ptr_[i] = z->ptr_[i - MINDEGREE];
            }
        }

        // k[pos]�½���y�У�����key��pointer
        for (int j = pos + 1; j < root->validnum_; j++) {
            root->key_[j - 1] = root->key_[j];
            root->ptr_[j] = root->ptr_[j + 1];
        }

        root->validnum_ -= 1;
        free(z);
    }

/************  ɾ������   **************
*
��ɾ��B���ڵ�ʱ��Ϊ�˱�����ݣ���������Ҫ�ϲ��Ľڵ�ʱ������ִ�кϲ���B����ɾ���㷨���£���root��Ҷ�ӽڵ㰴��search���ɱ�����
��1��  ���target��Ҷ�ڵ�x�У���ֱ�Ӵ�x��ɾ��target�������2���ͣ�3���ᱣ֤����Ҷ�ӽڵ��ҵ�targetʱ���϶��ܽ�ڵ��ϲ��ɹ����������𸸽ڵ�Ĺؼ��ָ�������t-1��
��2��  ���target�ڷ�֧�ڵ�x�У�
��a��  ���x�����֧�ڵ�y���ٰ���t���ؼ��֣����ҳ�y�����ҵĹؼ���prev�����滻target������y�еݹ�ɾ��prev��
��b��  ���x���ҷ�֧�ڵ�z���ٰ���t���ؼ��֣����ҳ�z������Ĺؼ���next�����滻target������z�еݹ�ɾ��next��
��c��  �������y��z��ֻ��t-1���ؼ��֣���targe��z�ϲ���y�У�ʹ��y��2t-1���ؼ��֣��ٴ�y�еݹ�ɾ��target��
��3��  ����ؼ��ֲ��ڷ�֧�ڵ�x�У����Ȼ��x��ĳ����֧�ڵ�p[i]�У����p[i]�ڵ�ֻ��t-1���ؼ��֡�
��a��  ���p[i-1]ӵ������t���ؼ��֣���x��ĳ���ؼ��ֽ���p[i]�У���p[i-1]�����ڵ�������x�С�
��b��  ���p[i+1]ӵ������t���ؼ��֣���x��ĳ���ؼ��ֽ���p[i]�У���p[i+1]����С�ؼ���������x����
��c��  ���p[i-1]��p[i+1]��ӵ��t-1���ؼ��֣���p[i]������һ���ֵܺϲ�����x��һ���ؼ��ֽ����ϲ��Ľڵ��У���Ϊ�м�ؼ��֡�
* 
*/

// ɾ�����
    sMultiTreeNode *BTree::deleteNode(sMultiTreeNode *root, int target) {
        // ���⴦������ֻ��������Ů����������Ů�Ĺؼ��ָ�����ΪM-1ʱ���ϲ�����������Ů
        // ����Ψһ�ܽ������ߵ�����
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

// root�����и�t���ؼ��֣���֤�������
    void BTree::deletePartNode(sMultiTreeNode *root, int target) {
        if (true == root->isleaf_) {
            // �����Ҷ�ӽڵ㣬ֱ��ɾ��
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
                // ����ڷ�֧�ڵ��ҵ�target
                y = root->ptr_[i];
                z = root->ptr_[i + 1];
                if (y->validnum_ > MINDEGREE - 1) {
                    // ������֧�ؼ��ֶ���M-1�����ҵ����֧�����ҽڵ�prev���滻target
                    // �������֧�еݹ�ɾ��prev,���2��a)
                    int pre = maxKey(y);
                    root->key_[i] = pre;
                    deletePartNode(y, pre);
                } else if (z->validnum_ > MINDEGREE - 1) {
                    // ����ҷ�֧�ؼ��ֶ���M-1�����ҵ��ҷ�֧������ڵ�next���滻target
                    // �����ҷ�֧�еݹ�ɾ��next,���2(b)
                    int next = minKey(z);
                    root->key_[i] = next;
                    deletePartNode(z, next);
                } else {
                    // ������֧�ڵ�����ΪM-1����ϲ���y������y�еݹ�ɾ��target,���2(c)
                    mergeChild(root, i, y, z);
                    deleteNode(y, target);
                }
            } else {
                // �ڷ�֧û���ҵ����϶��ڷ�֧���ӽڵ���
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
                        // ���ڽӽڵ�ؼ��ָ�������M-1
                        //���3(a)
                        rightShiftMaxkeyTopos(root, i - 1, p, y);
                    } else if (i < root->validnum_ && z->validnum_ > MINDEGREE - 1) {
                        // ���ڽӽڵ�ؼ��ָ�������M-1
                        // ���3(b)
                        leftShiftMinkeyTopos(root, i, y, z);
                    } else if (i > 0) {
                        // ���3��c)
                        mergeChild(root, i - 1, p, y); // note
                        y = p;
                    } else {
                        // ���3(c)
                        mergeChild(root, i, y, z);
                    }
                    deletePartNode(y, target);
                } else {
                    deletePartNode(y, target);
                }
            }

        }
    }

//Ѱ��rightmost����rootΪ�������ؼ���
    int BTree::maxKey(sMultiTreeNode *root) {
        sMultiTreeNode *y = root;
        while (false == y->isleaf_) {
            y = y->ptr_[y->validnum_];
        }
        return y->key_[y->validnum_ - 1];
    }

// Ѱ��leftmost����rootΪ������С�ؼ���
    int BTree::minKey(sMultiTreeNode *root) {
        sMultiTreeNode *z = root;
        while (false == z->isleaf_) {
            z = z->ptr_[0];
        }
        return z->key_[0];
    }

// z��y��ڵ㣬��root->k[pos]�½���z����y�����ؼ���������root��pos��
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

// y���ڵ㣬��root->k[pos]�½���y����z����С�ؼ���������root��pos��
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
        // ���ж��ļ��Ƿ����
        // windows�£���io.h�ļ���linux���� unistd.h�ļ�
        // int access(const char *pathname, int mode);
        if (-1 == access("define.Bdb", F_OK)) {
            // ������ ,����
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