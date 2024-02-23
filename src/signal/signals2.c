/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:25:23 by afontain          #+#    #+#             */
/*   Updated: 2024/02/22 22:52:09 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sighere(int sig_segv)
{
	(void)sig_segv;
	ft_printf("\n");
	g_retval = 139;
	close(0);
}

void	handle_sigint_exec(void)
{
	signal(SIGINT, handle_exec);
}

void	handle_exec(int sig_int)
{
	(void)sig_int;
	g_retval = 130;
	ft_printf("\n");
}
