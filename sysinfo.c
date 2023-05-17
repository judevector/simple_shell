#include "shell.h"

/**
 * clear_data - initializes info_t struct
 * @commandInfo: struct address
 */
void clear_data(info_t *commandInfo)
{
    commandInfo->arg = NULL;
    commandInfo->argv = NULL;
    commandInfo->path = NULL;
    commandInfo->argc = 0;
}

/**
 * set_data - This initializes or set info_t struct
 * @commandInfo: struct address or information in the command
 * @av: argument vector used in the command
 */
void set_data(info_t *commandInfo, char **av)
{
    int i = 0;

    commandInfo->fileName = av[0];
    if (commandInfo->arg)
    {
        commandInfo->argv = word_split(commandInfo->arg, " \t");
        	if (!commandInfo->argv)
        	{
            	commandInfo->argv = malloc(sizeof(char *) * 2);
            	if (commandInfo->argv)
            	{
                	commandInfo->argv[0] = strdupl(commandInfo->arg);
                	commandInfo->argv[1] = NULL;
            	}
        }
        	for (i = 0; commandInfo->argv && commandInfo->argv[i]; i++)
            	;
        	commandInfo->argc = i;

        	resolve_alias(commandInfo);
        	apply_vars(commandInfo);
    	}
}

/**
 * clear_info - frees info_t struct fields used in the command
 * @commandInfo: struct address or information
 * @all: true if freeing all fields
 */
void clear_info(info_t *commandInfo, int all)
{
    ffree(commandInfo->argv);
    commandInfo->argv = NULL;
    commandInfo->path = NULL;
    	if (all)
    	{
        	if (!commandInfo->cmd_buf)
            	free(commandInfo->arg);
        	if (commandInfo->env)
            	free_list(&(commandInfo->env));
        	if (commandInfo->history)
            	free_list(&(commandInfo->history));
        	if (commandInfo->alias)
            	free_list(&(commandInfo->alias));
        ffree(commandInfo->environ);
        commandInfo->environ = NULL;
        bfree((void **)commandInfo->cmd_buf);
        	if (commandInfo->readfd > 2)
            	close(commandInfo->readfd);
        	writeChar(BUF_FLUSH);
    	}
}

