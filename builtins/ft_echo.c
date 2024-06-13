#include "../minishell.h"

void	check_options(char **args, int *i, int *option)
{
	int	j;
	int	found;

	found = 0;
	while (args[*i])
	{
		if (args[*i][0] == '-')
		{
			j = 1;
			while (args[*i][j])
			{
				if (args[*i][j] == 'n')
				{
					found = 1;
					j++;
				}
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

int ft_echo(char **args)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	// printf("I'M HERE");
	// while (args[i])
	// {
	// 	printf("arg :%s\n", args[i]);
	// 	i++;
	// }
	check_options(args, &i, &option);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!option)
		printf("\n");
	return (0);
}