#include "minishell.h"

void	check_quotes_counting(char *s, int *i, int *counter, char quotes_type)
{
	(*i)++;
	while (s[*i] && s[*i] != quotes_type)
		(*i)++;
	if (s[*i] == quotes_type)
		(*i)++;
	else if (s[*i] && cmp_operators(s[*i]))
		;
	else
	{
		while (s[*i] && s[*i] != ' ')
			(*i)++;
		if (s[*i])
			(*i)++;
	}
	if (s[*i] == ' ' || s[*i] == '\0' || cmp_operators(s[*i]))
		(*counter)++;
}

int	quotes_counter(char *s, int *i, int *counter)
{
	if (s[*i] == '\'')
	{
		check_quotes_counting(s, i, counter, '\'');
		return (1);
	}
	else if (s[*i] == '\"')
	{
		check_quotes_counting(s, i, counter, '\"');
		return (1);
	}
	return (0);
}

// int	parentheses_counter(char *s, int *i, int *counter)
// {
// 	int	level;

// 	level = 0;
// 	if (s[*i] && s[*i] == '(')
// 	{
// 		level++;
// 		(*i)++;
// 		while (s[*i])
// 		{
// 			if (s[*i] && s[*i] == '(')
// 				level++;
// 			if (s[*i] && s[*i] == ')')
// 				level--;
// 			(*i)++;
// 			if (level == 0)
// 				break ;
// 		}
// 		if (s[*i] == ')')
// 			(*i)++;
// 		if (cmp_operators(s[*i]))
// 			;
// 		(*counter)++;
// 		return (1);
// 	}
// 	return (0);
// }

int	words_counter(const char *s, char c)
{
	int	i;
	int	counter;

	(1) && (i = 0, counter = 0);
	while (s[i])
	{
		if (quotes_counter((char *)s, &i, &counter))
			;
		else if ((s[i] != c) && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (counter);
}
