#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int data;
    struct Node *next;
};

int append_node(struct Node **head, int value)
{
    struct Node *new_node = malloc(sizeof(struct Node));

    if (new_node == NULL)
    {
        return 0;
    }

    new_node->data = value;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return 1;
    }

    struct Node *current = *head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = new_node;
    return 1;
}

void free_list(struct Node *head)
{
    struct Node *current = head;

    while (current != NULL)
    {
        struct Node *next_node = current->next;
        free(current);
        current = next_node;
    }
}

int count_nodes(struct Node *head)
{
    int count = 0;
    struct Node *current = head;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

int search_node(struct Node *head, int target)
{
    struct Node *current = head;

    while (current != NULL)
    {
        if (current->data == target)
        {
            return 1;
        }

        current = current->next;
    }

    return 0;
}

int delete_node(struct Node **head, int target)
{
    if (*head == NULL)
    {
        return 0;
    }

    if ((*head)->data == target)
    {
        struct Node *old_head = *head;
        *head = (*head)->next;
        free(old_head);
        return 1;
    }

    struct Node *previous = *head;
    struct Node *current =(*head)->next;

    while (current != NULL)
    {
        if (current->data == target)
        {
            previous->next = current->next;
            free(current);
            return 1;
        }

        previous = current;
        current = current->next;
    }

    return 0;
}

int main (void)
{
    struct Node *head = NULL;

    if (!append_node(&head, 10))
    {
        printf("Failed to add node with value 10.\n");
        free_list(head);
        return 1;
    }

    if (!append_node(&head, 20))
    {
        printf("Failed to add node with value 20.\n");
        free_list(head);
        return 1;
    }

    if (!append_node(&head, 30))
    {
        printf("Failed to add node with value 30.\n");
        free_list(head);
        return 1;
    }

    if (!append_node(&head, 40))
    {
        printf("Failed to add node with value 40.\n");
        free_list(head);
        return 1;
    }

    struct Node *current = head;

    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
    printf("Total nodes: %d\n", count_nodes(head));

    int target = 99;

    if (delete_node(&head, target))
    {
        printf("Value %d deleted successfully.\n", target);
    }
    else
    {
        printf("Value %d not found.\n", target);
    }

    printf("List after deletion: ");

    current = head;

    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
    printf("Node count after deletion: %d\n", count_nodes(head));

    free_list(head);

    return 0;
}
