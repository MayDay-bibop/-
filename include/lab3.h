#ifndef LAB3_H
#define LAB3_H

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct node_
{
    int data;
    struct node_ *next;
} node;

void print_list(node *head);
node *create_node(int d);
void free_list(node *head);
void add_node(node **head, int value);
int contains(node *head, int value);
int main3();
#endif