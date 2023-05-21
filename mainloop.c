#include "shell.h"

/**
 * hsh - main shell loop
 * @commandInfo: the parameter & return info struct used in the shell
 * @av: the argument vector from main() used in the shell
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *commandInfo, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_data(commandInfo);
		if (isInteractive(commandInfo))
			printString("$ ");
		printErrorChar(BUF_FLUSH);
		r = read_input(commandInfo);
		if (r != -1)
		{
			set_data(commandInfo, av);
			builtin_ret = detect_builtin(commandInfo);
			if (builtin_ret == -1)
				detect_cmd(commandInfo);
		}
		else if (isInteractive(commandInfo))
			writeChar('\n');
		clear_info(commandInfo, 0);
	}
	record_history(commandInfo);
	clear_info(commandInfo, 1);
	if (!isInteractive(commandInfo) && commandInfo->status)
		exit(commandInfo->status);
	if (builtin_ret == -2)
	{
		if (commandInfo->err_num == -1)
			exit(commandInfo->status);
		exit(commandInfo->err_num);
	}
	return (builtin_ret);
}

/**
 * detect_builtin - This detects a builtin command
 * @commandInfo: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin was executed successfully,
 * 1 if builtin was found but not successful,
 * 2 if builtin has signals exit()
 */
int detect_builtin(info_t *commandInfo)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", shellExit},
		{"env", showEnv},
		{"help", showHelp},
		{"history", showHistory},
		{"setenv", updateEnv},
		{"unsetenv", unsetEnv},
		{"cd", changeDirectory},
		{"alias", manageAlias},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
		if (compareStrings(commandInfo->argv[0], builtintbl[i].type) == 0)
		{
			commandInfo->line_count++;
			built_in_ret = builtintbl[i].func(commandInfo);
			break;
		}
	return (built_in_ret);
}

/**
 * detect_cmd - This detects a command in PATH
 * @commandInfo: the parameter & return info struct
 * Return: void or null
 */
void detect_cmd(info_t *commandInfo)
{
	char *path = NULL;
	int i, k;

	commandInfo->path = commandInfo->argv[0];
	if (commandInfo->linecount == 1)
	{
		commandInfo->line_count++;
		commandInfo->linecount = 0;
	}
	for (i = 0, k = 0; commandInfo->arg[i]; i++)
		if (!isDelimiter(commandInfo->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = searchPath(commandInfo, fetchEnv(commandInfo, "PATH="),
	commandInfo->argv[0]);
	if (path)
	{
		commandInfo->path = path;
		spawn_cmd(commandInfo);
	}
	else
	{
		if ((isInteractive(commandInfo) || fetchEnv(commandInfo, "PATH=") ||
		commandInfo->argv[0][0] == '/') && isCmd(commandInfo, commandInfo->argv[0]))
			spawn_cmd(commandInfo);
		else if (*(commandInfo->arg) != '\n')
		{
			commandInfo->status = 127;
			printErr(commandInfo, "not found\n");
		}
	}
}

/**
 * spawn_cmd - This forks a an exec thread to run command
 * @commandInfo: the parameter & return commandInfo struct used in the program
 *
 * Return: void or null
 */
void spawn_cmd(info_t *commandInfo)
{
i	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(commandInfo->path, commandInfo->argv,
		access_env(commandInfo)) == -1)
		{
			clear_info(commandInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(commandInfo->status));
		if (WIFEXITED(commandInfo->status))
		{
			commandInfo->status = WEXITSTATUS(commandInfo->status);
			if (commandInfo->status == 126)
				printErr(commandInfo, "Permission denied\n");
		}
	}
}
