/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:32:56 by abadouab          #+#    #+#             */
/*   Updated: 2024/05/22 22:11:28 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*loc;
	size_t	bytes;

	loc = NULL;
	bytes = count * size;
	if (count != 0 && bytes / count != size)
		return (NULL);
	loc = malloc(bytes);
	if (!loc)
		return (NULL);
	ft_bzero(loc, bytes);
	return (loc);
}
