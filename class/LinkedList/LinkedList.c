#include "LinkedList.h"

void PrintIntArr(int *arr, int len)
{
    printf("[");
    for (int i = 0; i < len; i++)
    {
        if (i > 0) printf(", ");
        printf("%d", arr[i]);
    }
    printf("]");
}

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
    if (head->next == NULL)
        return 0;
    struct Node *temp = head->next;
    *data = temp->data;
    head->next = temp->next;
    free(temp);
    return 1;
}

void TailInsert(struct Node *head, int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    
    struct Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
}

int TailDelete(struct Node *head, int *data)
{
    if (head->next == NULL)
        return 0;
    
    struct Node *current = head;
    while (current->next->next != NULL)
    {
        current = current->next;
    }
    struct Node *temp = current->next;
    *data = temp->data;
    current->next = NULL;
    free(temp);
    return 1;
}

void PrintLinkedList(struct Node *head)
{
    printf("[");
    struct Node *current = head->next;
    int first = 1;
    while (current != NULL)
    {
        if (!first) printf(", ");
        printf("%d", current->data);
        current = current->next;
        first = 0;
    }
    printf("]");
}
