/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:40:14 by besalort          #+#    #+#             */
/*   Updated: 2024/02/02 17:59:13 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_first_child(t_mdata *data, t_command *cmd)
{
	int	pid;
	
	pid = fork();
	if (pid == -1)
		return (perror("Error fork\n"), ft_exit(data), NULL);
	if (pid == 0)
	{
		
	}
}