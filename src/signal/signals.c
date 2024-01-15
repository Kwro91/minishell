/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:59:04 by afontain          #+#    #+#             */
/*   Updated: 2024/01/15 13:43:40 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigquit(int sigquit)
{
	(void)sigquit;
	write(STDOUT_FILENO, "Quit (core dump)\n", 17);
}

void	handle_sigsegv(int sigsegv)
{
	(void)sigsegv;
	exit(1);
}

void	handle_sigint(int sigint)
{
	(void)sigint;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSEGV, handle_sigsegv);
	signal(SIGINT, handle_sigint);
}
