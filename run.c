/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:03:20 by abadouab          #+#    #+#             */
/*   Updated: 2024/05/22 22:23:04 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mylib.h"

void    lk(){system("leaks minishell");}

int main(){
	t_allocate	*leak;
	char		*loc;
	char		*loc1;
	char		*loc2;
	char		*loc3;
	char		*loc4;
	char		*loc5;

	atexit(lk);
	leak = NULL;
	loc = ft_itoa(&leak, 10);
	loc1 = ft_itoa(&leak, 120);
	loc2 = ft_itoa(&leak, 1210);
	loc3 = ft_itoa(&leak, 10889);
	loc4 = ft_itoa(&leak, 19990);
	loc5 = ft_itoa(&leak, 1984650);
	cleanup(&leak);
	return (TRUE);
}
