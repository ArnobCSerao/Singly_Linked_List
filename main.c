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

int insert_at_position(struct Node **head, int value, int position)
{
    if (position < 1)
    {
        return 0;
    }

    struct Node *new_node = malloc(sizeof(struct Node));

    if (new_node == NULL)
    {
        return 0;
    }

    new_node->data = value;
    new_node->next = NULL;

    if (position == 1)
    {
        new_node->next = *head;
        *head = new_node;
        return 1;
    }

    struct Node *current = *head;

    for (int i = 1; i < position - 1; i++)
    {
        if (current == NULL)
        {
            free(new_node);
            return 0;
        }

        current = current->next;
    }

    if (current == NULL)
    {
        free(new_node);
        return 0;
    }

    new_node->next = current->next;
    current->next = new_node;

    return 1;
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

    if (insert_at_position(&head, 25, 3))
    {
        printf("Value 25 inserted successfully at position 3.\n");

    }
    else
    {
        printf("Insertion failed.\n");
    }

    printf("List after insertion: ");

    current = head;

    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
    printf("Node count after insertion: %d\n", count_nodes(head));

    if (insert_at_position(&head, 5, 1))
    {
        printf("Value 5 inserted successfully at position 1.\n");
    }
    else
    {
        printf("Insertion failed.\n");
    }

    printf("List after beginning insertion: ");

    current = head;

    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
    printf("Node count: %d\n", count_nodes(head));

    if (insert_at_position(&head, 50, 7))
    {
        printf("Value 50 inserted successfully at position 7.\n");
    }
    else
    {
        printf("Insertion failed.\n");
    }

    printf("List after end insertion: ");

    current = head;

    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
    printf("Node count: %d\n", count_nodes(head));

    if (insert_at_position(&head, 99, 9))
    {
        printf("Value 99 inserted successfully.\n");
    }
    else
    {
        printf("Invalid position. Insertion failed.\n");
    }

    printf("Node count after invalid insertion: %d\n", count_nodes(head));
    free_list(head);

    return 0;
}
