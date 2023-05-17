#include "shell.h"

/**
 * showEnv - shows the current environment in the shell
 *  @commandInfo: parameter or information about the command
 * Return: Always 0 and 1 when error
 */
int showEnv(info_t *commandInfo)
{
	printStrList(commandInfo->env);
	return (0);
}

/**
 * fetchEnv - This gets the value of an environment variable
 *  @commandInfo: parameter or information about the command
 * @name: the name of the environment variable
 * Return: the value of the environment variable
 */
char *fetchEnv(info_t *commandInfo, const char *name)
{
	list_n *node = commandInfo->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * updateEnv - Initialize a new environment variable,
 *             or modify an existing one
 *  @commandInfo: parameter or information about the command
 *  Return: Always 0 if successful and -1 otherwise
 */
int updateEnv(info_t *commandInfo)
{
	if (commandInfo->argc != 3)
	{
		errorPrintString("Incorrect number of arguements\n");
		return (1);
	}
	if (setEnv(commandInfo, commandInfo->argv[1], commandInfo->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnv - Remove an environment variable
 *  @commandInfo: parameter or information about the command
 * Return: Always 0 if successful and -1 otherwise
 */
int unsetEnv(info_t *commandInfo)
{
	int i;

	if (commandInfo->argc == 1)
	{
		errorPrintString("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= commandInfo->argc; i++)
		discardEnv(commandInfo, commandInfo->argv[i]);

	return (0);
}

/**
 * fillEnv - this populates env linked list used by command
 *  @commandInfo: parameter or information about the command
 * Return: Always 0 and 1 if otherwise
 */
int fillEnv(info_t *commandInfo)
{
	list_n *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		appendNode(&node, environ[i], 0);
	commandInfo->env = node;
	return (0);
}

