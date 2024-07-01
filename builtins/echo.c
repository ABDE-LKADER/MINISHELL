#include "minishell.h"

void	check_options(char **args, int *i, int *option)
{
	int		j;
	int		found;

	found = 0;
	while (args[*i])
	{
		if (args[*i][0] == '-')
		{
			j = 1;
			while (args[*i][j])
			{
				if (args[*i][j] == 'n')
					(TRUE) && (found = 1, j++);
				else if (args[*i][j] != '\0' && args[*i][j] != 'n')
					return ;
			}
			if (found)
				*option = 1;
		}
		else
			return ;
		(*i)++;
	}
}

void	ft_echo(t_minishell *ms, char **args)
{
	int	i;
	int	option;
	char	*str;

	i = 1;
	option = 0;
	check_options(args, &i, &option);
	while (args[i])
	{
		str = ft_strdup(&ms->leaks, args[i]);
		// ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			str = ft_strjoin(&ms->leaks, str, " ");
			// ft_putstr_fd(" ", 1);
		i++;
	}
	if (!option)
		str = ft_strjoin(&ms->leaks, str, "\n");
		// ft_putstr_fd("\n", 1);
	ft_putstr_fd(str, 1);
	ms->exit_status = 0;
}
