/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:18:31 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/19 16:52:01 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token_if_redir(char *token)
{
	if (check_if_operator(token)
		&& ft_strncmp(token, ">>", ft_strlen(token))
		&& ft_strncmp(token, "<<", ft_strlen(token))
		&& ft_strncmp(token, "<", ft_strlen(token))
		&& ft_strncmp(token, ">", ft_strlen(token)))
		return (1);
	return (0);
}

int	check_syntax_err(t_minishell *ms)
{
	int	i;

	i = 0;
	while (ms->tokens[i])
	{
		if (check_if_operator(ms->tokens[i])
			&& ft_strncmp(ms->tokens[i], ">>", ft_strlen(ms->tokens[i]))
			&& ft_strncmp(ms->tokens[i], "<<", ft_strlen(ms->tokens[i]))
			&& ft_strncmp(ms->tokens[i], "<", ft_strlen(ms->tokens[i]))
			&& ft_strncmp(ms->tokens[i], ">", ft_strlen(ms->tokens[i])))
			return (syntax_err(ms, NULL,
					"syntax error near unexpected token", 258), 1);
		i++;
	}
	return (0);
}

int	ft_here_doc_in_child(t_minishell *ms, pid_t pid, char *delimiter, int fds[])
{
	char	*line;

	if (pid == 0)
	{
		sig_heredoc();
		while (1)
		{
			line = readline("> ");
			if (!line || (ft_strncmp(line, delimiter, ft_strlen(line)) == 0
					&& ft_strlen(line) == ft_strlen(delimiter)))
				break ;
			else
				(write(fds[0], line, ft_strlen(line)), write(fds[0], "\n", 1));
			free(line);
		}
		if (close(fds[0]) < 0)
			return (ft_putstr_fd(strerror(errno), 2), -1);
		if (close(fds[1]) < 0)
			return (ft_putstr_fd(strerror(errno), 2), -1);
		exit(EXIT_SUCCESS);
	}
	if (!ms->tree->syntax_err)
		ms->exit_status = 0;
	return (0);
}

void	check_syntax_err_in_heredoc(t_minishell *ms)
{
	int	i;

	i = 0;
	while (ms &&  ms->tokens[i])
	{
		if ((check_op_syntax(ms->tokens[i]) == 0 && ms->tokens[i + 1]
		&& check_op_syntax(ms->tokens[i + 1]) == 0)
		|| (check_token_op(ms->tokens[i]) && ms->tokens[i + 1]
		&& check_token_op(ms->tokens[i + 1])))
			syntax_err(ms, NULL, "syntax error", 258);
		i++;
	}
	// check_closed_quotes(ms, 0, 0);
}

int	ft_open_here_doc(t_minishell *ms, char *delimiter, t_tree *node)
{
	int		fds[2];
	int		len;
	pid_t	pid;
	int		status;

	check_syntax_err_in_heredoc(ms);
	unlink("here_doc");
	fds[0] = open("here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	fds[1] = open("here_doc", O_RDONLY, 0644);
	if (fds[0] < 0 && fds[1] < 0)
		return (ft_putstr_fd(strerror(errno), 2), -1);
	(ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '\"'))
		&& (node->redir[node->redir_index].set_expand = 1);
	delimiter = splite_mult_args(ms, delimiter, FALSE, TRUE);
	(TRUE) && (unlink("here_doc"), len = ft_strlen(delimiter), pid = fork());
	if (pid < 0)
		return (perror("fork"), cleanup_handler(ms), -1);
	if (ft_here_doc_in_child(ms, pid, delimiter, fds) == -1)
		return (-1);
	waitpid(pid, &status, 0);
	(WIFSIGNALED(status)) && (g_catch_signals = SIGINT);
	(g_catch_signals == SIGINT) && (ms->exit_status = 1);
	if (close(fds[0]) < 0)
		return (ft_putstr_fd(strerror(errno), 2), -1);
	return (fds[1]);
}
