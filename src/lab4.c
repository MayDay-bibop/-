#include "../include/lab4.h"
struct Node* createNode(int key)
{
    struct Node* p = malloc(sizeof(struct Node));
    p->key = key; 
    p->size = 1;
    p->left = p->right = NULL;
    return p;
}

int getsize(struct Node* p)
{
    if(!p) return 0;
    return p->size;
}

void fixsize(struct Node* p)
{
    p->size = getsize(p->left) + getsize(p->right) + 1;
}

struct Node* rotateright(struct Node* p)
{
    struct Node* q = p->left;
    if(!q) return p;
    p->left = q->right;
    q->right = p;
    q->size = p->size;
    fixsize(p);
    return q;
}

struct Node* rotateleft(struct Node* q)
{
    struct Node* p = q->right;
    if(!p) return q;
    q->right = p->left;
    p->left = q;
    p->size = q->size;
    fixsize(q);
    return p;
}

struct Node* insertroot(struct Node* p, int k)
{
    if(!p) return createNode(k);
    if(k < p->key)
    {
        p->left = insertroot(p->left, k);
        return rotateright(p);
    }
    else
    {
        p->right = insertroot(p->right, k);
        return rotateleft(p);
    }
}

struct Node* insert(struct Node* p, int k)
{
    if(!p) return createNode(k);
    if(rand() % (p->size + 1) == 0)
        return insertroot(p, k);
    if(p->key > k)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    fixsize(p);
    return p;
}

void showTrunks(struct Trunk* p) 
{
    if(p == NULL) return;
    showTrunks(p->prev);
    printf("%s", p->str);
}

void printTree(struct Node* root, struct Trunk* prev, int isLeft) 
{
    if(root == NULL) return;

    char* prev_str = "     ";
    struct Trunk* trunk = (struct Trunk*)malloc(sizeof(struct Trunk));
    trunk->prev = prev;
    trunk->str = prev_str;

    printTree(root->right, trunk, true);

    if(!prev) 
    {
        trunk->str = "-----";
    }
    else if(isLeft) 
    {
        trunk->str = ".----";
        prev_str = "    |";
    }
    else 
    {
        trunk->str = "`----";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    printf(" %d\n", root->key);

    if(prev) prev->str = prev_str;
    trunk->str = "    |";

    printTree(root->left, trunk, false);
    free(trunk);
}

void deleteRoot(struct Node** root) 
{
    if (*root == NULL) {
        return;
    }
    
    deleteRoot(&(*root)->left);
    deleteRoot(&(*root)->right);
    free(*root);
    *root = NULL;
}
int nodeCount(struct Node* p) //подсчет узлов
{
    if(p == NULL) return 0;
    return 1 + nodeCount(p->left) + nodeCount(p->right);
}

int nodecnt = 0;

void nodeDiff(struct Node* p) //вычисление разницы
{
    if(p == NULL) return;
    
    int cntL = nodeCount(p->left);
    int cntR = nodeCount(p->right);
    int diff = cntL - cntR;
    nodecnt++;
    if(diff == 1 || diff == -1) 
        printf(" %d (%d); ", nodecnt, p->key);
    
    nodeDiff(p->left);
    nodeDiff(p->right);
}

int main4() 
{
    srand(time(NULL));
    FILE* fpin = fopen("tree.txt", "rt");
    if(!fpin) {
        printf("файл не открылся\n");
        return 1;
    }
    
    struct Node* root = NULL;
    int value;
    
    while(fscanf(fpin, "%d", &value) == 1) 
    {
        root = insert(root, value);
    }
    
    fclose(fpin);
    
    printf("вывод дерева:\n");
    printTree(root, NULL, false);
    printf("\nномера вершин у которых разница в потомках = 1:");
    nodeDiff(root);
    printf("\n");

    deleteRoot(&root);
    
    return 0;
}