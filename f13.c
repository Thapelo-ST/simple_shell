#include "sh.h"
/**
 * clean_buffer - ...
 * @jobs:...
 * @job:..
 * Return:...
 */

int clean_buffer(void **ptr)
{
	return (ptr && *ptr) ? (free(*ptr), *ptr = NULL, 1) : 0;	
}

/**
 * check_cmd - ...
 * @jobs:...
 * @job:..
 * Return:...
*/

int check_cmd(jobs *job, char *path)
{
        struct stat st;
        (void)job;

        if (!path || stat(path, &st) || !(st.st_mode & S_IFREG))
                return (0);

        return (1);
}
/**
 * _repeat - ...
 * @jobs:...
 * @job:..
 * Return:...
*/
char *_repeat(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = start, k = 0;

	do {
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
		i++;
	} while (i < stop);

	buf[k] = '\0';
	return (buf);
}

/**
 * path_serch -...
 * @jobs:...
 * @job:..
 * Return:...
 */

char *path_serch(jobs *job, char *pathstr, char *cmd)
{
        int i = 0, curr_pos = 0;
        char *path;
        if (!pathstr)
                return (NULL);

        if ((_strlen(cmd) > 2) && _bw(cmd, "./"))
        {
                if (check_cmd(job, cmd))
                        return (cmd);
        }
        while (1)
        {
                if (!pathstr[i] || pathstr[i] == ':')
                {
                        path = _repeat(pathstr, curr_pos, i);
                        _strcat(path, (*path) ? "/" : "");
                        _strcat(path, cmd);
                        if (check_cmd(job, path))
                                return (path);
                        if (!pathstr[i])
                                break;
                        curr_pos = i;
                }
                i++;
        }
        return (NULL);
}
