/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:17:03 by abadouab          #+#    #+#             */
/*   Updated: 2023/12/07 21:16:33 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;
	size_t	ld;
	size_t	ls;

	len = 0;
	ls = ft_strlen(src);
	if (!dst && !dstsize)
		return (ls);
	while (dst[len] && len < dstsize)
		len++;
	ld = len;
	if (dstsize > len)
	{
		i = 0;
		while (src[i] && len < dstsize - 1)
		{
			dst[len] = src[i];
			len++;
			i++;
		}
		dst[len] = '\0';
	}
	return (ld + ls);
}
