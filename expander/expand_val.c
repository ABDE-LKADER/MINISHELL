/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/27 18:32:13 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**change_linked_to_double(t_minishell *ms)
{
	int			i;
	int			len;
	t_environ	*tmp;
	char		**env;

	(1) && (tmp = ms->env, len = 0);
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	env = allocate(&ms->leaks, len + 1, sizeof(char *));
	if (!env)
		cleanup_handler(ms);
	tmp = ms->env;
	i = 0;
	while (tmp)
	{
		env[i] = ft_strjoin(&ms->leaks, tmp->var, "=");
		env[i] = ft_strjoin(&ms->leaks, env[i], tmp->val);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

char	*expand_doller(t_minishell *ms)
{
	int		pid;
	char	*id;
	t_fds	fds;
	char	*args[4];
	int		pipes[2];

	(TRUE) && (args[0] = "pgrep", args[1] = "-a", args[2] = "minishell",
		args[3] = NULL, fds = save_fds(), pipe(pipes), pid = fork());
	if (pid == 0)
	{
		(dup2(pipes[1], STDOUT_FILENO), close(pipes[1]), close(pipes[0]));
		execve(fetch_path(ms, ms->env, args[0]), args,
			change_linked_to_double(ms));
		exit (EXIT_FAILURE);
	}
	(waitpid(pid, NULL, 0), id = get_next_line(&ms->leaks, pipes[0]),
		close(pipes[0]), close(pipes[1]), restore_fds(fds));
	return (*ft_split(&ms->leaks, id, '\n'));
}

bool	only_var(t_minishell *ms, char *arg)
{
	int		len;
	char	**hold;
	char	*value;

	len = ft_strlen(arg);
	if (*arg != '$' || arg[len - 1] == '$'
		|| ft_strnstr(arg, "$$", len))
		return (TRUE);
	hold = ft_split(&ms->leaks, arg, '$');
	if (!hold)
		cleanup_handler(ms);
	if (!*hold)
		return (TRUE);
	while (*hold)
	{
		if ((!ft_isalpha(**hold) && **hold != '_')
			|| !check_valid_identifier(*hold))
			return (TRUE);
		value = get_env_val(ms, *hold);
		if (value && *value)
			return (TRUE);
		hold++;
	}
	return (FALSE);
}

char	*expand_val(t_minishell *ms, char *value)
{
	t_environ	*loop;

	if (!ft_strncmp(value, "$$", ft_strlen(value))
		&& ft_strlen("$$") == ft_strlen(value))
		return (expand_doller(ms));
	if (!ft_strncmp(value, "$?", ft_strlen(value))
		&& ft_strlen("$?") == ft_strlen(value))
		return (ft_itoa(&ms->leaks, ms->exit_status));
	(TRUE) && (value++, loop = ms->env);
	if (ft_isdigit(*value))
		return (value + 1);
	while (loop)
	{
		if (!ft_strncmp(loop->var, value, ft_strlen(value))
			&& ft_strlen(value) == ft_strlen(loop->var))
		{
			if (!loop->val)
				break ;
			if (loop->val)
				return (loop->val);
		}
		loop = loop->next;
	}
	return (ft_strdup(&ms->leaks, ""));
}
