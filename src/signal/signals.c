/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:59:04 by afontain          #+#    #+#             */
/*   Updated: 2024/03/22 13:59:14 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sigint)
{
	if (sigint == SIGQUIT)
		return ;
	g_retval = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signals_exec(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_heredoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	g_retval = 130;
	return ;
}

void	error_signal(void)
{
	if (g_retval == 128 + SIGTERM)
		write(STDERR_FILENO, "Terminated\n", 11);
	else if (g_retval == 128 + SIGSEGV)
		write(STDERR_FILENO, "Segmentation fault (core dumped)\n", 33);
	else if (g_retval == 128 + SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	}
	else if (g_retval == 128 + SIGABRT)
		write(STDERR_FILENO, "Aborted (core dumped)\n", 22);
}
