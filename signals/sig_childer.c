/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_childer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:57:34 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/27 00:20:40 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_int_quit(int sig)
{
	if (sig == SIGINT)
	{
		printf(INIT);
		exit(EXIT_FAILURE);
	}
}

void	sig_heredoc(void)
{
	rl_catch_signals = 1;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_int_quit);
}

static void	signal_int_quit(int sig)
{
	g_catch_signals = sig;
}

void	sig_childer(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, signal_int_quit);
	signal(SIGINT, signal_int_quit);
}
