#include "sh.h"

/**
 * _decimal - ...
 * @jobs:...
 * @job:..
 * Return:...
 */

int _decimal(int input, int fd)
{
        int (*m_putchar)(char) = _putchar;
        int i, count = 0;
        unsigned int absolute, current;

        if (fd == STDERR_FILENO)
                m_putchar = env_putchar;
        if (input < 0)
        {
                absolute = -input;
                m_putchar('-');
                count++;
        }
        else
                absolute = input;
        current = absolute;
        for (i = 1000000000; i > 1; i /= 10)
        {
                if (absolute / i)
                {
                        m_putchar('0' + current / i);
                        count++;
                }
                current %= i;
        }
        m_putchar('0' + current);
        count++;

        return (count);
}


int print_filedir(char c, int fd)
{
        static int i;
        static char buffer[EBSZ];

        if (c == CBF || i >= EBSZ)
        {
                write(fd, buffer, i);
                i = 0;
        }
        if (c != CBF)
                buffer[i++] = c;
        return (1);
}

int show_filedir(char *c, int d)
{
        int i = 0;

        if (!c)
                return (0);
        while (*c)
        {
                i += print_filedir(*c++, d);
        }
        return (i);
}


int env_putchar(char c)
{
        static int i;
        static char buffer[EBSZ];

        if (c == CBF || i >= EBSZ)
        {
                write(2, buffer, i);
                i = 0;
        }
        if (c != CBF)
                buffer[i++] = c;
        return (1);
}


void env_put(char *str)
{
        int i = 0;

        if (str == 0)
                return;
        while (str[i] != '\0')
        {
                env_putchar(str[i]);
                i++;
        }
}
