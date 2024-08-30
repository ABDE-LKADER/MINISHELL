/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:40:18 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/27 09:48:22 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_int(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_catch_signals = SIGINT;
	}
}

void	sig_handler(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_int);
}

void	set_signals(int status)
{
	sig_handler();
	if (WIFSIGNALED(status) && g_catch_signals == SIGQUIT)
		printf("Quit: %d\n", g_catch_signals);
}
