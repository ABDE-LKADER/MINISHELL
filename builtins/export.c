/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by ||||||||          #+#    #+#             */
/*   Updated: 2024/07/13 01:56:09 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_export_vars(t_environ **export)
{
	size_t		len;
	void		*var;
	void		*val;
	t_environ	*first;
	t_environ	*second;

	(TRUE) && (len = 0, first = *export);
	while (first)
	{
		second = first->next;
		while (second)
		{
			len = ft_strlen(first->var);
			if (len < ft_strlen(second->var))
				len = ft_strlen(second->var);
			if (ft_strncmp(first->var, second->var, len) > 0)
			{
				(TRUE) && (var = first->var, val = first->val);
				(TRUE) && (first->var = second->var, first->val = second->val);
				(TRUE) && (second->var = var, second->val = val);
			}
			second = second->next;
		}
		first = first->next;
	}
}

static void	export_list(t_environ *env)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		sort_export_vars(&env);
		while (env)
		{
			if (!env->val)
				ft_printf("declare -x %s\n", env->var);
			else if (ft_strncmp(env->var, "_", ft_strlen(env->var)))
				ft_printf("declare -x %s=\"%s\"\n", env->var, env->val);
			env = env->next;
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
}

bool	search_env(t_minishell *ms, t_environ *env, char *arg, int _len)
{
	int		len;
	char	*new_val;
	char	*to_find;

	((arg)[_len - 1] == '+' && arg[_len] == '=') && (_len--);
	to_find = ft_substr(&ms->leaks, arg, 0, _len);
	while (env)
	{
		if (!ft_strncmp(env->var, to_find, ft_strlen(to_find))
			&& ft_strlen(to_find) == ft_strlen(env->var))
		{
			if (ft_strchr(arg, '='))
			{
				(TRUE) && (len = strlen_set(arg, '='), new_val =
					ft_substr(&ms->alloc, arg, len + 1, ft_strlen(arg)));
				if (arg[len - 1] == '+' && arg[len] == '=')
					env->val = ft_strjoin(&ms->alloc, env->val, new_val);
				else
					env->val = new_val;
			}
			return (TRUE);
		}
		env = env->next;
	}
	return (FALSE);
}

void	create_to_export(t_minishell *ms, t_environ *env, char **args,
	int *status)
{
	int		len;

	while (*args)
	{
		if (**args && ((!ft_isalpha(**args) && **args != '_')
				|| !valid_identifier(*args, strlen_set(*args, '='))))
		{
			syntax_err(ms, *args, "not a valid identifier", 1);
			*status = 1;
		}
		else if (**args && !search_env(ms, env, *args, strlen_set(*args, '=')))
		{
			len = strlen_set(*args, '=');
			((*args)[len - 1] == '+' && (*args)[len] == '=') && (len--);
			if (ft_strchr(*args, '='))
				environment_add(ms, &ms->env, ft_substr(&ms->alloc, *args, 0,
						len), ft_substr(&ms->alloc, *args, strlen_set(*args,
							'=') + 1, ft_strlen(*args)));
			else
				environment_add(ms, &ms->env, ft_substr(&ms->alloc, *args,
						0, len), NULL);
		}
		args++;
	}
}

void	ft_export(t_minishell *ms, t_environ *env, char **args)
{
	int		len;
	int		index;
	int		status;

	(TRUE) && (len = 0, index = -1, status = 0);
	while (args[++index])
		(*args[index]) && (len++);
	if (len == 1)
		export_list(env);
	if (len != 1)
		create_to_export(ms, env, ++args, &status);
	if (!status)
		ms->exit_status = status;
}
