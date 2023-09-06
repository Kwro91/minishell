/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:59:04 by afontain          #+#    #+#             */
/*   Updated: 2023/09/06 12:59:04 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigsegv(int sigsegv)
{
	(void)sigsegv;
	write(2, "Exit\n", 5);
	exit(1);
}

void handle_sigquit(int sigquit)
{
	(void)sigquit;
	write(STDOUT_FILENO, "Quit (core dump)\n", 17);
}

void handle_sigint(int sigint)
{
	(void)sigint;
	write(STDOUT_FILENO, "\n", 1)
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void handle_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, handle_sigsegv);
	signal(SIGINT, handle_sigint);
}
