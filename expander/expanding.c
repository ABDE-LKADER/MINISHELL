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

void	expand_add(t_minishell *ms, t_expand **expand, void *value)
{
	t_expand	*new;
	t_expand	*node;

	if (!value)
		return ;
	new = allocate(&ms->leaks, 1, sizeof(t_expand));
	if (!new)
		cleanup_handler(ms);
	new->value = value;
	new->next = NULL;
	if (!*expand)
	{
		*expand = new;
		return ;
	}
	node = *expand;
	while (node->next)
		node = node->next;
	node->next = new;
}

char	*skip_to_var(t_minishell *ms, char *arg, int start, int *index)
{
	char	*sub;

	sub = NULL;
	while (arg[*index] && arg[*index] != '$')
		(*index)++;
	if (*index - start)
		sub = ft_substr(&ms->leaks, arg, start, *index - start);
	return (sub);
}

char	*get_to_expand(t_minishell *ms, char *arg, int start, int *index)
{
	char	*sub;

	sub = NULL;
	if (arg[*index] && arg[*index] == '$')
		(*index)++;
	while (arg[*index] && (ft_isalnum(arg[*index]) || arg[*index] == '_'))
		(*index)++;
	if (arg[*index] && arg[*index - 1] == '$'
		&& (arg[*index] == '$' || arg[*index] == '?'))
		(*index)++;
	if (*index - start)
		sub = ft_substr(&ms->leaks, arg, start, *index - start);
	return (sub);
}

char	*splite_to_expand(t_minishell *ms, char *arg, bool option)
{
	char		*new;
	int			index;
	t_expand	*expand;

	(TRUE) && (index = 0, new = NULL, expand = NULL);
	while (arg[index])
	{
		expand_add(ms, &expand, skip_to_var(ms, arg, index, &index));
		expand_add(ms, &expand, get_to_expand(ms, arg, index, &index));
	}
	while (expand)
	{
		if (*expand->value == '$'
			&& expand_option(arg, expand->value, option))
			expand->value = expand_val(ms, expand->value);
		new = ft_strjoin(&ms->leaks, new, expand->value);
		expand = expand->next;
	}
	return (new);
}
