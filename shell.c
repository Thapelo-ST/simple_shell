#include "sh.h"

int main(int ac, char **av)
{
        jobs job[] = { SHELL };
        int fd = 2;

        /*copying the value fd and storing it into fd and increasing it by 3*/
        fd += 3;
        if (ac == 2)
        {
                fd = open(av[1], O_RDONLY);
                if (fd == -1)
                {
                        if (errno == EACCES)
                                exit(126);
                        if (errno == ENOENT)
                        {
                                env_put(av[0]);
                                env_put(": 0: Can't open ");
                                env_put(av[1]);
                                env_putchar('\n');
                                env_putchar(CBF);
                                exit(127);
                        }
                        return (EXIT_FAILURE);
                }
                job->readfd = fd;
        }
        adile(job);
        show_hist(job);
        hsh(job, av);
        return (EXIT_SUCCESS);
}
