#include "sh.h"

/**
 * _realloc - ...
 * @ptr:...
 * @old_size:...
 * @new_size:...
 * Return:...
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
/*declare variables*/
	void *p;
/*checking validity*/
/*allocate newsize*/
	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
/*return the new_size ptr*/
	if (new_size == old_size)
		return (ptr);
/*allocating memory and checking if memory is alocated*/
	p = malloc(new_size);
	if (!p)
		return (NULL);
	memcpy(p, ptr, (old_size < new_size) ? old_size : new_size);
	free(ptr);
	return (p);
}

/**
 * ffree - ...
 * @pp:...
 */

void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _memset - ...
 * @s:...
 * @b:...
 * @n:...
 * Return:...
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * hsh -...
 * @job:...
 * @av:..
 * Return:...
 */

int hsh(jobs *job, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clean1(job);
		if (mobility(job))
			_puts("$ ");
		env_putchar(CBF);
		r = own_getline(job);
		if (r != -1)
		{
			start_job(job, av);
			builtin_ret = get_blt(job);
			if (builtin_ret == -1)
				get_command(job);
		}
		else if (mobility(job))
			_putchar('\n');
		clean2(job, 0);
	}
	record(job);
	clean2(job, 1);
	if (!mobility(job) && job->status)
		exit(job->status);
	if (builtin_ret == -2)
	{
		if (job->err_num == -1)
			exit(job->status);
		exit(job->err_num);
	}
	return (builtin_ret);
}

/**
 * get_blt -...
 * @job:..
 * Return:...
 */

int get_blt(jobs *job)
{
	int i, rt_blt = -1;
	_table b_table[] = {
		{"exit", _exits},
		{"env", _enviroment},
		{"help", _help1},
		{"history", _history},
		{"setenv", own_setenv},
		{"unsetenv", own_unsetenv},
		{"cd", change_dir},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; b_table[i].blt_type; i++)
		if (_strcmp(job->argv[0], b_table[i].blt_type) == 0)
		{
			job->line_count++;
			rt_blt = b_table[i].func(job);
			break;
		}
	return (rt_blt);
}
