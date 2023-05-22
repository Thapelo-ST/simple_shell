#include "sh.h"
#define BLT_CLC 1
#define BLT_UNSC 2

/**
 * perr -...
 * @job:...
 * @estr:...
 */

void perr(jobs *job, char *estr)
{
	env_put(job->fname);
	env_put(": ");
	_decimal(job->line_count, STDERR_FILENO);
	env_put(": ");
	env_put(job->argv[0]);
	env_put(": ");
	env_put(estr);
}
/**
 * atoi_error -...
 * @s:...
 * Return:...
 */

int atoi_error(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * changeInt-...
 * @num:...
 * @base:...
 * @flags:...
 * Return:...
 */
char *changeInt(long int num, int base, int flags)
{
	static char buffer[50];
	char *p = buffer + sizeof(buffer) - 1;
	unsigned long n = num < 0 && !(flags & BLT_UNSC) ? -num : num;
	char sign = num < 0 && !(flags & BLT_UNSC) ? '-' : 0;
	char *chain = flags & BLT_CLC ? "0123456789abcdef" : "0123456789ABCDEF";

	*p = '\0';
	while (n != 0)
	{
		*--p = chain[n % base];
		n /= base;
	}
	if (sign)
		*--p = sign;
	return (p);
}

/**
 * no_hashtags -...
 * @buf:...
 */

void no_hashtags(char *buf)
{
	char *hashtag = _strchr(buf, '#');

	if (hashtag != NULL && (hashtag == buf || *(hashtag - 1) == ' '))
		*hashtag = '\0';
}
