/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_childer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:57:34 by abadouab          #+#    #+#             */
/*   Updated: 2024/09/26 15:50:30 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_int(int sig)
{
	if (sig == SIGINT)
	{
		printf(INIT);
		exit(EXIT_FAILURE);
	}
}

void	sig_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_int);
}

static void	signal_int_quit(int sig)
{
	g_catch_signals = sig;
}

void	sig_childer(void)
{
	signal(SIGQUIT, signal_int_quit);
	signal(SIGINT, signal_int_quit);
}
