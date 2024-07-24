/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlwr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:31:59 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/23 09:59:59 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	*ft_strlwr(char *str)
{
	int		index;

	if (!str)
		return (NULL);
	index = -1;
	while (str[++index])
		str[index] = ft_tolower(str[index]);
	return (str);
}
