#include "../include/lab3.h"
void print_list(node *head)
{
    node *ptr = head;
    while (ptr != NULL)
    {
        if (ptr->next == NULL) printf("%d", ptr->data);
        else printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

node *create_node(int d) 
{
    node *res = malloc(sizeof(node));
    res->data = d;
    res->next = NULL;
    return res;
}

void free_list(node *head)
{
    node *ptr = head;
    while (ptr != NULL) 
    {
        node *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}

void add_node(node **head, int value)
{
    node *new_node = create_node(value);
    
    if (*head == NULL) *head = new_node; 
    else
    {
        node *ptr = *head;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
}

int contains(node *head, int value)
{
    node *ptr = head;
    while (ptr != NULL)
    {
        if (ptr->data == value) return 1;
        ptr = ptr->next;
    }
    return 0;
}

int main3()
{
    int length = 0;
    node *head = NULL;

    printf("Введите длину списка: ");
    scanf("%d", &length);
    printf("Введите список длины %d: ", length);
    
    for (int i = 0; i < length; i++)
    {
        int value;
        scanf("%d", &value);
        if (!contains(head, value)) add_node(&head, value);
    }
    
    printf("Список без повторений: ");
    print_list(head);
    free_list(head);
    return 0;
}
