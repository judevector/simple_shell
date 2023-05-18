#include "shell.h"

/**
 * isCmd - This determines if a file is an executable command or not
 * @commandInfo: the info struct used in the command
 * @path: The path to the file
 *
 * Return: 1 if true, 0 if otherwise
 */
int isCmd(info_t *commandInfo, char *path)
{
    struct stat st;

    (void)commandInfo;
    if (!path || stat(path, &st))
        return (0);

    if (st.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}

/**
 * dupCharList - duplicates characters in the list
 * @pathText: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dupCharList(char *pathText, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (pathText[i] != ':')
            buf[k++] = pathText[i];
    buf[k] = 0;
    return (buf);
}

/**
 * searchPath - finds this cmd in the PATH string
 * @commandInfo: the info struct
 * @pathText: the PATH string in the program
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *searchPath(info_t *commandInfo, char *pathText, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathText)
        return (NULL);
    if ((str_length(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (isCmd(commandInfo, cmd))
            return (cmd);
    }
    while (1)
    {
        if (!pathText[i] || pathText[i] == ':')
        {
            path = dupCharList(pathText, curr_pos, i);
            if (!*path)
                str_concat(path, cmd);
            else
            {
                str_concat(path, "/");
                str_concat(path, cmd);
            }
            if (isCmd(commandInfo, path))
                return (path);
            if (!pathText[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return (NULL);
}

