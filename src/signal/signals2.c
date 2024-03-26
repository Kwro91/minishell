/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:25:23 by afontain          #+#    #+#             */
/*   Updated: 2024/03/26 15:31:55 by besalort         ###   ########.fr       */
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

void	handle_sigquit(int sigquit)
{
	(void)sigquit;
	g_retval = 131;
	write(STDOUT_FILENO, "Quit core dump\n", 1);
}

void	handle_sigsegv(int sigsegv)
{
	(void)sigsegv;
	exit(1);
}
