/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:15:18 by besalort          #+#    #+#             */
/*   Updated: 2024/02/16 16:15:53 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_out(t_mdata *data, t_command *cmd)
{
	t_files	*tmp;

	(void)data;
	if (!cmd->out)
		return ;
	tmp = cmd->out;
	while (tmp)
	{
		if (tmp && tmp->fd > 1)
			close(tmp->fd);
		tmp->fd = -1;
		tmp = tmp->next;
	}
}

void	close_all_in(t_mdata *data, t_command *cmd)
{
	t_files	*tmp;

	(void)data;
	if (!cmd->in)
		return ;
	tmp = cmd->in;
	while (tmp)
	{
		if (tmp && tmp->fd > 1)
			close(tmp->fd);
		tmp->fd = -1;
		tmp = tmp->next;
	}
}

void	close_all_files(t_mdata *data, t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		close_all_in(data, tmp);
		close_all_out(data, tmp);
		tmp = tmp->next;
	}
}

void	close_two(t_mdata *data, int fd1, int fd2)
{
	(void)data;
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
}
