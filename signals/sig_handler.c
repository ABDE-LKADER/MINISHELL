/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:40:18 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/26 12:21:05 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_int_quit(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_catch_signals = SIGINT;
	}
	if (sig == SIGQUIT)
		g_catch_signals = SIGQUIT;
}

void	sig_handler(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, signal_int_quit);
	signal(SIGINT, signal_int_quit);
}
