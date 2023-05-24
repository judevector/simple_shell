#include "shell.h"

/**
 * inputBuf - this buffers the  chained commands
 * @commandInfo: parameter or struct info used in shell
 * @buf: address of buffer to receive
 * @length: address of len variable used in shell
 *
 * Return: bytes read if successful otherwise NULL
 */
ssize_t inputBuf(info_t *commandInfo, char **buf, size_t *length)
{
ssize_t r = 0;
size_t len_p = 0;

if (!*length)
{
free(*buf);
*buf = NULL;
signal(SIGINT, sigintAction);
#if USE_GETLINE
r = getline(buf, &len_p, stdin);
#else
r = get_line(commandInfo, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /* remove trailing newline */
r--;
}
commandInfo->linecount = 1;
strip_comments(*buf);
form_history(commandInfo, *buf, commandInfo->history_count++);
{
*length = r;
commandInfo->cmd_buf = buf;
}
}
}
return (r);
}

/**
 * read_input - This reads the input line minus the newline used
 * @commandInfo: The parameter or struct info used in the output file
 *
 * Return: bytes read after the input line otherwise return nothing
 */
ssize_t read_input(info_t *commandInfo)
{
static char *buf; /* the ';' command chain buffer */
static size_t i, j, length;
ssize_t r = 0;
char **buf_p = &(commandInfo->arg), *p;

writeChar(BUF_FLUSH);
r = inputBuf(commandInfo, &buf, &length);
if (r == -1) /* EOF */
return (-1);
if (length)
{
j = i;
p = buf + i;

test_chain(commandInfo, buf, &j, i, length);
while (j < length)
{
if (verify_chain(commandInfo, buf, &j))
break;
j++;
}

i = j + 1;
if (i >= length)
{
i = length = 0;
commandInfo->cmd_buf_type = CMD_NORM;
}

*buf_p = p;
return (str_length(p));
}

*buf_p = buf;
return (r);
}

/**
 * get_buf - This reads a buffer in the program
 * @commandInfo: The parameter struct or info used
 * @buf: the buffer used in the program
 * @i: size
 *
 * Return: this returns r nothing else
 */
ssize_t get_buf(info_t *commandInfo, char *buf, size_t *i)
{
ssize_t r = 0;

if (*i)
return (0);
r = read(commandInfo->readfd, buf, READ_BUF_SIZE);
if (r >= 0)
*i = r;
return (r);
}

/**
 * get_line - gets the next line of input from STDIN in the program
 * @commandInfo: parameter struct or information structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s if successful else returns NULL
 */
int get_line(info_t *commandInfo, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;

p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;

r = get_buf(commandInfo, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);

c = findChar(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = reallocate(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);

if (s)
strnConcat(new_p, buf + i, k - i);
else
strnCopy(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_p;

if (length)
*length = s;
*ptr = p;
return (s);
}

/**
 * sigintAction - blocks ctrl-C
 * @sig_num: the signal number is used in the program
 * u
 * Return: void or NULL
 */
void sigintAction(__attribute__((unused)) int sig_num)
{
printString("\n");
printString("$ ");
writeChar(BUF_FLUSH);
}

