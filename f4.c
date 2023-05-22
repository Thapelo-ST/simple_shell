#include "sh.h"

/**
 * adile - ...
 * @job:..
 * Return:...
 */

int adile(jobs *job)
{
/* declare variables*/
	size_t i = 0;
	list *node = NULL;

/* adding node to enviroment nodes */
	while (environ[i])
	{
		adne(&node, environ[i], 0);
		i++;
	}
/*assign enviroment with the new node*/
	job->env = node;
	return (0);
}

/**
 * own_unsetenv -...
 * @job:..
 * Return:...
 */

int own_unsetenv(jobs *job)
{
/* declare variables */
	int i;

/* checking argument validity */
	if (job->argc == 1)
	{
		env_put("add args.\n");
		return (1);
	}
/* unseting enviroment */
	for (i = 1; i <= job->argc; i++)
	{
/*checking if enviromen can be unset*/
		if (_unsetenv(job, job->argv[i]) != 0)
		{
			env_put("failed to unset env varriable\n");
			return (1);
		}
	}
	return (0);
}

/**
 * own_setenv - ...
 * @job:..
 * Return:...
 */

int own_setenv(jobs *job)
{
/* checking argc validity */
	if (job->argc != 3)
	{
		env_put("Fix arrguement number\n");
		return (1);
	}
/* checking if the enviroment is set */
	if (_setenv(job, job->argv[1], job->argv[2]))
	{
		env_put("cant set enviroment variable\n");
		return (0);
	}
	return (1);
}

/**
 * _fetch -...
 * @job:...
 * @name:..
 * Return:...
 */

char *_fetch(jobs *job, const char *name)
{
	list *node = job->env;
	char *p;

	while (node)
	{
		p = _bw(node->str, name);
		if (p && *p)
		{
			return (p);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * _enviroment -...
 * @job:...
 * Return:...
 */

int _enviroment(jobs *job)
{
	print_s(job->env);
	return (0);
}
