#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convertNum() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_n;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount: if on count this line of input
 * @fileName: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @envMutated: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @history_count: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount;
	char *fileName;
	list_n *env;
	list_n *history;
	list_n *alias;
	char **environ;
	int envMutated;
	int status;

	char **cmd_buf;   /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int history_count;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* toem_shloop.c */
int hsh(info_t *, char **);
int detect_builtin(info_t *);
void detect_cmd(info_t *);
void spawn_cmd(info_t *);

/* toem_parser.c */
int isCmd(info_t *, char *);
char *dupCharList(char *, int, int);
char *searchPath(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void errorPrintString(char *);
int printErrorChar(char);
int fdPrint(char c, int fd);
int fdPuts(char *str, int fd);

/* toem_string.c */
int str_length(char *);
int compareStrings(char *, char *);
char *starts_with(const char *, const char *);
char *str_concat(char *, char *);

/* toem_string1.c */
char *str_copy(char *, char *);
char *strdupl(const char *);
void printString(char *);
int writeChar(char);

/* toem_exits.c */
char *strnCopy(char *, char *, int);
char *strnConcat(char *, char *, int);
char *findChar(char *, char);

/* toem_tokenizer.c */
char **word_split(char *, char *);
char **extract_words(char *, char);

/* toem-reallocate.c */
char *resetMatrix(char *, char, unsigned int);
void dispose(char **);
void *reallocate(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bufferFree(void **);

/* toem_str2int.c */
int isInteractive(info_t *);
int isDelimiter(char, char *);
int isAlphabetic(int);
int convertToInt(char *);

/* toem_errors1.c */
int safeStringToInt(char *);
void printErr(info_t *, char *);
int display_d(int, int);
char *convertNum(long int, int, int);
void strip_comments(char *);

/* toem_builtin.c */
int shellExit(info_t *);
int changeDirectory(info_t *);
int showHelp(info_t *);

/* toem_builtin1.c */
int showHistory(info_t *);
int manageAlias(info_t *);

/*toem_getline.c */
ssize_t read_input(info_t *);
int get_line(info_t *, char **, size_t *);
void sigintAction(int);

/* toem_getinfo.c */
void clear_data(info_t *);
void set_data(info_t *, char **);
void clear_info(info_t *, int);

/* toem_environ.c */
char *fetchEnv(info_t *, const char *);
int showEnv(info_t *);
int updateEnv(info_t *);
int unsetEnv(info_t *);
int fillEnv(info_t *);

/* toem_getenv.c */
char **access_env(info_t *);
int discardEnv(info_t *, char *);
int setEnv(info_t *, char *, char *);

/* toem_history.c */
char *retrieve_file(info_t *info);
int record_history(info_t *info);
int get_hist(info_t *info);
int form_history(info_t *info, char *buf, int linecount);
int reorder_hist(info_t *info);

/* toem_lists.c */
list_n *push_node(list_n **, const char *, int);
list_n *appendNode(list_n **, const char *, int);
size_t printStrList(const list_n *);
int eraseNodeAtIndex(list_n **, unsigned int);
void clear_list(list_n **);

/* toem_lists1.c */
size_t get_length(const list_n *);
char **list2str(list_n *);
size_t listPrint(const list_n *);
list_n *startsWith(list_n *, char *, char);
ssize_t findNodeIndex(list_n *, list_n *);

/* toem_vars.c */
int verify_chain(info_t *, char *, size_t *);
void test_chain(info_t *, char *, size_t *, size_t, size_t);
int resolve_alias(info_t *);
int apply_vars(info_t *);
int replace_string(char **, char *);

#endif

