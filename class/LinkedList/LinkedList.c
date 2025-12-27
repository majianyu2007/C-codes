#include "LinkedList.h"


void InitLinkedList(struct Node *head)
{
    head->data = 0;
    head->next = NULL;
}

void HeadInsert(struct Node *head, int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = head->next;
    head->next = newNode;
}

int HeadDelete(struct Node *head, int *data)
{
    if(head->next == NULL)
        return 0;
    struct Node *deleted = head->next;
    head->next = deleted->next; // head->next = head->next->next;
    deleted->next = NULL;
    *data = deleted->data;
    free(deleted);
    return 1;
}

void PrintLinkedList(struct Node *head)
{
    if(head->next == NULL)
        return;
    struct Node *p = head->next;
    while(p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    putchar('\n');
}

void TailInsert(struct Node *head, int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    struct Node *p = head;
    while(p->next != NULL)
        p = p->next;
    p->next = newNode;
}

int TailDelete(struct Node *head, int *data)
{
    if(head->next == NULL)
        return 0;
    struct Node *p = head;
    while(p->next->next != NULL)
        p = p->next;
    struct Node *deleted = p->next;
    p->next = NULL;
    *data = deleted->data;
    return 1;
}









