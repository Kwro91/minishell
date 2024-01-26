/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:32:59 by afontain          #+#    #+#             */
/*   Updated: 2024/01/22 18:14:00 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(int value, char *cmd)
{
	if (cmd)
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO,"\n", 1);
	return (value);
}

int	error_cmd(char *cmd)
{
	
}