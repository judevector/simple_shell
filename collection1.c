#include "shell.h"

/**
 * get_length - determines length of linked list in the program
 * @h: pointer to first node in linked list
 *
 * Return: size of list in bytes
 */
size_t get_length(const list_n *h)
{
    size_t i = 0;

    while (h)
    {
        h = h->next;
        i++;
    }
    return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings of the list->str
 */
char **list2str(list_n *head)
{
    list_n *node = head;
    size_t i = get_length(head), j;
    char **strs;
    char *str;

    if (!head || !i)
        return (NULL);
    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (NULL);
    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(str_length(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (NULL);
        }

        str = str_copy(str, node->str);
        strs[i] = str;
    }
    strs[i] = NULL;
    return (strs);
}

/**
 * listPrint - prints all elements of a list_t linked list
 * @h: pointer to first node in the list
 *
 * Return: size of list used for printing
 */
size_t listPrint(const list_n *h)
{
    size_t i = 0;

    while (h)
    {
        printString(convertNum(h->num, 10, 0));
        writeChar(':');
        writeChar(' ');
        printString(h->str ? h->str : "(nil)");
        printString("\n");
        h = h->next;
        i++;
    }
    return (i);
}

/**
 * startsWith - returns node whose string starts with prefix in the given string
 * @node: pointer to list head used in the program
 * @prefix: string to match in the program
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_n *startsWith(list_n *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return (node);
        node = node->next;
    }
    return (NULL);
}

/**
 * findNodeIndex - gets the first index of a node
 * @header: This is the pointer to list head
 * @node: This is the pointer to the node
 *
 * Return: index of node or -1 else otherwise.
 */
ssize_t findNodeIndex(list_n *header, list_n *node)
{
    size_t i = 0;

    while (header)
    {
        if (header == node)
            return (i);
        header = header->next;
        i++;
    }
    return (-1);
}

