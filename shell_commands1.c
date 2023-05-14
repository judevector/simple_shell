#include "shell.h"

/**
 * commandHistory - shows the history list, one command per line,
 *           with line numbers starting at 0 before each command.
 * @commandInfo: Arrangement with potential arguments.
 *          used to preserve the prototype of the constant function.
 *  Return: Always 0
 */
int commandHistory(info_t *commandInfo)
{
	displayList(commandInfo->history);
	return (0);
}

/**
 * removeAlias - changes the alias to a string
 * @commandInfo: a struct with parameters
 * @string: the alias string
 *
 * Return: Always 0 if successful, otherwise 1 if unsuccessful
 */
int removeAlias(info_t *commandInfo, char *string)
{
	char *ptr, c;
	int ret;

	ptr = findCharacter(string, '=');
	if (!ptr)
	return (1);
	c = *ptr;
	*ptr = 0;
	ret = eraseNodeAtPosition(&(commandInfo->alias),
	findNodeIndex(commandInfo->alias, startsWithNode
	(commandInfo->alias, string, -1)));
    *ptr = c;
    return (ret);
}

/**
 * createAlias - creates alias to string
 * @commandInfo: parameter struct
 * @string: the string alias used in the command
 *
 * Return: Always 0 on success, otherwise 1 on error
 */
int createAlias(info_t *commandInfo, char *string)
{
    char *ptr;

    ptr = findCharacter(string, '=');
    if (!ptr)
        return (1);
    if (!*++ptr)
        return (removeAlias(commandInfo, string));

    removeAlias(commandInfo, string);
    return (insertNodeAtEnd(&(commandInfo->alias), string, 0) == NULL);
}

/**
 * displayAlias - displays an alias string
 * @node: the alias node in the command
 *
 * Return: Always 0 on success, 1 on error
 */
int displayAlias(list_t *node)
{
    char *ptr = NULL, *a = NULL;

    if (node)
    {
        ptr = findCharacter(node->string, '=');
        for (a = node->string; a <= ptr; a++)
            printChar(*a);
        printChar('\'');
        _puts(ptr + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * aliasTable - myalias mimics the built-in alias (man alias)
 * @commandInfo: Structure containing potential
 *             arguments used to retain the prototype of the constant function
 *  Return: Always 0 and 1 when error is encountered
 */
int aliasTable(info_t *commandInfo)
{
    int n = 0;
    char *ptr = NULL;
    list_t *node = NULL;

    if (commandInfo->argc == 1)
    {
        node = commandInfo->alias;
        while (node)
        {
            displayAlias(node);
            node = node->next;
        }
        return (0);
    }
    for (n = 1; commandInfo->argv[n]; n++)
    {
        ptr = findCharacter(commandInfo->argv[n], '=');
        if (ptr)
            createAlias(commandInfo, commandInfo->argv[n]);
        else
            displayAlias(startsWithNode(commandInfo->alias, commandInfo->argv[n], '='));
    }

    return (0);
}

