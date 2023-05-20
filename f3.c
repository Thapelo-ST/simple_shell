#include "sh.h"

/**
 * alias -
 * @jobs:...
 * @job:.. 
 * Return:..
 */

int unset_a(jobs *job, char *str)
{
        char *p = _strchr(str, '=');
        int feed = 0;

        if (!p)
                return (1);

        *p = '\0';
        feed = dnai(&(job->alias),
                    gni(job->alias, nbw
                        (job->alias, str, -1)));
        *p = '=';
        return (feed);
}

int set_a(jobs *job, char *str)
{
        char *value = _strchr(str, '=') + 1;

        if (*value == '\0')
                return (unset_a(job, str));
        unset_a(job, str);
        return (adne(&(job->alias), str, 0) == NULL);
}

int _alias(jobs *job)
{
        int i;
        char *p;

        if (job->argc == 1)
        {
                list *node = job->alias;
                while (node)
                {
                        print_a(node);
                        node = node->next;
                }
                return (0);
        }

        for (i = 1; job->argv[i]; i++)
        {
                p = _strchr(job->argv[i], '=');
                if (p)
                        set_a(job, job->argv[i]);
                else
                        print_a(nbw(job->alias, job->argv[i], '='));
        }

        return (0);
}

int print_a(list *node)
{
        char *p = NULL, *a = NULL;

        if (node)
        {
                p = _strchr(node->str, '=');
                for (a = node->str; a <= p; a++)
                        _putchar(*a);
                _putchar('\'');
                _puts(p + 1);
                _puts("'\n");
                return (0);
        }
        return (1);
}
