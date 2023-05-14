#include "shell.h"

/**
 * exitCommandInfo - This exits the shell
 * @commandInfo: A hypothetical argument structure is contained in the function
 * which is used to keep the constant function prototype up to date.
 * Return: Return leaves the shell with the specified exit status.
 *          If commandInfo.argv[0] does not contain the word "exit," it returns 0.
 */

int exitCommandInfo(info_t *commandInfo)
{
	int exitStatus;

	if (commandInfo->argv[1]) /* If there is an exit arguement */
	{
		exitStatus = safeAtoi(commandInfo->argv[1]);
		if (exitStatus == -1)
		{
			commandInfo->status = 2;
			showError(commandInfo, "Illegal number: ");
			errorPuts(commandInfo->argv[1]);
			errorPutchar('\n');
			return (1);
		}
		commandInfo->err_num = safeAtoi(commandInfo->argv[1]);
		return (-2);
	}
	commandInfo->err_num = -1;
	return (-2);
}

/**
 * cdInfo - changes the current directory of the process
 * @commandInfo: Structure containing potential arguments. That can be used to maintain
 * constant function prototype in the program.
 * Return: Always 0
 */
int cdInfo(info_t *commandInfo)
{
	char *currentDirectory, *dir, buffer[1024];
	int chdirResult;

	currentDirectory = getcwd(buffer, 1024);
	if (!currentDirectory)
		printString("TODO: >>getcwd failure emsg here<<\n");
	if (!commandInfo->argv[1])
	{
		dir = fetchEnvVar(commandInfo, "HOME=");
		if (!dir)
			chdirResult = /* TODO: what should this be? */
				chdir((dir = fetchEnvVar(commandInfo, "PWD=")) ? dir : "/");
		else
			chdirResult = chdir(dir);
	}
	else if (stringCompare(commandInfo->argv[1], "-") == 0)
	{
		if (!fetchEnvVar(commandInfo, "OLDPWD="))
		{
			printString(currentDirectory);
			printChar('\n');
			return (1);
		}
		printString(fetchEnvVar(commandInfo, "OLDPWD=")), printChar('\n');
		chdirResult = /* TODO: the result from changing directory */
			chdir((dir = fetchEnvVar(commandInfo, "OLDPWD=")) ? dir : "/");
	}
	else
		chdirResult = chdir(commandInfo->argv[1]);
	if (chdirResult == -1)
	{
		showError(commandInfo, "can't cd to ");
		errorPuts(commandInfo->argv[1]), errorPutchar('\n');
	}
	else
	{
		updateEnvVar(commandInfo, "OLDPWD", fetchEnvVar(commandInfo, "PWD="));
		updateEnvVar(commandInfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * helpCommandInfo - Modifies the process's current directory
 * @commandInfo: Structure holding potential parameters. used to
 * keep up a prototype constant function. Always return 0
 * Return: Always 0 if successful
 */
int helpCommandInfo(info_t *commandInfo)
{
	char **arguments;

	arguments = commandInfo->argv;
	printString("The helpline is operational. The function is not yet operational. \n");
	if (0)
		printString(*arguments);
	return (0);
}

