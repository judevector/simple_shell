#include "shell.h"

/**
 * shellExit - this shuts down the shell in the program
 * @commandInfo: the command info with possible arguments to keep the 
 prototype of the program function running.
 * Return: After leaving with the specified exit status 
 If info.argv[0]!= "exit", then the value is 0.
 */
int shellExit(info_t *commandInfo)
{
    int check;

if (commandInfo->argv[1])
    {
        check = safeStringToInt(commandInfo->argv[1]);
		if (check == -1)
			{
            	commandInfo->status = 2;
            	print_error(commandInfo, "Illegal number: ");
            	errorPrintString(commandInfo->argv[1]);
            	printErrorChar('\n');
            	return (1);
        	}
        	commandInfo->err_num = safeStringToInt(commandInfo->argv[1]);
        	return (-2);
    }
    commandInfo->err_num = -1;
    return (-2);
}

/**
 * changeDirectory - Changes the process's current directory
 * @commandInfo: the command info with possible arguments to keep the
 prototype of the program function running
 * Return: 0 is always.
 */
int changeDirectory(info_t *commandInfo)
{
    char *s, *dir, buffer[1024];
    int chdir_rekt;

    s = getcwd(buffer, 1024);
    if (!s)
        printString("TODO: >>getcwd failure emsg here<<\n");
    if (!commandInfo->argv[1])
    {
        dir = fetchEnv(commandInfo, "HOME=");
        if (!dir)
            	chdir_rekt = /* TODO: what should this be? */
                chdir((dir = fetchEnv(commandInfo, "PWD=")) ? dir : "/");
        else
            chdir_rekt = chdir(dir);
    }
    else if (compareStrings(commandInfo->argv[1], "-") == 0)
    {
        if (!fetchEnv(commandInfo, "OLDPWD="))
        	{
            	printString(s);
            	writeChar('\n');
            	return (1);
        	}
        printString(fetchEnv(commandInfo, "OLDPWD=")), writeChar('\n');
        chdir_rekt = /* TODO: what should this be? */
            chdir((dir = fetchEnv(commandInfo, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_rekt = chdir(commandInfo->argv[1]);
    if (chdir_rekt == -1)
    {
        print_error(commandInfo, "can't cd to ");
        errorPrintString(commandInfo->argv[1]), printErrorChar('\n');
    }
    else
    {
        setEnv(commandInfo, "OLDPWD", fetchEnv(commandInfo, "PWD="));
        setEnv(commandInfo, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * showHelp - Displays the help information for the command.
 * @commandInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int showHelp(info_t *commandInfo)
{
    char **arg_array;

    arg_array = commandInfo->argv;
    printString("help call works. Function not yet implemented \n");
    if (0)
        printString(*arg_array);
    return (0);
}

