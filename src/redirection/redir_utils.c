/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:54:38 by besalort          #+#    #+#             */
/*   Updated: 2024/02/02 15:44:37 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_out_files(t_mdata *data, t_command *cmd)
{
	t_files	*tmp;

	(void)data;
	if (!cmd->out)
		return ;
	tmp = cmd->out;
	while (tmp)
	{
		if (tmp->here_doc == 0)
			tmp->fd = open(tmp->files, O_RDWR | O_TRUNC | O_CREAT,
					S_IRWXU);
		else
			tmp->fd = open(tmp->files, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
		tmp = tmp->next;
	}
}

void	open_in_files(t_mdata *data, t_command *cmd)
{
	t_files	*tmp;

	if (cmd->in == NULL)
		return ;
	tmp = cmd->in;
	while (tmp)
	{
		if (tmp->here_doc == 0)
			tmp->fd = open(tmp->files, O_RDONLY);
		else
			ft_mhere_doc(data, tmp);
		if (tmp->fd < 0)
		{
			ft_error(data, "minishell: ", 0);
			ft_error(data, tmp->files, 0);
			ft_error(data, ": no such file or directory\n", 0);
		}
		tmp = tmp->next;
	}
}

void	ft_open_mfiles(t_mdata *data, t_command *cmd)
{
	open_in_files(data, cmd);
	open_out_files(data, cmd);
}
