#include "sh.h"

/**
 * _strlen -...
 * @s:...
 * Return:...
 */


int _strlen(char *s)
{
	if (!s || *s == '\0')
		return (0);
	return (1 + _strlen(s + 1));
}

/**
 * _strcat -...
 * @dest:...
 * @src:...
 * Return:...
 */
char *_strcat(char *dest, char *src)
{
        char *ret = dest;

        while (*dest)
                dest++;
        while (*src)
                *dest++ = *src++;
        *dest = *src;
        return (ret);
}

/**
 * _strncpy -...
 * @dest:...
 * @src:...
 * @n:...
 * Return:...
 */

char *_strncpy(char *dest, char *src, int n)
{
        int i, j;
        char *s = dest;

        for (i = 0; src[i] != '\0' && i < n - 1; i++)
                dest[i] = src[i];
        if (i < n)
        {
                for (j = i; j < n; j++)
                        dest[j] = '\0';
        }
        return (s);
}

/**
 * _strncat -...
 * @dest:...
 * @src:...
 * @n:...
 * Return:...
 */

char *_strncat(char *dest, char *src, int n)
{
        int i, j;
        char *s = dest;

        i = 0;
        j = 0;
        for (i = 0; dest[i] != '\0'; i++)
                ;
        for (j = 0; src[j] != '\0' && j < n; j++)
        {
                dest[i] = src[j];
                i++;
        }
        if (j < n)
                dest[i] = '\0';
        return (s);
}
