#include "minishell.h"

void	env_unset_target(t_environ **env, char *to_find)
{
	t_environ	*current;
	t_environ	*previous;

	current = *env;
	previous = NULL;
	while (current)
	{
		if (!ft_strncmp(current->var, to_find, ft_strlen(to_find))
			&& ft_strlen(current->var) == ft_strlen(to_find))
		{
			if (!previous)
				*env = current->next;
			else
				previous->next = current->next;
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	export_unset_target(t_environ **env, char *to_find)
{
	int			pad;
	t_environ	*current;
	t_environ	*previous;

	current = *env;
	previous = NULL;
	pad = ft_strlen("declare -x ");
	while (current)
	{
		if (!ft_strncmp(current->var + pad, to_find, ft_strlen(to_find))
			&& ft_strlen(current->var + pad) == ft_strlen(to_find))
		{
			if (!previous)
				*env = current->next;
			else
				previous->next = current->next;
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	ft_unset(t_minishell *ms, char **args)
{
	int     index;

	index = 0;
	while (args[++index])
	{
		env_unset_target(&ms->env, args[index]);
		export_unset_target(&ms->export, args[index]);
	}
}
