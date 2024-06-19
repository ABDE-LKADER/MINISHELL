#include "minishell.h"

static void	export_list(t_environ *export)
{
	while (export)
	{
		ft_printf("%s=%s\n", export->var, export->val);
		export = export->next;
	}
}

void	ft_export(t_minishell *ms, t_environ *export, char **args)
{
	int		len;

	len = 0;
	while (args[len])
		len++;
	if (len == 1)
		export_list(export);
	if (len != 1)
	{
		while (*args++)
		{
			environment_add(ms, &ms->env,
				ft_substr(&ms->alloc, *args, 0, strlen_set(*args, '=')),
				ft_substr(&ms->alloc, *args, strlen_set(*args, '=') + 1,
				ft_strlen(*args)));
			environment_add(ms, &ms->export,
				ft_substr(&ms->alloc, *args, 0, strlen_set(*args, '=')),
				ft_substr(&ms->alloc, *args, strlen_set(*args, '=') + 1,
				ft_strlen(*args)));
		}
		sort_export_vars(&ms->export);
	}
}
