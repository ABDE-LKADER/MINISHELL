/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:35:42 by abadouab          #+#    #+#             */
/*   Updated: 2024/05/23 10:03:04 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	*ft_substr(t_allocate **alloc, char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*str;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(alloc, ""));
	if (len > slen - start)
		len = slen - start;
	str = allocate(alloc, len + 1, sizeof(char));
	if (!str)
		return (NULL);
	return (ft_strlcpy(str, s + start, len + 1), str);
}
