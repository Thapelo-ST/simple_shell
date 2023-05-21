#include "sh.h"

/**
 * _putchar -...
 * @jobs:...
 * @job:..
 * Return:...
 */

int _putchar(char c)
{
        static int i;
        static char buf[EBSZ];

        if (c == CBF || i >= EBSZ)
        {
                write(1, buf, i);
                i = 0;
        }
        if (c != CBF)
                buf[i++] = c;
        return (1);
}

/**
 * adne -...
 * @jobs:...
 * @job:..
 * Return:...
 */

list *adne(list **head, const char *str, int num)
{
        list *new_node, *node;

        if (!head)
                return (NULL);

        node = *head;
        new_node = malloc(sizeof(list));
        if (!new_node)
                return (NULL);
        _memset((void *)new_node, 0, sizeof(list));
        new_node->num = num;
        if (str)
        {
                new_node->str = _strdup(str);
                if (!new_node->str)
                {
                        free(new_node);
                        return (NULL);
                }
        }
        if (node)
        {
                while (node->next)
                        node = node->next;
                node->next = new_node;
        }
        else
                *head = new_node;
        return (new_node);
}

char *_strchr(char *s, char c)
{
        for( ; *s != '\0'; s++ )
        {
                if (*s == c)
                        return(s);
        }
        return (NULL);
}

/**
 * _strchr -...
 * @jobs:...
 * @job:..
 * Return:...
 */

int _strcmp(char *s1, char *s2)
{
        if (*s1 && *s2)
        {
                if (*s1 != *s2)
                        return (*s1 - *s2);
                return (_strcmp(s1 + 1, s2 + 1));
        }

        if (*s1 == *s2)
                return (0);
        else
                return ((*s1 < *s2) ? -1 : 1);
}

/**
 * _puts -...
 * @jobs:...
 * @job:..
 */
void _puts(char *str)
{
        int i = 0;

        if (!str)
                return;
        while (str[i] != '\0')
        {
                _putchar(str[i]);
                i++;
        }
}
