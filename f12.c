#include "sh.h"
/**
 * node_incr- ...
 * @jobs:...
 * @job:..
 * Return:...
 */

list *node_incr(list **head, const char *str, int num)
{
        list *new_head;

        if (!head)
                return (NULL);
        new_head = malloc(sizeof(list));
        if (!new_head)
                return (NULL);
        _memset((void *)new_head, 0, sizeof(list));
        new_head->num = num;
        if (str)
        {
                new_head->str = _strdup(str);
                if (!new_head->str)
                {
                        free(new_head);
                        return (NULL);
                }
        }
        new_head->next = *head;
        *head = new_head;
        return (new_head);
}

/**
 * dnai -...
 * @jobs:...
 * @job:..
 * Return:...
 */

int dnai(list **head, unsigned int index)
{
        list *node, *prev_node;
        unsigned int i = 0;

        if (!head || !*head)
                return (0);

        if (index == 0)
        {
                node = *head;
                *head = (*head)->next;
                free(node->str);
                free(node);
                return (1);
        }
        prev_node = NULL;
        node = *head;
        while (node && i < index)
        {
                prev_node = node;
                node = node->next;
                i++;
        }

        if (node)
        {
                prev_node->next = node->next;
                free(node->next);
                free(node);
                return(1);
        }
        return (0);
}

/**
 * clear_list -...
 * @jobs:...
 * @job:..
 * Return:...
 */

void clear_list(list **head_ptr)
{
        list *node, *next_node, *head;

        if (!head_ptr || !*head_ptr)
                return;
        head = *head_ptr;
        node = head;
        while (node)
        {
                next_node = node->next;
                free(node->str);
                free(node);
                node = next_node;
        }
        *head_ptr = NULL;
}

/**
 * print_s -...
 * @jobs:...
 * @job:..
 * Return:...
 */

size_t print_s(const list *h)
{
        size_t i = 0;

        while (h)
        {
                _puts(h->str ? h->str : "(nill)");
                _puts("\n");
                h = h->next;
                i++;
        }
        return (i);
}
