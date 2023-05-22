#include "shell.h"

/**
 * retrieve_file - gets the history file
 * @commandInfo: parameter used in the command
 *
 * Return: allocated string containing the history file
 */

char *retrieve_file(info_t *commandInfo)
{
char *buf, *dir;

dir = fetchEnv(commandInfo, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (str_length(dir) + str_length(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
str_copy(buf, dir);
str_concat(buf, "/");
str_concat(buf, HIST_FILE);
return (buf);
}

/**
 * record_history - creates a file, or appends to an existing file
 * @commandInfo: the parameter struct or information struct
 * Return: 1 on success, else otherwise -1
 */
int record_history(info_t *commandInfo)
{
ssize_t fd;
char *filename = retrieve_file(commandInfo);
list_n *node = NULL;

if (!filename)
return (-1);

fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = commandInfo->history; node; node = node->next)
{
fdPuts(node->str, fd);
fdPrint('\n', fd);
}
fdPrint(BUF_FLUSH, fd);
close(fd);
return (1);
}

/**
 * get_hist - reads history from file
 * @commandInfo: the parameter struct
 *
 * Return: history_count on success, 0 otherwise
 */
int get_hist(info_t *commandInfo)
{
int i, last = 0, linecount = 0;
ssize_t fd, rlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = retrieve_file(commandInfo);

if (!filename)
return (0);

fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
form_history(commandInfo, buf + last, linecount++);
last = i + 1;
}
if (last != i)
form_history(commandInfo, buf + last, linecount++);
free(buf);
commandInfo->history_count = linecount;
while (commandInfo->history_count-- >= HIST_MAX)
eraseNodeAtIndex(&(commandInfo->history), 0);
reorder_hist(commandInfo);
return (commandInfo->history_count);
}

/**
 * form_history - adds entry to a history linked list
 * @commandInfo: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, history_count
 *
 * Return: Always 0
 */
int form_history(info_t *commandInfo, char *buf, int linecount)
{
list_n *node = NULL;

if (commandInfo->history)
node = commandInfo->history;
appendNode(&node, buf, linecount);

if (!commandInfo->history)
commandInfo->history = node;
return (0);
}

/**
 * reorder_hist - renumbers the history linked list after changes
 * @commandInfo: Structure containing potential arguments. Used in the code
 *
 * Return: the new history_count
 */
int reorder_hist(info_t *commandInfo)
{
list_n *node = commandInfo->history;
int i = 0;

while (node)
{
node->num = i++;
node = node->next;
}
return (commandInfo->history_count = i);
}

