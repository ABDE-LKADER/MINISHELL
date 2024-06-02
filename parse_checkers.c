/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:32 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/02 09:39:33 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token_op(char *token)
{
	char	*operators[4];
	int		i;

	operators[0] = "|";
	operators[1] = "||";
	operators[2] = "&&";
	operators[3] = NULL;
	if (!token)
		return (0);
	i = 0;
	while (operators[i])
	{
		if (ft_strncmp(token, operators[i], ft_strlen(token)) == 0
			&& ft_strlen(token) == ft_strlen(operators[i]))
			return (1);
		i++;
	}
	return (0);
}

void	set_op(t_tree *tree, char *token)
{
	if (ft_strncmp(token, "|", ft_strlen(token)) == 0)
		tree->type = PIPE_T;
	else if (ft_strncmp(token, "&&", ft_strlen(token)) == 0)
		tree->type = AND_T;
	else if (ft_strncmp(token, "||", ft_strlen(token)) == 0)
		tree->type = OR_T;
}

int	check_closed_quotes(char **tokens, int i, int j)
{
	char	quotes;

	i = 0;
	while (tokens[i])
	{
		(1) && (j = 0, quotes = -1);
		while (tokens[i][j])
		{
			if (tokens[i][j] == '"' || tokens[i][j] == '\'')
			{
				if (quotes > -1 && tokens[i][j] == quotes)
					quotes = -1;
				else if (quotes == -1)
					quotes = tokens[i][j];
			}
			j++;
		}
		if (quotes > -1)
			return (ft_putstr_fd("Minishell: ", 2),
				ft_putstr_fd("unexpected EOF while looking for matching `", 2),
				write(2, &quotes, 1), ft_putstr_fd("'\n", 2), 1);
		i++;
	}
	return (0);
}
