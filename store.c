#include "shell.h"

/**
 * verify_chain - This test if current char in buffer is a chain delimeter
 * @commandInfo: the parameter struct used in the code
 * @buf: the char buffer used in the code
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int verify_chain(info_t *commandInfo, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		commandInfo->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		commandInfo->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		commandInfo->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * test_chain - checks we should continue chaining based on last status
 * @commandInfo: the parameter struct
 * @buf: the char buffer used in the code
 * @p: address of current position in buf used in the program
 * @i: starting position in buf used in the program
 * @len: length of buf used in the program
 *
 * Return: Void or NULL
 */
void test_chain(info_t *commandInfo, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (commandInfo->cmd_buf_type == CMD_AND)
	{
		if (commandInfo->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (commandInfo->cmd_buf_type == CMD_OR)
	{
		if (!commandInfo->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * resolve_alias - replaces an aliases in the tokenized string
 * @commandInfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int resolve_alias(info_t *commandInfo)
{
	int i;
	list_n *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = startsWith(commandInfo->alias, commandInfo->argv[0], '=');
		if (!node)
			return (0);
		free(commandInfo->argv[0]);
		p = findChar(node->str, '=');
		if (!p)
			return (0);
		p = strdupl(p + 1);
		if (!p)
			return (0);
		commandInfo->argv[0] = p;
	}
	return (1);
}

/**
 * apply_vars - This replaces vars in the tokenized string in the program
 * @commandInfo: the parameter struct or information used
 *
 * Return: 1 if replaced, 0 otherwise
 */
int apply_vars(info_t *commandInfo)
{
	int i = 0;
	list_n *node;

	for (i = 0; commandInfo->argv[i]; i++)
	{
		if (commandInfo->argv[i][0] != '$' || !commandInfo->argv[i][1])
			continue;

		if (!compareStrings(commandInfo->argv[i], "$?"))
		{
			replace_string(&(commandInfo->argv[i]),
					strdupl(convertNum(commandInfo->status, 10, 0)));
			continue;
		}
		if (!compareStrings(commandInfo->argv[i], "$$"))
		{
			replace_string(&(commandInfo->argv[i]),
					strdupl(convertNum(getpid(), 10, 0)));
			continue;
		}
		node = startsWith(commandInfo->env, &commandInfo->argv[i][1], '=');
		if (node)
		{
			replace_string(&(commandInfo->argv[i]),
					strdupl(findChar(node->str, '=') + 1));
			continue;
		}
		replace_string(&commandInfo->argv[i], strdupl(""));
	}
	return (0);
}

/**
 * replace_string - This replaces the string
 * @old: The address of old string used in the program
 * @new: The new string used
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

