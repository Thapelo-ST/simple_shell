#include "sh.h"

/**
 * main - Entry point of the program
 *
 * This function demonstrates the usage of various functions from the "sh.h" library.
 * It showcases the functionality of adding nodes to a linked list, traversing the list,
 * comparing strings, and searching for characters in a string. Additionally, it utilizes
 * the `_putchar` function to write characters, and the `_puts` function to write strings.
 *
 * Return: Always 0
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
