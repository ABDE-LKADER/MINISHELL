#include "minishell.h"

void	ft_exit(char **args)
{
	int	len;
	int	exit_status;

	len = 0;
	while (args[len])
		len++;
	ft_printf("exit\n");
	exit_status = 0;
	if (len > 2)
	{
		ft_printf("Minishell: exit: too many arguments\n");
		exit(1);
	}
	else if (len == 2)
	{
		len = 0;
		while (args[1][len])
		{
			if (!((args[1][len] >= '0' && args[1][len] <= '9')
				|| ((args[1][len] == '-' || args[1][len] == '+') && len == 0)))
				(ft_printf("Minishell: exit: %s: numeric argument required\n", args[1]),
				exit(2));
			len++;
		}
		exit_status = ft_atoi(args[1]);
	}
	exit(exit_status);
}
