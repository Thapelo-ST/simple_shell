#include "sh.h"

int mobility(jobs *job)
{
	int stdin_fileno = fileno(stdin);
	int input_isatty = isatty(stdin_fileno);
	int readfile = job->readfd <= 2;
	return (input_isatty && readfile);
}

int _isalpha(int c)
{
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                return (1);
        else
                return (0);
}

int _atoi(char *s)
{
	int si = 1;
	int res = 0;
	int digit;

	while (isspace(*s))
	{
		s++;
	}

	if (*s == '+' || *s == '-')
	{
		si = (*s == '-') ? -1 : 1;
		s++;
	}

	while (isdigit(*s))
	{
		digit = *s - '0';
		res = res * 10 + digit;
		s++;
	}

	return (si * res);
}

char **str_tok(char *str, char *d)
{
        int i, j, k, numwords = 0;
        char **s;

        if (!str || str[0] == '\0')
                return NULL;

        if (!d)
                d = " ";

        for (i = 0; str[i] != '\0'; i++)
                if (!check_del(str[i], d) && (check_del(str[i + 1], d) || !str[i + 1]))
                        numwords++;

        if (numwords == 0)
                return NULL;

        s = malloc((numwords + 1) * sizeof(char *));
        if (!s)
                return NULL;

        for (i = 0, j = 0; j < numwords; j++) {
                while (check_del(str[i], d))
                        i++;

                k = 0;
                while (!check_del(str[i + k], d) && str[i + k] != '\0')
                        k++;

                s[j] = malloc((k + 1) * sizeof(char));
                if (!s[j]) {
                        for (k = 0; k < j; k++)
                                free(s[k]);
                        free(s);
                        return NULL;
                }

                strncpy(s[j], &str[i], k);
                s[j][k] = '\0';
                i += k;
        }

        s[j] = NULL;
        return s;
}

char **split_string(char *str, char d)
{
        int i, j, k, numwords = 0;
        char **s;

        if (!str || str[0] == '\0')
                return (NULL);

        for (i = 0; str[i] != '\0'; i++)
                if ((str[i] != d && str[i + 1] == d) ||
                    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
                        numwords++;

        if (numwords == 0)
                return (NULL);

        s = malloc((numwords + 1) * sizeof(char *));
        if (!s)
                return (NULL);

        for (i = 0, j = 0; j < numwords; j++) {
                while (str[i] == d)
                        i++;

                k = 0;
                while (str[i + k] != d && str[i + k] != '\0')
                        k++;

                s[j] = malloc((k + 1) * sizeof(char));
                if (!s[j]) {
                        for (k = 0; k < j; k++)
                                free(s[k]);
                        free(s);
                        return (NULL);
                }

                strncpy(s[j], &str[i], k);
                s[j][k] = '\0';
                i += k;
        }

        s[j] = NULL;
        return (s);
}
