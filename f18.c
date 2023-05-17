#include "sh.h"

char *_bw(const char *haystack, const char *needle)
{
        while (*needle)
                if (*needle++ != *haystack++)
                        return (NULL);
        return ((char *)haystack);
}


ssize_t scan_buffer(jobs *job, char *buf, size_t *i)
{
        ssize_t r = 0;

        if (*i)
                return (0);
        r = read(job->readfd, buf, BSZ);
        if (r >= 0)
                *i = r;
        return (r);
}

int check_del(char c, char *delim)
{
	int i;

	for (i = 0; delim[i] != '\0'; i++)
	{
		if (c == delim[i])
		{
			return (1);
		}
	}
	return (0);
}
