#include "minishell.h"

void	ft_env(t_environ *env)
{
	while (env)
	{
		printf("%s=%s\n", env->var, env->val);
		env = env->next;
	}
}
