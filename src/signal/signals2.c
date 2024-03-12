/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:25:23 by afontain          #+#    #+#             */
/*   Updated: 2024/03/07 17:32:43 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_siginthere(int sig_segv)
{
	(void)sig_segv;
	close(STDIN_FILENO);
	write(2, "\n", 1);
	g_retval = 130;
	return ;
}

void	handle_sigint_exec(void)
{
	signal(SIGINT, handle_exec);
}

void	handle_exec(int sig_int)
{
	(void)sig_int;
	g_retval = 130;
}

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
