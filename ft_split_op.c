#include "minishell.h"

int	cmp_operators(char c)
{
	char	operators[5];
	int		i;

	operators[0] = '|';
	operators[1] = '<';
	operators[2] = '>';
	operators[3] = '&';
	operators[4] = '\0';
	i = 0;
	while (operators[i] != '\0')
	{
		if (operators[i] == c)
			return (operators[i]);
		i++;
	}
	return (0);
}

static char	**fill_in(t_allocate **leaks, char **arr, char *s, char c)
{
	int		j;
	int		i;
	int		w;
	char	quotes;

	(1) && (w = 0, quotes = -1);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		get_tokens(s, &j, &quotes);
		arr[w] = allocate(leaks, j + 1, sizeof(char));
		if (!arr[w])
			return (NULL);
		ft_strlcpy(arr[w], s, j + 1);
		tokenize_operators(s, &j, arr, w);
		i = 0;
		while (*s && i <= j)
			(1) && (s++, i++);
		w++;
	}
	arr[w] = NULL;
	return (arr);
}

char	**ft_split_op(t_allocate **leaks, char const *s, char c)
{
	char	**arr;
	int		count;

	if (!s)
		return (NULL);
	count = words_counter(s, c);
	arr = allocate(leaks, count + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	return (fill_in(leaks, arr, (char *)s, c));
}
