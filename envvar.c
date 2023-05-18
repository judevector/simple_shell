#include "shell.h"

/**
 * access_env - This returns the string array copy of our environment
 * @commandInfo: Structure containing potential arguments.
 * Return: Always 0 if successful
 */
char **access_env(info_t *commandInfo)
{
    if (!commandInfo->environ || commandInfo->envMutated)
    {
        commandInfo->environ = list2str(commandInfo->env);
        commandInfo->envMutated = 0;
    }

    return (commandInfo->environ);
}

/**
 * discardEnv - Remove an environment variable in the program
 * @commandInfo: Structure containing potential arguments. Used in the code
 *  Return: 1 on delete, else 0 otherwise
 * @var: the string env var property to be used
 */
int discardEnv(info_t *commandInfo, char *var)
{
    list_n *node = commandInfo->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = starts_with(node->str, var);
        	if (p && *p == '=')
        	{
            	commandInfo->envMutated = eraseNodeAtIndex(&(commandInfo->env), i);
            	i = 0;
            	node = commandInfo->env;
            	continue;
        	}
        node = node->next;
        i++;
    }
    return (commandInfo->envMutated);
}

/**
 * setEnv - Initialize a new environment variable,
 *             or modify an existing one
 * @commandInfo: Structure containing potential arguments. Used in the command
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0 and 1 if error occurs
 */
int setEnv(info_t *commandInfo, char *var, char *value)
{
    char *buf = NULL;
    list_n *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = malloc(str_length(var) + str_length(value) + 2);
    if (!buf)
        return (1);
    str_copy(buf, var);
    str_concat(buf, "=");
    str_concat(buf, value);
    node = commandInfo->env;
    while (node)
    {
        p = starts_with(node->str, var);
        	if (p && *p == '=')
        	{
            	free(node->str);
            	node->str = buf;
            	commandInfo->envMutated = 1;
            	return (0);
        	}
        node = node->next;
    }
    appendNode(&(commandInfo->env), buf, 0);
    free(buf);
    commandInfo->envMutated = 1;
    return (0);
}

