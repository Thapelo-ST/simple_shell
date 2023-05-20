#include "sh.h"

/**
 * nbw - ...
 * @jobs:...
 * @job:..
 * Return:...
 */

list *nbw(list *node, char *prefix, char c)
{
        char *p = NULL;

        while (node)
        {
                p = _bw(node->str, prefix);
                if (p && ((c == -1) || (*p == c)))
                        return (node);
                node = node->next;
        }
        return (NULL);
}

/**
 * gni - ...
 * @jobs:...
 * @job:..
 * Return:...
 */

ssize_t gni(list *head, list *node)
{
        size_t i = 0;

        while (head)
        {
                if (head == node)
                        return (i);
                head = head->next;
                i++;
        }
        return (-1);
}

/**
 * p_list - ...
 * @jobs:...
 * @job:..
 * Return:...
 */

size_t p_list(const list *h)
{
        size_t i = 0;

        while (h)
        {
                _puts(changeInt(h->num, 10, 0));
                _putchar(':');
                _putchar(' ');
                _puts(h->str ? h->str : "(nil)");
                _puts("\n");
                h = h->next;
                i++;
        }
        return (i);
}

/**
 * _list - ...
 * @jobs:...
 * @job:..
 * Return:...
 */

size_t _list(const list *h)
{
        size_t i = 0;
        for ( ; h ; h=h->next)
                i++;
        return (i);
}

/**
 * list_str - ...
 * @jobs:...
 * @job:..
 * Return:...
 */

char **list_str(list *head)
{

        list *node = head;
        size_t i = _list(head), j;
        char **strs;
        char *str;

        if (!head || !i)
                return (NULL);
        strs = malloc(sizeof(char *) * (i + 1));
        if (!strs)
                return (NULL);
        for (i = 0; node; node = node->next, i++)
        {
                str = malloc(_strlen(node->str) + 1);
                if (!str)
                {
                        for (j = 0; j < i; j++)
                                free(strs[j]);
                        free(strs);
                        return (NULL);
                }

                str = _strcpy(str, node->str);
                strs[i] = str;
        }
        strs[i] = NULL;
        return (strs);
}
