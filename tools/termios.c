/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:11:57 by abadouab          #+#    #+#             */
/*   Updated: 2024/07/27 17:16:38 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_if_tty(void)
{
	if (isatty(0) == 0 || isatty(1) == 0 || isatty(2) == 0)
		(printf("Please use a tty :)\n"), exit(2));
}

void	save_termios_mode(t_minishell *ms, bool mode)
{
	check_if_tty();
	if (!mode && tcgetattr(STDIN_FILENO, &ms->termios) == -1)
		perror("tcsetattr");
	if (mode && tcsetattr(STDIN_FILENO, TCSANOW, &ms->termios) == -1)
		perror("tcsetattr");
}
