/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:32:02 by besalort          #+#    #+#             */
/*   Updated: 2024/02/06 15:51:41 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_end(t_mdata *data)
{
	t_command *tmp;
	
	tmp = data->cmd;
	while (tmp)
	{
		close_all_files(data, tmp);
		tmp = tmp->next;
	}
}

void	end_loop(t_mdata *data)
{
	close_end(data);
}