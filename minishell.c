#include "minishell.h"

int	count_op(char *s)
{
	int		i;
	int		space_counter;
	char	quotes;

	(1) && (i = 0, space_counter = 0, quotes = -1);
	while (s[i])
	{
		if (s[i] && quotes == -1 && (s[i] == '\"' || s[i] == '\''))
		{
			quotes = s[i];
			while (s[i] && s[i] != quotes)
				i++;
		}
		else if (s[i] && s[i] == quotes)
			(1) && (quotes = -1, i++);
		if (s[i] == '\0')
			break ;
		if (quotes == -1 && i != 0 && cmp_operators(s[i])
			&& ((s[i - 1] && (s[i - 1] != ' ' && !cmp_operators(s[i - 1])))
				|| (s[i + 1] != ' ' && !cmp_operators(s[i + 1]))))
			space_counter++;
		i++;
	}
	return (space_counter);
}

void	copy_quotes(t_inject_data *data, char *s, char *str)
{
	if (s[data->i] && data->quotes == -1
		&& (s[data->i] == '\"' || s[data->i] == '\''))
	{
		data->quotes = s[data->i];
		while (s[data->i] && s[data->i] != data->quotes)
			(1) && (str[data->j] = s[data->i], data->i++, data->j++);
	}
	else if (s[data->i] && s[data->i] == data->quotes)
		(1) && (data->quotes = -1, str[data->j] = s[data->i],
		data->i++, data->j++);
}

void	copy_and_inject_spaces(t_inject_data *data, char *s, char *str)
{
	copy_quotes(data, s, str);
	if (s[data->i] == '\0')
		return ;
	if (data->quotes == -1 && data->i != 0 && cmp_operators(s[data->i])
		&& s[data->i - 1] && (s[data->i - 1] != ' '
			&& !cmp_operators(s[data->i - 1])))
	{
		(1) && (str[data->j] = ' ', data->j++,
		str[data->j] = s[data->i], data->j++);
		if (cmp_operators(s[data->i]) && s[data->i + 1]
			&& (s[data->i + 1] != ' ' && !cmp_operators(s[data->i + 1])))
			(1) && (str[data->j] = ' ', data->j++);
		data->i++;
	}
	else if (data->quotes == -1 && cmp_operators(s[data->i]) && s[data->i + 1]
		&& (s[data->i + 1] != ' ' && !cmp_operators(s[data->i + 1])))
		(1) && (str[data->j] = s[data->i], data->j++,
		str[data->j] = ' ', data->j++, data->i++);
	else if (s[data->i])
		(1) && (str[data->j] = s[data->i], data->j++, data->i++);
}

char	*inject_spaces(t_minishell *ms, char *s)
{
	char			*str;
	t_inject_data	data;

	(TRUE) && (data.len = ft_strlen(s), data.len += count_op(s),
		data.i = 0, data.j = 0, data.quotes = -1);
	str = allocate(&ms->leaks, data.len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s[data.i])
		copy_and_inject_spaces(&data, s, str);
	str[data.j] = '\0';
	return (str);
}

int	main(void)
{
	t_minishell		ms;
	char			*str;
	char			*injected_spaces;
	char			**splitted_by_space;
	int				i;

	ft_bzero(&ms, sizeof(t_minishell));
	while (1)
	{
		str = readline("Minishell >$ ");
		if (!str)
			break ;
		injected_spaces = inject_spaces(&ms, str);
		splitted_by_space = ft_split_op(&ms.leaks, injected_spaces, ' ');
		i = 0;
		while (splitted_by_space[i])
			printf("token: %s\n", splitted_by_space[i++]);
		free(str);
	}
	cleanup(&ms.leaks);
	return (0);
}
