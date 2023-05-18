#include "shell.h"

/**
 * push_node - adds a node to the start of the list in the the program
 * @head: address of pointer to head node in the program
 * @str: the string field of node
 * @num: node index used by history
 *
 * Return: size of list else nothing on failure
 */
list_n *push_node(list_n **head, const char *str, int num)
{
    list_n *nhead;

    if (!head)
        return (NULL);
    nhead = malloc(sizeof(list_n));
    if (!nhead)
        return (NULL);
    resetMatrix((void *)nhead, 0, sizeof(list_n));
    nhead->num = num;
    if (str)
    {
        nhead->str = strdupl(str);
        if (!nhead->str)
        {
            free(nhead);
            return (NULL);
        }
    }
    nhead->next = *head;
    *head = nhead;
    return (nhead);
}

/**
 * appendNode - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_n *appendNode(list_n **head, const char *str, int num)
{
    list_n *new_node, *node;

    if (!head)
        return (NULL);

    node = *head;
    new_node = malloc(sizeof(list_n));
    if (!new_node)
        return (NULL);
    resetMatrix((void *)new_node, 0, sizeof(list_n));
    new_node->num = num;
    if (str)
    {
        new_node->str = strdupl(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;
    return (new_node);
}

/**
 * listPrint - This prints only the string element of a list_n linked list
 * @h: pointer to first node in the program
 *
 * Return: size of list
 */
size_t listPrint(const list_n *h)
{
    size_t i = 0;

    while (h)
    {
        printString(h->str ? h->str : "(nil)");
        printString("\n");
        h = h->next;
        i++;
    }
    return (i);
}

/**
 * eraseNodeAtIndex - deletes node at given index in the list
 * @head: address of pointer to first node in the program
 * @index: This is the index of node to delete
 *
 * Return: 1 on success, else 0 on failure
 */
int eraseNodeAtIndex(list_n **head, unsigned int index)
{
    list_n *node, *prevPtr;
    unsigned int i = 0;

    if (!head || !*head)
        return (0);

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return (1);
    }
    node = *head;
    while (node)
    {
        if (i == index)
        {
            prevPtr->next = node->next;
            free(node->str);
            free(node);
            return (1);
        }
        i++;
        prevPtr = node;
        node = node->next;
    }
    return (0);
}

/**
 * clear_list - frees all nodes of a list
 * @headPtr: address of pointer to head node in the program
 *
 * Return: void if nothing
 */
void clear_list(list_n **headPtr)
{
    list_n *node, *next_node, *head;

    if (!headPtr || !*headPtr)
        return;
    head = *headPtr;
    node = head;
    while (node)
    {
        next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }
    *headPtr = NULL;
}

