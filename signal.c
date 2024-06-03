/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:40:18 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/03 12:47:36 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_int_quit(int sig)
{
	pid_t	pid;

	pid = wait(NULL);
	if (pid == -1 && sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, signal_int_quit);
	signal(SIGINT, signal_int_quit);
}

static void	heredoc_int_quit(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(EXIT_FAILURE);
	}
}

void	sig_heredoc(void)
{
	rl_catch_signals = 1;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_int_quit);
}
