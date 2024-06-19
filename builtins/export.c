#include "minishell.h"

static void	export_list(t_environ *export)
{
	while (export)
	{
		printf("%s=%s\n", export->var, export->val);
		export = export->next;
	}
}

void	ft_export(t_environ *export, char **args)
{
	int     len;

	len = 0;
	while (args[len])
		len++;
	if (len == 1)
		export_list(export);
}
