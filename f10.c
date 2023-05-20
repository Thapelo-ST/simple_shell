#include "sh.h"

/**
 *  _chain- ...
 * @jobs:...
 * @job:..
 */

void _chain(jobs *job, char *buf, size_t *p, size_t i, size_t len)
{
        size_t j = *p;

        if (job->cmd_buf_type == AND)
        {
                if (job->status)
                {
                        buf[i] = 0;
                        j = len;
                }
        }
        if (job->cmd_buf_type == OR)
        {
                if (!job->status)
                {
                        buf[i] = 0;
                        j = len;
                }
        }

        *p = j;
}
/**
 * ovwr_alias -...
 * @jobs:...
 * @job:..
 * Return:...
 */

int ovwr_alias(jobs *job)
{
        int i;
        list *node;
        char *p;

        for (i = 0; i < 10; i++)
        {
                node = nbw(job->alias, job->argv[0], '=');
                if (!node)
                        return (0);
                free(job->argv[0]);
                p = _strchr(node->str, '=');
                if (!p)
                        return (0);
                p = _strdup(p + 1);
                if (!p)
                        return (0);
                job->argv[0] = p;
        }
        return (1);
}


int _change(char **old, char *new)
{
        free(*old);
        *old = new;
        return (1);
}

/**
 * ovwr_var-...
 * @jobs:...
 * @job:..
 * Return:...
 */

int ovwr_var(jobs *job)
{
        int i = 0;
        list *node;

        for (i = 0; job->argv[i]; i++)
        {
                if (job->argv[i][0] != '$' || !job->argv[i][1])
                        continue;

                if (!_strcmp(job->argv[i], "$?"))
                {
                        _change(&(job->argv[i]),
                                _strdup(changeInt(job->status, 10, 0)));
                        continue;
                }
                if (!_strcmp(job->argv[i], "$$"))
                {
                        _change(&(job->argv[i]),
                                _strdup(changeInt(getpid(), 10, 0)));
                        continue;
                }
                node = nbw(job->env, &job->argv[i][1], '=');
                if (node)
                {
                        _change(&(job->argv[i]),
                                _strdup(_strchr(node->str, '=') + 1));
                        continue;
                }
                _change(&job->argv[i], _strdup(""));

        }
        return (0);
}

/**
 * c_chain -...
 * @jobs:...
 * @job:..
 * Return:...
 */

int c_chain(jobs *job, char *buf, size_t *p)
{
        size_t j = *p;

        if (buf[j] == '|' && buf[j + 1] == '|')
        {
                buf[j] = 0;
                j++;
                job->cmd_buf_type = OR;
        }
        else if (buf[j] == '&' && buf[j + 1] == '&')
        {
                buf[j] = 0;
                j++;
                job->cmd_buf_type = AND;
        }
        else if (buf[j] == ';') /* found end of this command */
        {
                buf[j] = 0; /* replace semicolon with null */
                job->cmd_buf_type = CHAIN;
        }
        else
                return (0);
        *p = j;
        return (1);
}
