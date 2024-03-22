/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:54:38 by besalort          #+#    #+#             */
/*   Updated: 2024/03/22 18:31:06 by afontain         ###   ########.fr       */
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
		if (tmp->here_doc == 0 && cmd->good != -1)
			tmp->fd = open(tmp->files, O_RDWR | O_TRUNC | O_CREAT,
					S_IRWXU);
		else if (cmd->good != -1)
			tmp->fd = open(tmp->files, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
		if (tmp->fd < 0)
			error_open(data, cmd, tmp, 1);
		tmp = tmp->next;
	}
}

void	error_open(t_mdata *data, t_command *cmd, t_files *tmp, int c)
{
	if (access(tmp->files, F_OK) == 0)
	{
		ft_error(data, "minishell: ", 1);
		ft_error(data, tmp->files, 1);
		ft_error(data, ": Permission denied\n", 1);
	}
	else if (c == 0)
	{
		ft_error(data, "minishell: ", 1);
		ft_error(data, tmp->files, 1);
		ft_error(data, ": no such file or directory\n", 1);
	}
	cmd->good = -1;
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
		{
			if (cmd->good != -1 && access(tmp->files, R_OK) != 0)
			{
				cmd->good = -1;
				tmp->fd = -1;
			}
			tmp->fd = open(tmp->files, O_RDONLY);
			if (tmp->fd < 0)
				error_open(data, cmd, tmp, 0);
		}
		else
			ft_mhere_doc(data, cmd, tmp);
		tmp = tmp->next;
	}
}

void	ft_open_mfiles(t_mdata *data, t_command *cmd)
{
	open_in_files(data, cmd);
	open_out_files(data, cmd);
}

t_files	*create_n_f(t_mdata *data, t_files *files, t_command *cmd, t_ifiles *i)
{
	t_files	*new;
	t_files	*tmp;

	new = get_new_file(data, cmd, i);
	tmp = files;
	if (!tmp)
		return (new);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (files);
}
