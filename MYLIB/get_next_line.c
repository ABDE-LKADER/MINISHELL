/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 09:10:23 by abadouab          #+#    #+#             */
/*   Updated: 2024/05/23 10:32:31 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	*allocate_set(t_allocate **alloc, char *str, char set)
{
	size_t	i;
	size_t	len;
	char	*new;

	if (!str || !*str)
		return (NULL);
	len = strlen_set(str, set);
	if (str[len] == NLN)
		len++;
	new = allocate(alloc, len + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = str[i];
	return (new[i] = END, new);
}

static char	*get_next(char *save)
{
	size_t	len;
	char	*new;

	if (!save || !*save)
		return (free(save), save = NULL, NULL);
	len = strlen_set(save, NLN);
	if (save[len] == NLN)
		len++;
	new = strdup_set(save + len, END);
	if (!new)
		return (free(save), save = NULL, NULL);
	return (free(save), save = NULL, new);
}

static char	*get_read(int fd, char *save)
{
	char	*load;
	int		bytes;

	bytes = 1;
	load = malloc((size_t)BUFFER_SIZE + 1);
	if (!load)
		return (free(save), save = NULL, NULL);
	while (ft_search(save) && bytes)
	{
		bytes = read(fd, load, BUFFER_SIZE);
		if (bytes == -1)
			return (free(load), free(save), NULL);
		load[bytes] = END;
		save = str_join(save, load);
		if (!save)
			break ;
	}
	return (free(load), save);
}

char	*get_next_line(t_allocate **alloc, int fd)
{
	static char	*save = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX
		|| read(fd, save, 0) == -1)
		return (free(save), save = NULL, NULL);
	save = get_read(fd, save);
	line = allocate_set(alloc, save, NLN);
	if (!line)
		return (free(save), save = NULL, NULL);
	return (save = get_next(save), line);
}
