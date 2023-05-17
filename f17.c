#include "sh.h"

void get_command(jobs *job)
{
        char *path = NULL;
        int i, k;

        job->path = job->argv[0];
        if (job->linecount_flag == 1)
        {
                job->line_count++;
                job->linecount_flag = 0;
        }
        for (i = 0, k = 0; job->arg[i]; i++)
                if (!check_del(job->arg[i], " \t\n"))
                        k++;
        if (!k)
                return;

        path = path_serch(job, _fetch(job, "PATH="), job->argv[0]);
        if (path)
        {
                job->path = path;
                _fork(job);
        }
        else
        {
                if ((mobility(job) || _fetch(job, "PATH=")
		     || job->argv[0][0] == '/') && check_cmd(job, job->argv[0]))
                        _fork(job);
                else if (*(job->arg) != '\n')
                {
                        job->status = 127;
                        perr(job, "not found\n");
                }
        }
}


void _fork(jobs *job)
{
        pid_t child_pid;

        child_pid = fork();
        if (child_pid == -1)
        {
                perror("Error:");
                return;
        }
        if (child_pid == 0)
        {
                if (execve(job->path, job->argv, env_fetch(job)) == -1)
                {
                        clean2(job, 1);
                        if (errno == EACCES)
                                exit(126);
                        exit(1);
                }
                else
                        perror("ERROR forking the command");
        }
        else
        {
                wait(&(job->status));
                if (WIFEXITED(job->status))
                {
                        job->status = WEXITSTATUS(job->status);
                        if (job->status == 126)
                                perr(job, "Permission denied\n");
                }
        }
}

int _setenv(jobs *job, char *var, char *value)
{
        /* copy of origional setenv using variables of the shell */
        /*declare variables*/
        char *buf = NULL;
        list *node;
        char *p;
        /* checking validity */
        if (!var || !value)
                return (0);
        /*allocate memory*/
        buf = malloc(_strlen(var) + _strlen(value) + 2);
        if (!buf)
                return (1);
        /* asigning variables and concatinating to buffer */
        _strcpy(buf, var);
        _strcat(buf, "=");
        _strcat(buf, value);
        node = job->env;
        /* setting enviroment enviroment */
        for (node = job->env; node; node = node->next)
        {
                if ((p = _bw(node->str, var)) && *p == '=')
                {
                        /*free if match*/
                        free(node->str);
                        /* reassign the node with whats left in the buffer */
                        node->str = buf;
                        job->env_changed = 1;
                        return (0);
                }
        }
        adne(&(job->env), buf, 0);
        job->env_changed = 1;
        free(buf);
        return (0);
}


int _unsetenv(jobs *job, char *var)
{
        /* copy of origional setenv using variables of the shell */
        /* declaring variables */
        list *node = job->env;
        size_t i = 0;
        char *p;

        /*checking validity*/
        return (node && var ? 1 : 0);
        /* repeat until you find the same as var*/
        while (node && (!(p = _bw(node->str, var)) || *p != '='))
        {
                node = node -> next;
                i++;
        }
        /* delete node containing env */
        job->env_changed = node ? dnai(&job->env, i) : 0;
        return (job->env_changed);
}

char **env_fetch(jobs *job)
{
        /*check if the enviroment is null
         *if true, enviroment willbe set to the list of strings result
         * else it will stay the same
         */
        job->environ = !job->environ || job->env_changed ?
                list_str(job->env) : job->environ;
        job->env_changed = 0;
        return (job->environ);
}
