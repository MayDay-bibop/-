#ifndef LAB4_H
#define LAB4_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define true 1
#define false 0

struct Trunk {
    struct Trunk* prev;
    char* str;
};

struct Node {
    int key;
    int size;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int key);
int getsize(struct Node* p);
void fixsize(struct Node* p);
struct Node* rotateright(struct Node* p);
struct Node* rotateleft(struct Node* q);
struct Node* insertroot(struct Node* p, int k);
struct Node* insert(struct Node* p, int k);
void showTrunks(struct Trunk* p);
void printTree(struct Node* root, struct Trunk* prev, int isLeft);
void deleteRoot(struct Node **root);
int main4();

#endif