/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_checkers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darkab <darkab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:19 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/13 21:13:52 by darkab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_op(char *token)
{
	char	ops[3];
	int		i;

	ops[0] = '|';
	ops[1] = '&';
	ops[2] = '\0';
	i = 0;
	while (ops[i])
	{
		if (token[0] == ops[i] && !check_token_op(token))
			return (1);
		i++;
	}
	return (0);
}

int	check_op_syntax(char *token)
{
	char	*ops[5];
	int		i;

	ops[0] = ">";
	ops[1] = "<";
	ops[2] = "<<";
	ops[3] = ">>";
	ops[4] = NULL;
	i = 0;
	while (ops[i])
	{
		if (ft_strncmp(token, ops[i], ft_strlen(token)) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_if_operator(char *token)
{
	char	*ops[3];
	int		i;

	ops[0] = ">";
	ops[1] = "<";
	ops[2] = NULL;
	i = 0;
	while (token && ops[i])
	{
		if (ft_strncmp(token, ops[i], ft_strlen(ops[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	check_args(t_tree *node, char **tokens, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i] && !check_token_op(tokens[i]))
	{
		if (tokens[i] && tokens[i + 1] && check_if_operator(tokens[i]))
			i += 2;
		else if (tokens[i] && (ft_strncmp(tokens[i], "(", ft_strlen(tokens[i])) == 0
				|| ft_strncmp(tokens[i], ")", ft_strlen(tokens[i])) == 0))
			i++;
		else if (tokens[i])
		{
			if (j < len && !check_if_operator(tokens[i]))
			{
				node->args[j] = tokens[i];
				j++;
			}
			i++;
		}
	}
}
