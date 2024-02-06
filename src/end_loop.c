/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:32:02 by besalort          #+#    #+#             */
/*   Updated: 2024/02/06 17:42:54 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_here_doc()
{
	int	fd;

	fd = open(".here_doc_tmp", O_RDONLY);
	if (fd >= 0)
	{
		close(fd);
		unlink(".here_doc_tmp");
	}
}

void	close_end(t_mdata *data)
{
	t_command *tmp;
	
	tmp = data->cmd;
	while (tmp)
	{
		close_all_files(data, tmp);
		close_here_doc();
		tmp = tmp->next;
	}
}

void	end_loop(t_mdata *data)
{
	close_end(data);
}