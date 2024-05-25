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

static char	*create_word(const char *s, int len)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc((sizeof(char)) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static char	**free_prev(char **s, int end)
{
	int	i;

	i = 0;
	while (end - i >= 0)
	{
		free(s[end - i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	**fill_in(char *s, char c, int count, char **arr)
{
	int		j;
	int		w;
	char	quotes;
	int		i;

	(1) && (w = -1, quotes = -1);
	while (++w < count)
	{
		while (*s && *s == c)
			s++;
		get_tokens(s, &j, &quotes);
		arr[w] = create_word(s, j);
		if (!arr[w])
			return (free_prev(arr, w));
		tokenize_operators(s, &j, arr, w);
		i = 0;
		while (*s && i <= j)
			(1) && (s++, i++);
	}
	arr[w] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		count;

	if (!s)
		return (NULL);
	count = words_counter(s, c);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	return (fill_in(s, c, count, arr));
}
