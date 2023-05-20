#include "sh.h"

/**
 * buff_var-...
 * @jobs:...
 * @job:..
 * Return:...
 */

ssize_t buff_var(jobs *job, char **buf, size_t *len)
{
        ssize_t r = 0;
        size_t len_p = 0;

        if (*len == 0)
        {
                free(*buf);
                *buf = NULL;
                signal(SIGINT, keyb_exit);
#if USE_GETLINE
                r = getline(buf, &len_p, stdin);
#else
                r = get_line(job, buf, &len_p);
#endif
                if (r > 0) {
                        if ((*buf)[r - 1] == '\n') {
                                (*buf)[r - 1] = '\0';
                                r--;
                        }
                        job->linecount_flag = 1;
                        no_hashtags(*buf);
                        hist_list(job, *buf, job->histcount++);
                        if (_strchr(*buf, ';')) {
                                *len = r;
                                job->cmd_buf = buf;
                        }
                }
        }
        return (r);
}

/**
 * own_getline -...
 * @jobs:...
 * @job:..
 * Return:...
 */

ssize_t own_getline(jobs *job)
{
        static char *buf;
        static size_t i, j, len;
        ssize_t r = 0;
        char **buf_p = &(job->arg), *p;

        _putchar(CBF);
        r = buff_var(job, &buf, &len);
        if (r == -1)
                return (-1);
        if (len)
        {
                j = i;
                p = buf + i;
                _chain(job, buf, &j, i, len);
                for (; j < len; j++)
                {
                        if (c_chain(job, buf, &j))
                                break;
                }
                i = j + 1;
                if (i >= len)
                {
                        i = len = 0;
                        job->cmd_buf_type = NORM;
                }
                *buf_p = p;
                return (_strlen(p));
        }
        *buf_p = buf;
        return (r);
}

/**
 * get_line -...
 * @jobs:...
 * @job:..
 * Return:...
 */

int get_line(jobs *job, char **ptr, size_t *length)
{
        /*declare variables*/
        static char buf[BSZ];
        static size_t i, len;
        size_t k;
        ssize_t r = 0, s = 0;
        char *p = NULL, *new_p = NULL, *c;

        /* assigning ptr to p and checking validity*/
        p = *ptr, length ? s = *length : 0;
        /*cheking if i = len */
        i == len ? i = len = 0 : 0;
        r = scan_buffer(job, buf, &len);
        /* if r is zero or -1 the function fails */
        if (r == -1 || (r == 0 && len == 0))
                return (-1);
        c = _strchr(buf + i, '\n');
        /*check if c is null then k will be assigned with e1 else e2*/
        k = c ? 1 + (unsigned int)(c - buf) : len;
        /*if malloc failed*/
        /* realloc with 3 args, the last arg is if s is true return s+k
         * else return k+1 */
        if (!(new_p = _realloc(p, s, s ? s + k : k + 1)))
                return (p ? free(p), -1 : -1);
        /*check if s is true then return e1 else e2*/
        s ? _strncat(new_p, buf + i, k - i) : _strncpy(new_p, buf + i, k - i + 1);
        /*reasigning variables*/
        s += k - i, i = k, p = new_p;
        /*finalizing get line*/
        length ? *length = s : 0, *ptr = p;
        return (s);
}

/**
 * keyb_exit-...
 * @jobs:...
 * @job:..
 * Return:...
 */

void keyb_exit(__attribute__((unused))int sig_num)
{
        _puts("\n");
        _puts("$ ");
        _putchar(CBF);
}

/**
 * start_job -...
 * @jobs:...
 * @job:..
 * Return:...
 */

void start_job(jobs *job, char **av)
{

        /* initializing vatiables */
        int i = 0;

        job->fname = av[0];
        /* checking if argument is not null */
        /* if not null allocate memory if null assign res from modified strtok*/
        job->argv = job->arg ? str_tok(job->arg, " \t") : malloc(sizeof(char *) * 2);
        /*if argument is still null*/
        if (job->argv)
        {
                for (i = 0 ; job->argv[i] ; i++)
                        ;
                job->argc = i;
                ovwr_alias(job);
                ovwr_var(job);
        }
}
