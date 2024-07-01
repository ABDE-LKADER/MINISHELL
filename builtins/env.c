#include "minishell.h"

void	ft_env(t_minishell *ms, t_environ *env)
{
	while (env)
	{
		if (env->val)
			ft_printf("%s=%s\n", env->var, env->val);
		env = env->next;
	}
	ms->exit_status = 0;
}
