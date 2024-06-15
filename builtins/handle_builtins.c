#include "minishell.h"

int	check_if_builtins(t_minishell *ms, char **args)
{
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (ft_echo(args), 1);
	else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (ft_pwd(), 1);
	else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		return (ft_export(ms->export, args), 1);
	else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		return (ft_unset(ms, args), 1);
	else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return (ft_env(ms->env), 1);
	else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		return (ft_exit(args), 1);
	return (0);
}
