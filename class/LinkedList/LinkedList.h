#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

void PrintIntArr(int *, int);

void InitLinkedList(struct Node *head);
void HeadInsert(struct Node *head, int data);
int HeadDelete(struct Node *head, int *data);
void PrintLinkedList(struct Node *head);
void TailInsert(struct Node *head, int data);
int TailDelete(struct Node *head, int *data);

#endif
