/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:25:23 by afontain          #+#    #+#             */
/*   Updated: 2023/10/17 17:48:03 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sighere(int sig_segv)
{
	(void)sig_segv;
	ft_printf("\n");
	close(0);
}

void	handle_exec(int sig_int)
{
	(void)sig_int;
	ft_printf("\n");
}

void	handle_sigint_exec(void)
{
	signal(SIGINT, handle_exec);
}
