#include "sh.h"

/**
 * @brief Function to display the history.
 * @param job The jobs struct object.
 * @return 0 on successful execution.
 */

int _history(jobs *job)
{
        p_list(job->history);
        return (0);
}

/**
 * @brief Function to handle exit functionality.
 * @param job The jobs struct object.
 * @return -2 to indicate exit.
 */

int _exits(jobs *job)
{
	int exitcode = job->argv[1] ? _atoi(job->argv[1]) : -1;

	job->err_num = exitcode;
	return (-2);
}

/**
 * @brief Function to change the directory.
 * @param job The jobs struct object.
 * @return 0 on successful execution.
 */

int change_dir(jobs *job)
{
	char *dir, buffer[1024];
	int chdir_ret;

	if (!job->argv[1])
	{
		dir = _fetch(job, "HOME=");
		if (!dir) dir =
				  _fetch(job, "PWD=");
		if (!dir)
			dir = "/";
	}
	else if (_strcmp(job->argv[1], "-") == 0)
	{
		dir = _fetch(job, "OLDPWD=");
		if (!dir)
		{
			_puts(getcwd(buffer, sizeof(buffer))), _putchar('\n');
			return (1);
		}
		_puts(dir), _putchar('\n');
	}
	else
	{
		dir = job->argv[1];
	}
	chdir_ret = chdir(dir);
	if (chdir_ret == -1)
	{
		perr(job, "can't cd to ");
		env_put(job->argv[1]), env_putchar('\n');
	}
	else
	{
		_setenv(job, "OLDPWD", _fetch(job, "PWD="));
		_setenv(job, "PWD", getcwd(buffer, sizeof(buffer)));
	}
	return (0);
}

/**
 * @brief Function to display help information.
 * @param job The jobs struct object.
 * @return 0 on successful execution.
 */

int _help1(jobs *job)
{
	char **arg_arr = job->argv;
	_puts("help calls work.Function not avalible\n");
	if (arg_arr != NULL && *arg_arr != NULL)
	{
		_puts("name of that function is:\n");
		_puts(*arg_arr);
		_puts("\n");
	}
	return 0;
}
