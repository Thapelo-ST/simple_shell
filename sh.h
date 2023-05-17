#ifndef SH_H
#define SH_H
/* needed addtitional headers for shell to run */
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
#include <ctype.h>
/* used to control needed marco variables in the shell */
#define BSZ 1024
#define EBSZ 1024
#define CBF -1
#define NORM 0
#define OR 1
#define AND 2
#define CHAIN 3
#define HFS ".shell_fh"
#define HMAX 4096
extern char **environ;

/* sigly linked list for nodes */
/**
 * list - ...
 * @num: ...
 * @str: ...
 * @next: ...
 */
typedef struct list
{
        int num;
        char *str;
        struct list *next;
} list;
/* singly liknked list for all the variables needed by shell */
/**
 * st_job - ...
 * @jobs: ...
 *
 */
typedef struct st_job
{
        char *arg;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        list *env;
        list *history;
        list *alias;
        char **environ;
        int env_changed;
        int status;
        char **cmd_buf;
        int cmd_buf_type;
        int readfd;
        int histcount;
} jobs;

/* this is the buffer the shell will start with and this is linked to the
 * st_job struture
 */
#define SHELL								\
	{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0}
/* for builtins that are like cd, clear,help etc */
/**
 *builtin - ...
 *@type: ...
 *@func: ...
 */
typedef struct builtins
{
        char *blt_type;
        int (*func)(jobs *);
} _table;
/* shell functions*/
/*********************************************************/
/* file 1 */
int _history(jobs *);
int _exits(jobs *);
int change_dir(jobs *);
int _help1(jobs *);
/*********************************************************/
/* file 2 */
int _putchar(char);
list *adne(list **, const char *, int);
char *_strchr(char *, char);
int _strcmp(char *, char *);
void _puts(char *);
/*********************************************************/
/* file 3 */
int unset_a(jobs *job, char *s);
int set_a(jobs *job, char *s);
int _alias(jobs *);
int print_a(list *n);
/*********************************************************/
/* file 4 */
int adile(jobs *);
int own_unsetenv(jobs *);
int own_setenv(jobs *);
char *_fetch(jobs *, const char *);
int _enviroment(jobs *);
/*********************************************************/
/* file 5 */
int _strlen(char *);
char *_strcat(char *, char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
/*********************************************************/
/* file 6 */
int _decimal(int, int);
int print_filedir(char count, int dir);
int show_filedir(char *c, int d);
int env_putchar(char);
void env_put(char *a);
/*********************************************************/
/* file 7 */
void perr(jobs *, char *);
int atoi_error(char *);
char *changeInt(long int, int, int);
void no_hashtags(char *);
/*********************************************************/
/* file 8 */
ssize_t buff_var(jobs *job, char **buf, size_t *len);
ssize_t own_getline(jobs *);
int get_line(jobs *, char **, size_t *);
void keyb_exit(int);
void start_job(jobs *, char **);
/*********************************************************/
/* file 9 */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void clean1(jobs *);
void clean2(jobs *, int);
/*********************************************************/
/* file 10 */
void _chain(jobs *, char *, size_t *, size_t, size_t);
int ovwr_alias(jobs *);
int _change(char **, char *);
int ovwr_var(jobs *);
int c_chain(jobs *, char *, size_t *);
/*********************************************************/
/* file 11 */
int hist_list(jobs *job, char *buf, int linecount);
char *fetch_fh(jobs *job);
int show_hist(jobs *job);
int record(jobs *job);
int c_hist(jobs *job);
/*********************************************************/
/* file 12 */
list *node_incr(list **, const char *, int);
int dnai(list **, unsigned int);
void clear_list(list **);
size_t print_s(const list *);
/*********************************************************/
/* file 13 */
int clean_buffer(void **);
int check_cmd(jobs *, char *);
char *_repeat(char *, int, int);
char *path_serch(jobs *, char *, char *);
/*********************************************************/
/* file 14 */
list *nbw(list *, char *, char);
ssize_t gni(list *, list *);
size_t p_list(const list *);
size_t _list(const list *);
char **list_str(list *);
/*********************************************************/
/* file 15 */
int mobility(jobs *);
int _isalpha(int);
int _atoi(char *);
char **split_string(char *,char);
char **str_tok(char *, char *);
/*********************************************************/
/* file 16 */
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);
char *_memset(char *, char, unsigned int);
int hsh(jobs *, char **);
int get_blt(jobs *);
/*********************************************************/
/* file 17 */
void get_command(jobs *);
void _fork(jobs *);
int _setenv(jobs *, char *, char *);
int _unsetenv(jobs *, char *);
char **env_fetch(jobs *);
/*********************************************************/
/* file 18 */
char *_bw(const char *, const char *);
ssize_t scan_buffer(jobs *job, char *buf, size_t *i);
int check_del(char, char *);
/*********************************************************/
#endif
