#include "minishell.h"

void    unset_target(t_environ **env, char *to_find)
{
	t_environ	*loop;
	t_environ	*hold;

	loop = *env;
	if (!ft_strncmp(loop->var, to_find, ft_strlen(to_find)))
		*env = (*env)->next;
	while (loop->next)
	{
		if (!ft_strncmp(loop->next->var, to_find, ft_strlen(to_find)))
			;
		loop = loop->next;
	}
}

void	ft_unset(t_minishell *ms, char **args)
{
	int     index;

	index = 0;
	while (args[++index])
		unset_target(&ms->env, args[index]);
}
