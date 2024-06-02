/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:37 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/02 18:09:28 by abbaraka         ###   ########.fr       */
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

int	ft_open_here_doc(char *delimiter)
{
	int		fd;
	int		fd1 = -1;
	char	*line;
	char	*buffer = NULL;
	t_allocate	*coll;
	int		len;
	pid_t	pid;

	unlink("here_doc");
	fd = open("here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	fd1 = open("here_doc", O_RDONLY, 0644);
	unlink("here_doc");
	len = ft_strlen(delimiter);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if 
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strncmp(line, delimiter, ft_strlen(line)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter)))
			break ;
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
	}
	close(fd);
	buffer = get_next_line(&coll, fd1);
	printf("%s", buffer);
	buffer = get_next_line(&coll, fd1);
	printf("%s", buffer);
	return (fd1);
}

void	set_redir(t_tree *node, char **tokens, int *i)
{
	if (ft_strncmp(tokens[*i], ">", ft_strlen(tokens[*i])) == 0)
	{
		node->redir[node->redir_index].redirection = OUT_RED_T;
		node->redir[node->redir_index].fd = -1;
	}
	else if (ft_strncmp(tokens[*i], "<", ft_strlen(tokens[*i])) == 0)
	{
		node->redir[node->redir_index].redirection = IN_RED_T;
		node->redir[node->redir_index].fd = -1;
	}
	else if (ft_strncmp(tokens[*i], ">>", ft_strlen(tokens[*i])) == 0)
	{
		node->redir[node->redir_index].redirection = OUT_RED_APPEND_T;
		node->redir[node->redir_index].fd = -1;
	}
	else if (ft_strncmp(tokens[*i], "<<", ft_strlen(tokens[*i])) == 0)
	{
		node->redir[node->redir_index].redirection = HERE_DOC_T;
		node->redir[node->redir_index].fd = ft_open_here_doc(tokens[*i + 1]);
	}
}

int	count_redir(char **tokens)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (tokens[i])
	{
		if (check_if_operator(tokens[i]))
			counter++;
		i++;
	}
	return (counter);
}

int	count_args(char **tokens)
{
	int	i;
	int	j;
	int	counter;

	(1) && (i = 0, j = 0, counter = 0);
	while (tokens[i] && !check_token_op(tokens[i]))
		i++;
	while (j < i)
	{
		if (tokens[j] && tokens[j + 1] && check_if_operator(tokens[j]))
			j += 2;
		if (tokens[j] && !check_if_operator(tokens[j]))
		{
			counter++;
			j++;
		}
		else
			j++;
	}
	return (counter);
}

t_tree	*parse_simple_command(t_allocate **leaks, char **tokens, int *i)
{
	t_tree		*node;
	int			redir_set;

	if (check_token_op(tokens[*i]))
		return (syntax_err("syntax error", 258), NULL);
	node = allocate(leaks, 1, sizeof(t_tree));
	(1) && (redir_set = 0, node->redir_index = 0,
	node->syntax_err = 0);
	node->redir = allocate(leaks, count_redir(tokens) + 1, sizeof(t_redir));
	node->args = allocate(leaks, count_args(tokens + *i) + 1, sizeof(char *));
	if (check_redirection(node, tokens, i, &redir_set))
		return (NULL);
	if (!tokens[*i])
		return (NULL);
	node->type = CMD_T;
	node->value = tokens[*i];
	(1) && (node->left = NULL, node->right = NULL);
	(1) && (redir_set = 0);
	if (tokens[*i] && !check_token_op(tokens[*i]))
		check_args(node, tokens + *i, count_args(tokens + *i));
	if (check_redir_at_end(node, tokens, i, &redir_set))
		return (NULL);
	if (node->syntax_err)
		return (NULL);
	return (node);
}
