#include "minishell.h"

char	*inject_spaces(t_minishell *ms, char *s)
{
	char			*str;
	t_inject_data	data;

	if (!s)
		return (NULL);
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
		if (!splitted_by_space)
			return (free(str), cleanup(&ms.leaks), 0);
		while (splitted_by_space[i])
			printf("token: %s\n", splitted_by_space[i++]);
		free(str);
	}
	cleanup(&ms.leaks);
	return (0);
}
