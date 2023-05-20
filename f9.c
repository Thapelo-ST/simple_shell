#include "sh.h"

/**
 * _strcpy -...
 * @jobs:...
 * @job:..
 * Return:...
 */

char *_strcpy(char *dest, char *src)
{
        int i = 0;

        if (dest == src || src == 0)
                return (dest);
        while (src[i])
        {
                dest[i] = src[i];
                i++;
        }
        dest[i] = 0;
        return (dest);
}
/**
 * _strdup -...
 * @jobs:...
 * @job:..
 * Return:...
 */

char *_strdup(const char *str)
{
        int length = 0;
        char *ret;

        if (str == NULL)
                return (NULL);
        while (*str++)
                length++;
        ret = malloc(sizeof(char) * (length + 1));
        if (!ret)
                return (NULL);
        for (length++; length--;)
                ret[length] = *--str;
        return (ret);
}

/**
 * clean1 -...
 * @jobs:...
 * @job:..
 * Return:...
 */

void clean1(jobs *job)
{
        /*reset everything to null*/
        job->arg = NULL;
        job->argv = NULL;
        job->path = NULL;
        job->argc = 0;
}

/**
 * clean2 -...
 * @jobs:...
 * @job:..
 * Return:...
 */

void clean2(jobs *job, int all)
{
        ffree(job->argv);
        job->argv = NULL;
        job->path = NULL;
        if (all)
        {
                if (!job->cmd_buf)
                        free(job->arg);
                if (job->env)
                        clear_list(&(job->env));
                if (job->history)
                        clear_list(&(job->history));
                if (job->alias)
                        clear_list(&(job->alias));
                ffree(job->environ);
		job->environ = NULL;
                clean_buffer((void **)job->cmd_buf);
                if (job->readfd > 2)
                        close(job->readfd);
                _putchar(CBF);
        }
}
