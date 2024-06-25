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
	new = allocate(&ms->alloc, 1, sizeof(t_expand));
	if (!new)
		error_handler(ms);
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

bool	expand_option(char *value)
{
	while (*value && *value == '\"' && *(value + 1) == '\"')
		value += 2;
	if (*value == '\"')
		return (TRUE);
	while (*value && *value == '\'' && *(value + 1) == '\'')
		value += 2;
	if (*value == '\'')
		return (FALSE);
	return (TRUE);
}

char	*skip_to_var(t_minishell *ms, char *arg, int start, int *index)
{
	char	*sub;

	sub = NULL;
	while (arg[*index] && arg[*index] != '$')
		(*index)++;
	if (*index && arg[*index] == '$' && arg[*index - 1] == '\\')
		(*index)--;
	if (*index - start)
		sub = ft_substr(&ms->leaks, arg, start, *index - start);
	return (sub);
}

char	*get_to_expand(t_minishell *ms, char *arg, int start, int *index)
{
	char	*sub;

	sub = NULL;
	if (arg[*index] && arg[*index] == '\\')
		(*index) += 2;
	if (arg[*index] && arg[*index] == '$')
		(*index)++;
	while (arg[*index] && (ft_isalnum(arg[*index]) || arg[*index] == '_'))
		(*index)++;
	if (*index - start)
		sub = ft_substr(&ms->leaks, arg, start, *index - start);
	return (sub);
}

char	*remove_duplicate_qoutes(t_minishell *ms, char *value)
{
	char	*new;
	int		start;
	int		index;

	(TRUE) && (new = NULL, index = 0);
	while (value[index])
	{
		while (value[index]
			&& ((value[index] == '\"' && value[index + 1] == '\"')
			|| (value[index] == '\'' && value[index + 1] == '\'')))
			index += 2;
		start = index;
		if ((value[index] == '\"' || value[index] == '\''))
			index++;
		while (value[index] && value[index] != '\"' && value[index] != '\'')
			index++;
		new = ft_strjoin(&ms->leaks, new,
			ft_substr(&ms->leaks, value, start, index - start));
	}
	return (new);
}

char	*splite_to_expand(t_minishell *ms, char *arg)
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
		if (ft_strchr(expand->value, '$') && *expand->value == '$')
			expand->value = expand_val(ms, expand->value + 1);
		if (ft_strchr(expand->value, '$') && *expand->value == '\\')
			expand->value += 1;
		new = ft_strjoin(&ms->leaks, new, expand->value);
		expand = expand->next;
	}
	return (new);
}
