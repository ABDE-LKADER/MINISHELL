/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:38:16 by abadouab          #+#    #+#             */
/*   Updated: 2024/05/23 10:44:44 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	*ft_strmapi(t_allocate **alloc, char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*str;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	str = allocate(alloc, len + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
		str[len] = f(len, s[len]);
	return (str);
}
