/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 07:52:24 by abadouab          #+#    #+#             */
/*   Updated: 2024/04/19 15:14:47 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

size_t	strlen_set(char *s, char set)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] && s[i] != set)
		i++;
	return (i);
}

size_t	ft_search(char *s)
{
	size_t	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i++] == NLN)
			return (0);
	}
	return (1);
}

char	*strdup_set(char *str, char set)
{
	size_t	i;
	size_t	len;
	char	*new;

	if (!str || !*str)
		return (NULL);
	len = strlen_set(str, set);
	if (str[len] == NLN)
		len++;
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = str[i];
	return (new[i] = END, new);
}

char	*str_join(char *save, char *load)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!save)
		return (strdup_set(load, END));
	str = malloc(strlen_set(save, END) + strlen_set(load, END) + 1);
	if (!str)
		return (free(save), NULL);
	i = -1;
	while (save[++i])
		str[i] = save[i];
	j = 0;
	while (load[j])
		str[i++] = load[j++];
	return (str[i] = END, free(save), str);
}
