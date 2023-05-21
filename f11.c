#include "sh.h"

/**
 * hist_list -...
 * @job:...
 * @buf:...
 * @linecount:...
 * Return:...
 */

int hist_list(jobs *job, char *buf, int linecount)
{
        /* initialize variables */
        /* initialize node to history if its not null else assign it to null */
        list *node = job->history ? job->history : NULL;
        adne(&node, buf, linecount);
        /*re-assigning history to origional history if its not null else to node*/
        job->history = job->history ? job->history : node;
        return (0);
}
/**
 * fetch_fh -...
 * @job:...
 * Return:...
 */

char *fetch_fh(jobs *job)
{
        char *buf, *dir;

        dir = _fetch(job, "HOME=");
        if (!dir)
                return (NULL);
        buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HFS) + 2));
        if (!buf)
        {
                free(dir);
                return (NULL);
        }
        sprintf(buf, "%s/%s", dir, HFS);
        return (buf);
}

/**
 * show_hist -...
 * @job:...
 * Return:...
 */
int show_hist(jobs *job)
{
        int i, last = 0, linecount = 0;
        ssize_t fd, rdlen, fsize = 0;
        struct stat st;
        char *buf = NULL, *filename = fetch_fh(job);

        if (!filename)
                return (0);

        fd = open(filename, O_RDONLY);
        free(filename);
        if (fd == -1)
                return (0);
        if (!fstat(fd, &st))
                fsize = st.st_size;
        if (fsize < 2)
                return (0);
        buf = malloc(sizeof(char) * (fsize + 1));
        if (!buf)
                return (0);
        rdlen = read(fd, buf, fsize);
        buf[fsize] = 0;
        if (rdlen <= 0)
                return (free(buf), 0);
        close(fd);
        for (i = 0; i < fsize; i++)
                if (buf[i] == '\n')
                {
                        buf[i] = 0;
                        hist_list(job, buf + last, linecount++);
                        last = i + 1;
                }
        if (last != i)
                hist_list(job, buf + last, linecount++);
        free(buf);
        job->histcount = linecount;
        while (job->histcount-- >= HMAX)
                dnai(&(job->history), 0);
        c_hist(job);
        return (job->histcount);
} 

/**
 * record -...
 * @job:...
 * Return:...
 */

int record(jobs *job)
{
        ssize_t fd;
        list *node = NULL;

        char *filename = fetch_fh(job);
        if (!filename)
                return (-1);
        fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
        free(filename);
        if (fd == -1)
                return (-1);
        for (node = job->history; node; node = node->next)
        {
                show_filedir(node->str, fd);
                print_filedir('\n', fd);
        }
        print_filedir(CBF, fd);
        close(fd);
        return (1);
}

/**
 * c_hist-...
 * @job:...
 * Return:...
 */

int c_hist(jobs *job)
{
        /*initialize variable*/
        int i = 0;
        list *node;

        /*assign a unique number to an entry*/
        for (node = job->history; node != NULL; node = node->next)
                node->num = i++;
        job->histcount = i;
        /* return total number of all history entries on the list */
        return (i);
}
