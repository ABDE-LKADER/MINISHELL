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
		while (!pid && env)
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

bool	search_env(t_minishell *ms, t_environ *env, char *arg)
{
	char	*to_find;

	to_find = ft_substr(&ms->alloc, arg, 0, strlen_set(arg, '='));
	while (env)
	{
		if (!ft_strncmp(env->var, to_find, ft_strlen(to_find))
			&& ft_strlen(to_find) == ft_strlen(env->var))
		{
			if (ft_strchr(arg, '='))
				env->val = ft_substr(&ms->alloc, arg, strlen_set(arg, '=')
					+ 1, ft_strlen(arg));
			return (TRUE);
		}
		env = env->next;
	}
	return (FALSE);
}

void	create_to_export(t_minishell *ms, t_environ *env, char **args, int *status)
{
	while (*args)
	{
		if ((!ft_isalpha(**args) && **args != '_')
			|| !valid_identifier(*args, strlen_set(*args, '=')))
		{
			syntax_err(ms, *args, "not a valid identifier", 1);
			*status = 1;
		}
		else if (!search_env(ms, env, *args))
		{
			if (ft_strchr(*args, '='))
				environment_add(ms, &ms->env,
					ft_substr(&ms->alloc, *args, 0, strlen_set(*args, '=')),
					ft_substr(&ms->alloc, *args, strlen_set(*args, '=') + 1,
					ft_strlen(*args)));
			else
				environment_add(ms, &ms->env, ft_substr(&ms->alloc, *args,
					0, strlen_set(*args, '=')), NULL);
		}
		args++;
	}
}

void	ft_export(t_minishell *ms, t_environ *env, char **args)
{
	int		len;
	int		status;

	(TRUE) && (len = 0, status = 0);
	while (args[len])
		len++;
	if (len == 1)
		export_list(env);
	if (len != 1)
		create_to_export(ms, env, ++args, &status);
	if (!status)
		ms->exit_status = status;
}
