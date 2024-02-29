/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:25:23 by afontain          #+#    #+#             */
/*   Updated: 2024/02/23 18:42:33 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_siginthere(int sig_segv)
{
	(void)sig_segv;
	close(STDIN_FILENO);
	write(2, "\n", 1);
	g_retval = 128;
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
