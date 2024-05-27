/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:39:56 by abadouab          #+#    #+#             */
/*   Updated: 2024/05/23 10:10:21 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	*ft_strjoin(t_allocate **alloc, char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = allocate(alloc, len, sizeof(char));
	if (!str)
		return (NULL);
	i = ft_strlen(s1);
	ft_memcpy(str, s1, i);
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	return (str[i] = '\0', str);
}
