#include "minishell.h"

int	check_if_builtins(t_minishell *ms, char **args)
{
	if (!ft_strncmp(*args, "echo", ft_strlen(*args)))
		return (ft_echo(args), 1);
	else if (!ft_strncmp(*args, "cd", ft_strlen(*args)))
		return (1);
	else if (!ft_strncmp(*args, "pwd", ft_strlen(*args)))
		return (ft_pwd(), 1);
	else if (!ft_strncmp(*args, "export", ft_strlen(*args)))
		return (ft_export(ms->export, args), 1);
	else if (!ft_strncmp(*args, "unset", ft_strlen(*args)))
		return (ft_unset(ms, args), 1);
	else if (!ft_strncmp(*args, "env", ft_strlen(*args)))
		return (ft_env(ms->env), 1);
	else if (!ft_strncmp(*args, "exit", ft_strlen(*args)))
		return (ft_exit(args), 1);
	return (0);
}
