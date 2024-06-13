#include "../minishell.h"

int	check_if_builtins(char **args)
{
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (ft_echo(args), 1);
	else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (ft_pwd(), 1);
	else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		return (ft_exit(args), 1);
	return (0);
}