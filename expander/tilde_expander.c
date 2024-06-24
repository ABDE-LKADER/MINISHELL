/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/11 14:46:14 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tilde_expander(t_environ *env)
{
	t_environ	*loop;

	loop = env;
	while (loop)
	{
		if (!ft_strncmp(loop->var, "HOME", ft_strlen(loop->var))
			&& ft_strlen(loop->var) == ft_strlen("HOME"))
			return (loop->val);
		loop = loop->next;
	}
	return (NULL);
}
