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

	i = 1;
	option = 0;
	check_options(args, &i, &option);
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!option)
		ft_printf("\n");
	ms->exit_status = 0;
}
