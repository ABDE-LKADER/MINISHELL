#include "minishell.h"

int	ft_exit(char **args)
{
    int len;
    int exit_status;

    len = 0;
    while (args[len])
        len++;
    printf("exit\n");
    exit_status = 0;
    if (len > 2)
    {
        printf("Minishell: exit: too many arguments\n");
        exit(1);
    }
    else if (len == 2)
        exit_status = ft_atoi(args[1]);
    exit(exit_status);
}
