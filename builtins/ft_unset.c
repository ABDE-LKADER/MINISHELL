#include "minishell.h"

void    unset_target(t_environ **env, char *to_find)
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
				current = current->next;
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
		unset_target(&ms->env, args[index]);
}
